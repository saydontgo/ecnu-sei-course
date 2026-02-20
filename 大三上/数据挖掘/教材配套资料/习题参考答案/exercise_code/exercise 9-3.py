import datetime
import pandas as pd
import matplotlib.pyplot as plt
from statsmodels.tsa.stattools import adfuller
from statsmodels.tsa.arima.model import ARIMA
from sklearn.metrics import mean_squared_error

# 函数：检验时间序列的平稳性
def check_adfuller(ts):
    result = adfuller(ts, autolag='AIC')
    print('Test statistic: ', result[0])
    print('p-value: ', result[1])
    print('Critical Values:', result[4])
plt.rcParams['font.sans-serif'] = ['STSong']   # 显示中文标签
font = {'family': 'STZhongsong', 'weight': 'normal', 'size': 24}
# 1.提取Bindikuri地区的平均温度数据
weather = pd.read_csv("../exercise_data/Summary of weather.csv")
weather = weather.loc[:, ["STA","Date","MeanTemp"]]
weather_bin = weather[weather.STA == 32907]
weather_bin["Date"] = pd.to_datetime(weather_bin["Date"])
# 2.创建时间序列
timeSeries = weather_bin.loc[:, ["Date","MeanTemp"]]
timeSeries.index = timeSeries.Date
ts = timeSeries.drop("Date",axis=1)
# 3.Dickey-Fuller Test检验时间序列的平稳性
check_adfuller(ts.MeanTemp)
# 4.模型拟合
model = ARIMA(ts, order=(1,0,1)) #阶数分别为1,0,1
model_fit = model.fit()
# 5.预测
start_index = datetime.datetime(1944, 6, 25)
end_index = datetime.datetime(1945, 5, 31) #设置测试集范围
forecast = model_fit.predict(start=start_index, end=end_index)
error = mean_squared_error(ts[start_index:], forecast) #计算测试集的平均预测误差
print("error: ", error)   # 输出为：“error:  1.9872544975809587”
# 6.异常检测：实际值与预测值相差超过阈值
next_days = start_index
outliers_df = pd.DataFrame(columns=['days', 'temp'])
while next_days <= end_index:
    try:
        actual_value = ts.at[next_days, 'MeanTemp']
        if abs(forecast[next_days] - actual_value) / actual_value > 0.18: #判断预测值与实际值的偏差是否超过阈值（0.18）
            outliers_df = outliers_df.append({'days': next_days, 'temp': ts.at[next_days, 'MeanTemp']}, ignore_index=True) #若超过，则加入异常值集合
        next_days += datetime.timedelta(days=1)
    except:
        next_days += datetime.timedelta(days=1)
        continue
# 7.对结果进行可视化
plt.figure(figsize=(22,10))
plt.plot(weather_bin.Date, weather_bin.MeanTemp, color='#ACD2C7', label="实 际 数 据")
plt.plot(forecast, color='#D57B70', label="预 测 数 据")
plt.scatter(outliers_df['days'], outliers_df['temp'], color='#94B5D8', label='异 常 值', s=200, alpha=0.8)
plt.xlabel("日  期", font)
plt.ylabel("平均气温/摄氏度", font)
plt.legend(prop=font)
plt.tick_params(labelsize=22)
plt.show()