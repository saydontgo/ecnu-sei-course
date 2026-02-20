import pandas as pd
import matplotlib.pyplot as plt

plt.rcParams['font.sans-serif'] = ['SimSun']
plt.rcParams.update({'font.size': 13})
df = pd.read_csv('../exercise_data/visitor numbers.csv')
x = df['游客量']
plt.figure()
plt.hist(x, color='#C5E0B3', edgecolor='k', alpha=0.5)
plt.grid(alpha=0.5, linestyle='-.')
plt.xlabel('游客量')
plt.ylabel('频数')
plt.title('第一季度游客量频数分布直方图')
plt.show()
