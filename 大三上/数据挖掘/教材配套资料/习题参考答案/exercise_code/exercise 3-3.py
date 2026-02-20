import pandas as pd
from scipy.stats import kendalltau

# 读取数据集
data = pd.read_csv('../exercise_data/Annual Statistical Indicators Data.csv')

# 缺失值处理
data = data.dropna()

# 提取目标变量列 "年末总人口"，并将其转换为向量
target_variable = data['年末总人口'].values

# 用于存储变量索引和对应的Kendall相关系数
correlation_dict = {}

# 计算Kendall相关系数
for column in data.columns:
    if column != '年末总人口':
        variable = data[column].values
        correlation, _ = kendalltau(variable, target_variable)
        correlation_dict[column] = correlation

# 按照相关系数从高到低排序变量索引
sorted_indices = sorted(correlation_dict, key=correlation_dict.get, reverse=True)

# 打印排序结果
print("变量排序：")
for idx, column in enumerate(sorted_indices):
    print(f"{idx + 1}. {column}")