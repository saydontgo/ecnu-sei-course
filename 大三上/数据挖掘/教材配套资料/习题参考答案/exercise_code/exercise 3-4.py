import numpy as np
import pandas as pd
from scipy.spatial.distance import cityblock, chebyshev

# 导入数据
data = pd.read_csv('../exercise_data/ratings.csv')

# 根据userId、movieId、rating三列得到评分行
pivot_df = data.pivot(index='userId', columns='movieId', values='rating')

# 填充NaN值为0
pivot_df_subset = pivot_df.fillna(0)
print(pivot_df_subset)

# 创建新的DataFrame用于存储矩阵
matrix_df_a = pd.DataFrame(index=pivot_df_subset.index, columns=pivot_df_subset.index)
matrix_df_b = pd.DataFrame(index=pivot_df_subset.index, columns=pivot_df_subset.index)

# 填充曼哈顿距离矩阵
for i in pivot_df_subset.index:
    for j in pivot_df_subset.index:  # 计算用户i和用户j之间的曼哈顿距离
        distance = cityblock(pivot_df_subset.loc[i], pivot_df_subset.loc[j])
        matrix_df_a.loc[i, j] = distance
print(matrix_df_a)

# 填充切比雪夫距离矩阵
for i in pivot_df_subset.index:
    for j in pivot_df_subset.index:  # 计算用户i和用户j之间的切比雪夫距离
        distance = chebyshev(pivot_df_subset.loc[i], pivot_df_subset.loc[j])
        matrix_df_b.loc[i, j] = distance
print(matrix_df_b)

# 保存结果
matrix_df_a.to_csv('距离相关分析-曼哈顿距离.csv')
matrix_df_b.to_csv('距离相关分析-切比雪夫距离.csv')