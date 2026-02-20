import numpy as np
from scipy import stats
from sklearn.datasets import load_iris

# 加载鸢尾花数据集
iris = load_iris()
data = iris.data

# 提取特征维度
sepal_length = data[:, 0]
sepal_width = data[:, 1]
petal_length = data[:, 2]
petal_width = data[:, 3]

# 计算特征维度之间的Spearman秩相关系数矩阵
correlation_matrix, p_matrix = stats.spearmanr(data)
print("特征维度之间的Spearman秩相关系数矩阵:")
print(correlation_matrix)