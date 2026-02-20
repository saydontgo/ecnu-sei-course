import pandas as pd

data = pd.read_excel('../exercise_data/stock.xlsx')
ts = list(data['星期一']) + list(data['星期二']) + list(data['星期三']) + list(data['星期四']) + list(data['星期五'])
ts = pd.DataFrame(ts, columns=['price'])
# 计算以5为窗口的均值
window_size = 5
smoothed_values = ts['price'].rolling(window=window_size, center=True).mean()