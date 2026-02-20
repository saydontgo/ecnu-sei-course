# ==========================
# Biomass Estimation Training Pipeline (TensorFlow)
# ==========================
import pandas as pd
import numpy as np
import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers
from tensorflow.keras.preprocessing import image_dataset_from_directory

from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
import os
from PIL import Image

# ==========================
# 1. Load and preprocess train.csv
# ==========================
df = pd.read_csv("train.csv")

# pivot to wide format: one row per image
targets = ["Dry_Green_g", "Dry_Dead_g", "Dry_Clover_g", "GDM_g", "Dry_Total_g"]
df_wide = df.pivot_table(index=["image_path", "Sampling_Date", "State", "Species", "Pre_GSHH_NDVI", "Height_Ave_cm"],
                         columns="target_name", values="target").reset_index()

# fill missing target columns (in case some targets are missing)
for t in targets:
    if t not in df_wide.columns:
        df_wide[t] = 0.0

print("Data shape:", df_wide.shape)
df_wide.head()

# ==========================
# 2. Split into train/val
# ==========================
train_df, val_df = train_test_split(df_wide, test_size=0.1, random_state=42)

# 1. 创建并 Fit Scaler (只用训练集！)
scaler = StandardScaler()
scaler.fit(train_df[targets])

# 2. Transform 训练集和验证集
train_df_scaled = train_df.copy()
val_df_scaled = val_df.copy()

train_df_scaled[targets] = scaler.transform(train_df[targets])
val_df_scaled[targets] = scaler.transform(val_df[targets])

# ==========================
# 3. Image preprocessing pipeline
# ==========================
IMG_SIZE = (380, 380)
BATCH_SIZE = 32

def load_image(path, labels):
    img = tf.io.read_file(path)
    img = tf.image.decode_jpeg(img, channels=3)
    # ！！！关键修改！！！
    # 不再使用 tf.image.resize，它会压扁图像
    # 使用 resize_with_pad 来保持宽高比
    img = tf.image.resize_with_pad(img, IMG_SIZE[0], IMG_SIZE[1])
    # ！！！修改结束！！！
    img = tf.cast(img, tf.float32) / 255.0
    return img, labels

def make_dataset(df, training=True):
    X_paths = df["image_path"].values
    X_paths = [os.path.join(".", x) for x in X_paths]
    # 使用缩放后的值！
    y = df[targets].values.astype(np.float32) 
    ds = tf.data.Dataset.from_tensor_slices((X_paths, y))
    ds = ds.map(load_image, num_parallel_calls=tf.data.AUTOTUNE)
    if training:
        ds = ds.shuffle(len(df)) # 提示：shuffle buffer 最好设为数据集大小
    return ds.batch(BATCH_SIZE).prefetch(tf.data.AUTOTUNE)

train_ds = make_dataset(train_df_scaled)
val_ds = make_dataset(val_df_scaled, training=False)

# ==========================
# 4. Build model (EfficientNetB4 backbone)
# ==========================
MODEL_PATH = "my_biomass_model.keras"

if os.path.exists(MODEL_PATH):
    print(f"INFO: 发现已保存的模型，正在加载 {MODEL_PATH}...")
    # 加载完整的模型（包括权重和优化器状态）
    model = keras.models.load_model(MODEL_PATH)
else: 
    print("INFO: 未找到已保存的模型，正在构建新模型...")
    base = keras.applications.EfficientNetB0(include_top=False, weights="imagenet", input_shape=(*IMG_SIZE,3), pooling="avg")

    x_in = layers.Input(shape=(*IMG_SIZE,3))
    x = base(x_in, training=True)
    x = layers.Dense(256, activation="relu")(x)
    x = layers.Dropout(0.3)(x)
    x_out = layers.Dense(5, activation="linear")(x)  # 5 regression outputs
    model = keras.Model(x_in, x_out)

    model.compile(
        optimizer=keras.optimizers.Adam(1e-5),
        loss="mse",
        metrics=[keras.metrics.MeanAbsoluteError()]
    )

    model.summary()

# ==========================
# 5. Train model
# ==========================
history = model.fit(
    train_ds,
    validation_data=val_ds,
    epochs=200
)
model.save("my_biomass_model.keras")
print("✅ 模型已成功保存到 my_biomass_model.keras")
# ==========================
# 6. Define Weighted R² for evaluation
# ==========================
def weighted_r2(y_true, y_pred):
    # 每个目标的权重
    weights = np.array([0.1, 0.1, 0.1, 0.2, 0.5])

    # 平均值需要对每个目标单独计算
    y_mean = np.average(y_true, axis=0)

    # 残差平方和（每个目标一列）
    ss_res = np.sum((y_true - y_pred) ** 2, axis=0)

    # 总方差平方和（每个目标一列）
    ss_tot = np.sum((y_true - y_mean) ** 2, axis=0)

    # 每个目标的R²
    r2_each = 1 - ss_res / ss_tot

    # 加权平均R²
    weighted_r2 = np.sum(weights * r2_each) / np.sum(weights)
    return weighted_r2

# compute R² on validation set
y_true_list, y_pred_list = [], []
for imgs, ys_scaled in val_ds:
    preds_scaled = model.predict(imgs) # preds_scaled 也是标准化的预测

    # ！！！关键步骤：反转归一化！！！
    y_true_list.append(scaler.inverse_transform(ys_scaled.numpy()))
    y_pred_list.append(scaler.inverse_transform(preds_scaled))
y_true = np.vstack(y_true_list)
y_pred = np.vstack(y_pred_list)
print("Weighted R²:", weighted_r2(y_true, y_pred))
print("R² for each target:", 1 - np.sum((y_true - y_pred)**2, axis=0) /
                             np.sum((y_true - np.mean(y_true, axis=0))**2, axis=0))

# ==========================
# 7. Predict test set and create submission.csv
# ==========================
test_df = pd.read_csv("test.csv")  # must contain image_path, sample_id

rows = []
for img_path in test_df["image_path"]:
    full_path = os.path.join(".", img_path)
    img = Image.open(full_path).convert("RGB").resize(IMG_SIZE)
    arr = np.array(img) / 255.0
    arr = np.expand_dims(arr, 0)
    pred = model.predict(arr)[0]
    for name, val in zip(targets, pred):
        rows.append({"sample_id": f"{os.path.basename(img_path).replace('.jpg','')}__{name}", "target": val})

sub = pd.DataFrame(rows)
sub.to_csv("submission.csv", index=False)
print("✅ submission.csv generated successfully.")
