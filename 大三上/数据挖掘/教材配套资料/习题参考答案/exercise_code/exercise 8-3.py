import matplotlib.pyplot as plt
import numpy as np
from sklearn.mixture import GaussianMixture
from sklearn.metrics import silhouette_score
# 读取数据
X = np.loadtxt("../exercise_data/data-8-3.txt")
# 设置绘图字体
plt.rc('font', family='serif', serif=['SimSun'])
plt.rc('axes', unicode_minus=False)
# 评估不同簇类数下的高斯混合聚类性能
n_components_range = range(2, 6)
silhouette_scores = []
for n_components in n_components_range:
    # 应用高斯混合模型聚类
    gmm = GaussianMixture(n_components=n_components,
                          random_state=42)
    gmm_labels = gmm.fit_predict(X)
    # 计算轮廓系数
    score = silhouette_score(X, gmm_labels)
    silhouette_scores.append(score)
# 可视化不同簇类数的轮廓系数
plt.figure(figsize=(10, 6))
plt.plot(n_components_range, silhouette_scores, marker='o')
plt.xlabel('聚类数',fontsize=20)
plt.ylabel('轮廓系数',fontsize=20)
plt.xticks(n_components_range,fontsize = 20)
plt.yticks(fontsize = 20)
plt.show()
print("最佳聚类数：",
      n_components_range[np.argmax(silhouette_scores)])
gmm = GaussianMixture(n_components=n_components_range[np.argmax(silhouette_scores)],
                      random_state=42)
gmm_labels = gmm.fit_predict(X)
plt.figure(figsize=(10, 6))
plt.scatter(X[:, 0], X[:, 1], c=gmm_labels, cmap='viridis',s=30)
plt.show()