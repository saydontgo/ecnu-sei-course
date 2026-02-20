import matplotlib.pyplot as plt
from sklearn.datasets import load_iris
import statsmodels.api as sm
# 1.加载鸢尾花数据集
data = load_iris()
X = data.data[:, 2].reshape(-1, 1)  # 只选择一个特征（花瓣长度）
y = data.data[:, 3]  # 目标变量（花瓣宽度）
# 2.绘制散点图
plt.scatter(X, y)
plt.xlabel("Petal Length")
plt.ylabel("Petal Width")
plt.title("Scatter Plot of Iris Dataset")
plt.show()
# 3.建模
X = sm.add_constant(X)
model = sm.OLS(y, X)
regressor = model.fit()
print(regressor.summary())
