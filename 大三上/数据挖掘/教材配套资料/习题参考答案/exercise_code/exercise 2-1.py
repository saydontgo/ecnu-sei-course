import pandas as pd

data = pd.read_excel('../exercise_data/shared bikes.xlsx')
# 均值填充
data['标准化温度'] = data['标准化温度'].fillna(data['标准化温度'].mean())
data['湿度'] = data['湿度'].fillna(data['湿度'].mean())
data['风速'] = data['风速'].fillna(data['风速'].mean())
data['总租赁数'] = data['总租赁数'].fillna(data['总租赁数'].mean())
# 众数填充
data['天气'] = data['天气'].fillna(data['天气'].mode())