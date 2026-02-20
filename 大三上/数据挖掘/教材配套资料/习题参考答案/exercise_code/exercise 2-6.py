import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.dates as mdates

plt.rcParams.update({'font.size': 13})
df = pd.read_csv('../exercise_data/visitor numbers-2.csv')
df['日期'] = pd.to_datetime(df['日期'], format='%m月%d日')
plt.rcParams['font.sans-serif'] = ['SimSun']
plt.rcParams['axes.unicode_minus'] = False
x = df['日期']
y = df['游客量']
fig, ax = plt.subplots()
ax.plot(x,
         y,
         linestyle='-',
         linewidth=2,
         color='#FEE599',
         marker='o',
         markersize=6,
         markeredgecolor='black',
         markerfacecolor='#F7CBAC',
         label='日游客量'             )
plt.title('二月游客量折线图')
plt.xlabel('日期')
plt.ylabel('游客量')
plt.grid(axis="y")
ax.xaxis.set_major_formatter(mdates.DateFormatter('%m-%d'))
plt.tight_layout()
plt.show()
