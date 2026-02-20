import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.preprocessing import StandardScaler
from sklearn.cluster import KMeans
from sklearn.manifold import TSNE

#1.读取数据
red_wine_df = pd.read_csv(r'./data/5-3.csv', index_col=0)

#2.数据处理
red_wine_df.isnull().sum()
scaler = StandardScaler()
red_wine_scaled = pd.DataFrame(data=scaler.fit_transform(red_wine_df), columns=red_wine_df.columns)

#3.模型构建
kmeans = KMeans(n_clusters=3)
cluster = kmeans.fit_predict(red_wine_scaled)
tsne2D = TSNE(n_components=2)
tsne_data2D = tsne2D.fit_transform(red_wine_scaled)
tsne2D_df = pd.DataFrame(data=tsne_data2D, columns=['x', 'y'])
tsne2D_df['cluster'] = cluster

#4.可视化降维后的数据
plt.figure(figsize=(6, 5), dpi=600)
sns.scatterplot(x='x', y='y', hue='cluster', data=tsne2D_df)
plt.title("t-SNE")
plt.show()
plt.savefig('t-SNE.png')