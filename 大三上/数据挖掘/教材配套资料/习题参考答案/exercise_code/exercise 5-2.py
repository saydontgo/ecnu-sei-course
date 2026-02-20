import matplotlib.pyplot as plt
from sklearn.datasets import load_digits
from sklearn.decomposition import PCA

#1.加载手写数字数据集
digits = load_digits()
X = digits.data
y = digits.target

#2.实例化一个PCA对象，将数据降至二维
pca = PCA(n_components=2)
X_pca = pca.fit_transform(X)

#3.可视化降维后的数据
plt.figure(figsize=(10, 8))
scatter = plt.scatter(X_pca[:, 0], X_pca[:, 1], c=y, edgecolor='none', alpha=0.8, cmap=plt.cm.get_cmap('tab10', 10))
plt.colorbar(scatter)
plt.title('PCA of Digits dataset')
plt.xlabel('Principal Component 1')
plt.ylabel('Principal Component 2')
plt.show()