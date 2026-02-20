#导入数据集---3
import numpy as np
import pandas as pd
import xgboost as xgb
import lightgbm as lgb
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error

# 从Excel文件中读取数据
data = pd.read_excel("../exercise_data/10-3.csv")

# 划分特征和目标变量
X = data.drop(columns='Sales')
y = data['Sales']

# 划分训练集和测试集
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# 构建XGBoost回归模型
xgb_model = xgb.XGBRegressor()

# 训练XGBoost模型
xgb_model.fit(X_train, y_train)

# 预测XGBoost模型
y_pred_xgb = xgb_model.predict(X_test)

# 评估XGBoost模型
mse_xgb = mean_squared_error(y_test, y_pred_xgb)
print("XGBoost均方误差（MSE）:", mse_xgb)

# 构建LightGBM回归模型
lgb_model = lgb.LGBMRegressor()

# 训练LightGBM模型
lgb_model.fit(X_train, y_train)

# 预测LightGBM模型
y_pred_lgb = lgb_model.predict(X_test)

# 评估LightGBM模型
mse_lgb = mean_squared_error(y_test, y_pred_lgb)
print("LightGBM均方误差（MSE）:", mse_lgb)

# 绘制XGBoost结果
plt.figure(figsize=(10, 6))
plt.scatter(y_test, y_pred_xgb, color='blue')
plt.plot([y_test.min(), y_test.max()], [y_test.min(), y_test.max()], color='red', linestyle='--')
plt.xlabel('True Sales')
plt.ylabel('Predicted Sales (XGBoost)')
plt.title('True vs Predicted Sales (XGBoost)')
plt.show()

# 绘制LightGBM结果
plt.figure(figsize=(10, 6))
plt.scatter(y_test, y_pred_lgb, color='green')
plt.plot([y_test.min(), y_test.max()], [y_test.min(), y_test.max()], color='red', linestyle='--')
plt.xlabel('True Sales')
plt.ylabel('Predicted Sales (LightGBM)')
plt.title('True vs Predicted Sales (LightGBM)')
plt.show()