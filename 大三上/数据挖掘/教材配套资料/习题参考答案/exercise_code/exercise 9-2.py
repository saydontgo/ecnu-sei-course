import numpy as np
import tensorflow as tf
from tensorflow import keras
from keras.models import load_model
import pandas as pd
import seaborn as sns
from pylab import rcParams
import matplotlib.pyplot as plt
from pandas.plotting import register_matplotlib_converters
from sklearn.preprocessing import StandardScaler

plt.rcParams['lines.linewidth'] = 6.0
def create_dataset(X, y, time_steps=1):
    Xs, ys = [], []
    for i in range(len(X) - time_steps):
        v = X.iloc[i:(i + time_steps)].values
        Xs.append(v)
        ys.append(y.iloc[i + time_steps])
    return np.array(Xs), np.array(ys)
# 1.可视化初始设置
plt.rcParams['font.sans-serif']=['SimSun']   # 显示中文标签
font = {'family': 'SimSun', 'weight': 'normal', 'size': 20}
register_matplotlib_converters()
sns.set(style='whitegrid', palette='muted', font_scale=1.5)
rcParams['figure.figsize'] = 10, 5
RANDOM_SEED = 42
np.random.seed(RANDOM_SEED)
tf.random.set_seed(RANDOM_SEED)
# 2.数据读取
df = pd.read_csv('../exercise_data/NYC Taxi.csv', parse_dates=['timestamp'], index_col='timestamp')
# 3.划分训练集和测试集
train_size = int(len(df) * 0.95)
test_size = len(df) - train_size
train, test = df.iloc[0:train_size], df.iloc[train_size:len(df)]
print(train.shape, test.shape)
# 4.进行数据归一化，提升模型训练效果
scaler = StandardScaler()
scaler = scaler.fit(train[['value']])
train['value'] = scaler.transform(train[['value']])
test['value'] = scaler.transform(test[['value']])
TIME_STEPS = 48   # 每天的采样数为48，因此将时间步长设为48
X_train, y_train = create_dataset(train[['value']], train.value, TIME_STEPS)   # 按照时间步长（30）生成数据
X_test, y_test = create_dataset(test[['value']], test.value, TIME_STEPS)
print(X_train.shape)   # 输出为：(7752, 30, 1)
# 5.模型创建及拟合
model = keras.Sequential()  # 初始化一个序列模型
model.add(keras.layers.LSTM(units=64, input_shape=(X_train.shape[1], X_train.shape[2])))  # 添加一个LSTM层，64个单元，输入形状为训练数据的时间步长和特征数
model.add(keras.layers.Dropout(rate=0.2))  # 添加一个Dropout层，丢弃率为20%，用于减少过拟合
model.add(keras.layers.RepeatVector(n=X_train.shape[1]))  # 重复向量层，重复特征向量以匹配输出序列的长度
model.add(keras.layers.LSTM(units=64, return_sequences=True))  # 添加第二个LSTM层，返回整个序列到下一层
model.add(keras.layers.Dropout(rate=0.2))  # 再次添加Dropout层，丢弃率为20%
model.add(keras.layers.TimeDistributed(keras.layers.Dense(units=X_train.shape[2])))  # 添加一个时间分布式全连接层，每个时间步应用一个全连接层
model.compile(loss='mae', optimizer='adam')  # 编译模型，使用平均绝对误差作为损失函数和Adam优化器
history = model.fit(X_train, y_train, epochs=10, batch_size=32, validation_split=0.1, shuffle=False)
# 6.计算预测loss
X_train_pred = model.predict(X_train)
train_mae_loss = np.mean(np.abs(X_train_pred - X_train), axis=1)
a=20
b=15
# 7.模型预测，并进行异常检测
X_test_pred = model.predict(X_test)
test_mae_loss = np.mean(np.abs(X_test_pred - X_test), axis=1)
THRESHOLD = np.percentile(test_mae_loss, 98)   # 将阈值设为前5%的MAE对应的值
test_score_df = pd.DataFrame(index=test[TIME_STEPS:].index)
test_score_df['loss'] = test_mae_loss
test_score_df['threshold'] = THRESHOLD
test_score_df['anomaly'] = test_score_df.loss > test_score_df.threshold
test_score_df['close'] = test[TIME_STEPS:].value
anomalies = test_score_df[test_score_df.anomaly == 1]
plt.close()
# 8.异常检测结果可视化
test_data = test[TIME_STEPS:].value.values.reshape(-1, 1)
predicted_values = scaler.inverse_transform(test_data)
plt.plot(test[TIME_STEPS:].index, predicted_values, label='交通流量')
anomalies_data = anomalies.close.values.reshape(-1, 1)
anomalies_data = scaler.inverse_transform(anomalies_data)
sns.scatterplot(anomalies.index, anomalies_data.flatten(), color=sns.color_palette()[3], s=50, label='异常值')
plt.xlabel('日  期', fontfamily='SimSun', fontsize=a)
plt.ylabel('交通流量', fontfamily='SimSun',fontsize=a)
plt.xticks(rotation=25)
plt.legend(prop=font)
plt.tick_params(labelsize=b)
plt.tight_layout()
plt.show()
