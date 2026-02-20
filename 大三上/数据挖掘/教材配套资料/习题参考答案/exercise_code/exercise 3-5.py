import numpy as np
from scipy.spatial.distance import mahalanobis

def chi_square_distance(x, y):
    distance = np.sum((x - y) ** 2 / (x + y))
    return distance

def covariance_matrix(X):
    n = X.shape[0]
    mean = np.mean(X, axis=0)
    covariance = np.dot((X - mean).T, (X - mean)) / (n - 1)
    return covariance

def mahalanobis_distance(x, y, cov):
    distance = mahalanobis(x, np.mean(X, axis=0), cov)
    return distance

# 示例数据矩阵
x = np.array([1, 2, 3])
y = np.array([4, 5, 6])
# 将两个向量合并成一个矩阵
X = np.vstack((x, y))
# 计算协方差矩阵
cov = covariance_matrix(X)
# 计算卡方距离
distance_chi = chi_square_distance(x, y)
# 计算马氏距离
distance_ma = mahalanobis_distance(x, y, cov)
print("卡方距离:", distance_chi)
print("马氏距离:", distance_ma)