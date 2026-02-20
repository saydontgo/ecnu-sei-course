import numpy as np
from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import PCA
from sklearn.cluster import AgglomerativeClustering, OPTICS, SpectralClustering
from sklearn.metrics import silhouette_score
import matplotlib.pyplot as plt
import seaborn as sns
#1.设置绘图字体
plt.rc('font', family='serif', serif=['SimSun'],size=20)
plt.rc('axes', unicode_minus=False)
#2.读取数据
data = np.loadtxt("data-8-4.txt")
#3.数据标准化
scaler = StandardScaler()
data_scaled = scaler.fit_transform(data)
#4.PCA降维到2维
pca = PCA(n_components=2)
data_pca = pca.fit_transform(data_scaled)
#5.可视化降维后的数据
plt.figure(figsize=(8, 6))
plt.scatter(data_pca[:, 0], data_pca[:, 1], s=10)
plt.title("PCA降维后的数据")
plt.xlabel("主成分1")
plt.ylabel("主成分2")
plt.show()
#6.准备一个函数来计算最佳簇类数
def find_best_clusters(data, max_clusters):
    best_score = -1
    best_k = 0
    for k in range(2, max_clusters + 1):
        model = AgglomerativeClustering(n_clusters=k)
        labels = model.fit_predict(data)
        score = silhouette_score(data, labels)
        if score > best_score:
            best_score = score
            best_k = k
    return best_k, best_score
#7.层次聚类
best_k_hierarchical, best_score_hierarchical = find_best_clusters(data_pca, 10)
model_hierarchical = AgglomerativeClustering(n_clusters=best_k_hierarchical)
labels_hierarchical = model_hierarchical.fit_predict(data_pca)
print(f"层次聚类 - 最佳簇类数: {best_k_hierarchical}, 轮廓系数: {best_score_hierarchical:.4f}")
#8.可视化层次聚类结果
plt.figure(figsize=(8, 6))
sns.scatterplot(x=data_pca[:, 0], y=data_pca[:, 1], hue=labels_hierarchical, palette="viridis", s=10)
plt.title(f"层次聚类结果 (最佳簇类数: {best_k_hierarchical})")
plt.xlabel("主成分1")
plt.ylabel("主成分2")
plt.legend(title="簇类")
plt.show()
#9.OPTICS算法参数调优
best_optics_score = -1
best_optics_params = None
min_samples_values = np.arange(2, 21, 1)  # min_samples 范围
for min_samples in min_samples_values:
    optics_model = OPTICS(min_samples=min_samples, xi=0.05, min_cluster_size=0.1)
    labels_optics = optics_model.fit_predict(data_pca)
    # 排除所有点都被标记为噪声的情况
    if len(set(labels_optics)) > 1:
        score = silhouette_score(data_pca, labels_optics)
        if score > best_optics_score:
            best_optics_score = score
            best_optics_params = min_samples
#10.使用最佳参数训练OPTICS模型
optics_model = OPTICS(min_samples=best_optics_params, xi=0.05, min_cluster_size=0.1)
labels_optics = optics_model.fit_predict(data_pca)
print(f"OPTICS聚类 - 最佳min_samples: {best_optics_params}, 轮廓系数: {best_optics_score:.4f}")
#11.可视化OPTICS聚类结果
plt.figure(figsize=(8, 6))
sns.scatterplot(x=data_pca[:, 0], y=data_pca[:, 1], hue=labels_optics, palette="viridis", s=10)
plt.title("OPTICS聚类结果")
plt.xlabel("主成分1")
plt.ylabel("主成分2")
plt.legend(title="簇类")
plt.show()
#12.谱聚类
best_k_spectral, best_score_spectral = find_best_clusters(data_pca, 10)
model_spectral = SpectralClustering(n_clusters=best_k_spectral, affinity='nearest_neighbors')
labels_spectral = model_spectral.fit_predict(data_pca)
print(f"谱聚类 - 最佳簇类数: {best_k_spectral}, 轮廓系数: {best_score_spectral:.4f}")
#13.可视化谱聚类结果
plt.figure(figsize=(8, 6))
sns.scatterplot(x=data_pca[:, 0], y=data_pca[:, 1], hue=labels_spectral, palette="viridis", s=10)
plt.title(f"谱聚类结果 (最佳簇类数: {best_k_spectral})")
plt.xlabel("主成分1")
plt.ylabel("主成分2")
plt.legend(title="簇类")
plt.show()