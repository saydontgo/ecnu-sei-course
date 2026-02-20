import numpy as np
import pandas as pd
from statsmodels.tsa.vector_ar.var_model import VAR
import matplotlib.pyplot as plt
from statsmodels.tsa.stattools import adfuller

# ADF检验函数
def adf_test(series):
    result = adfuller(series)
    p_value = result[1]
    return p_value
# 进行平稳性判断和差分操作
def check_stationarity(df):
    p_values = []
    stationary = False
    while not stationary:
        for column in df.columns:# 对每一列时间序列进行ADF检验
            p_value = adf_test(df[column])
            p_values.append(p_value)
        if all(p_value <= 0.05 for p_value in p_values):# 判断所有变量的p-value是否小于等于阈值（例如0.05）
            stationary = True
        else:
            df = df.diff().dropna()# 进行一阶差分操作
            p_values = []
    return df

df = pd.read_csv('../exercise_data/SKAB.csv', index_col=0)  # 读取文件
# 判断多元时间序列是否平稳，并进行差分操作
stationary_df = check_stationarity(df)
if stationary_df.empty:
    print("不平稳")
else:
    print("平稳")
# 训练VAR模型
model = VAR(stationary_df)
results = model.fit()
residuals = results.resid  # 获取残差序列
scores = np.linalg.norm(residuals, axis=1)  # 计算异常得分
scores = pd.DataFrame(scores)
# 标记异常
threshold = scores.quantile(0.96)# 设置异常阈值
plt_scores = scores.iloc[:100,:]  # 为更清晰地展示异常点，此处仅展示前100个数据
anomalies = np.where(plt_scores > threshold)[0]# 标记异常点
# 结果可视化
plt.plot(plt_scores, label='scores')
plt.scatter(anomalies, plt_scores.values[anomalies], color='red', label='Anomaly')
plt.xlabel('Time')
plt.ylabel('Scores')
plt.title('VAR Anomaly detection')
plt.legend()
plt.show()