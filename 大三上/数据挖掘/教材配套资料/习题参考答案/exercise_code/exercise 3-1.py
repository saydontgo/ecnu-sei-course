def pearson_correlation(x, y):
    # 计算均值
    mean_x = sum(x) / len(x)
    mean_y = sum(y) / len(y)
    # 计算协方差
    cov = sum((xi - mean_x) * (yi - mean_y) for xi, yi in zip(x, y))
    # 计算标准差
    std_x = (sum((xi - mean_x) ** 2 for xi in x)) ** 0.5
    std_y = (sum((yi - mean_y) ** 2 for yi in y)) ** 0.5
    pearson_corr = cov / (std_x * std_y)  # 计算皮尔逊相关系数
    return pearson_corr

# 示例数据
x = [1, 2, 3, 4, 5]
y = [2, 4, 6, 8, 10]
# 计算皮尔逊相关系数
corr_coefficient = pearson_correlation(x, y)
print("皮尔逊相关系数:", corr_coefficient)