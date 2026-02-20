import pandas as pd
import numpy as np
from sklearn.preprocessing import MinMaxScaler

data = pd.read_excel('../exercise_data/stock.xlsx')
ts = list(data['星期一']) + list(data['星期二']) + list(data['星期三']) + list(data['星期四']) + list(data['星期五'])
ts = np.array(ts).reshape(-1,1)
# 创建MinMaxScaler对象
scaler = MinMaxScaler()
# 最大最小规范化
ts = scaler.fit_transform(ts)