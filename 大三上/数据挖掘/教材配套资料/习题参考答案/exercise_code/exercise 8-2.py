from sklearn.cluster import KMeans, DBSCAN
from sklearn.metrics import silhouette_score
import matplotlib.pyplot as plt
import numpy as np
# 设置绘图字体
plt.rc('font', family='serif', serif=['SimSun'],size=30)
plt.rc('axes', unicode_minus=False)
def perform_clustering(n_samples):
    # 读取数据
    X= np.loadtxt(f"data-8-2-{n_samples}.txt")
    # 使用K-Means 聚类
    kmeans = KMeans(n_clusters=5, random_state=0)
    kmeans.fit(X)
    kmeans_labels = kmeans.predict(X)
    kmeans_score = silhouette_score(X, kmeans_labels)
    # 使用 DBSCAN 聚类
    dbscan = DBSCAN(eps=0.5, min_samples=3)
    dbscan.fit(X)
    dbscan_labels = dbscan.labels_
    #轮廓系数计算
    if len(set(dbscan_labels)) > 1:
        dbscan_score = silhouette_score(X, dbscan_labels)
    else:
        dbscan_score = -1
    # 绘制可视化结果
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 6))
    ax1.scatter(X[:, 0], X[:, 1], c=kmeans_labels, cmap='viridis')
    ax1.set_title(f'K-Means (轮廓系数: {kmeans_score:.2f})',fontsize=20)
    ax1.tick_params(axis = "both", labelsize=20)
    ax2.scatter(X[:, 0], X[:, 1], c=dbscan_labels, cmap='viridis')
    ax2.set_title(f'DBSCAN (轮廓系数: {dbscan_score:.2f})',fontsize=20)
    ax2.tick_params(axis="both", labelsize=20)
    plt.xticks(fontsize=20)
    plt.yticks(fontsize=20)
    plt.show()
    return kmeans_score, dbscan_score
# 计算聚类结果
results = {}
for n in [50, 100, 1000]:
    results[n] = perform_clustering(n_samples=n)
print(results)