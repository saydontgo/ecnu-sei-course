from scipy.cluster.hierarchy import dendrogram, linkage
from matplotlib import pyplot as plt
import numpy as np
# 设置中文显示
plt.rc('font', family='serif', serif=['SimSun'])
plt.rc('axes', unicode_minus=False)
# 输入数据
X = np.loadtxt("data-8-1.txt")
# 执行层次聚类
linked = linkage(X, 'single')
# 绘制树状图
plt.figure(figsize=(10, 8))
dendrogram(linked,
            orientation='top',
            labels=range(1, 11),
            distance_sort='descending',
            show_leaf_counts=True)
plt.xticks(fontsize=30)
plt.yticks(fontsize=30)
plt.title("单链接",fontsize=30)
plt.xlabel("索引",fontsize=30)
plt.ylabel("距离",fontsize=30)
plt.show()
# 执行层次聚类
linked = linkage(X, 'complete')
# 绘制树状图
plt.figure(figsize=(10, 9))
dendrogram(linked,
            orientation='top',
            labels=range(1, 11),
            distance_sort='descending',
            show_leaf_counts=True)
plt.xticks(fontsize=30)
plt.yticks(fontsize=30)
plt.title("全链接",fontsize=30)
plt.xlabel("索引",fontsize=30)
plt.ylabel("距离",fontsize=30)
plt.show()
# 执行层次聚类
linked = linkage(X, 'average')
# 绘制树状图
plt.figure(figsize=(10, 8))
dendrogram(linked,
            orientation='top',
            labels=range(1, 11),
            distance_sort='descending',
            show_leaf_counts=True)
plt.xticks(fontsize=30)
plt.yticks(fontsize=30)
plt.title("平均链接",fontsize=30)
plt.xlabel("索引",fontsize=30)
plt.ylabel("距离",fontsize=30)
plt.show()
# 执行层次聚类
linked = linkage(X, 'ward')
# 绘制树状图
plt.figure(figsize=(13, 8))
dendrogram(linked,
            orientation='top',
            labels=range(1, 11),
            distance_sort='descending',
            show_leaf_counts=True)
plt.xticks(fontsize=30)
plt.yticks(fontsize=30)
plt.title("Ward链接",fontsize=30)
plt.xlabel("索引",fontsize=30)
plt.ylabel("距离",fontsize=30)
plt.show()