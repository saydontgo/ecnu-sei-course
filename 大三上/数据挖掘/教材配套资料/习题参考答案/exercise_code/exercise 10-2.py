#导入数据集---2
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeRegressor
from sklearn.ensemble import RandomForestRegressor

# 从Excel文件读取数据
filename = '../exercise_data/10-2.csv'
df = pd.read_excel(filename)

# 数据划分
X = df[['Feature1']]
y = df['Target']

# 划分数据集
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# 使用决策树进行回归
tree_reg = DecisionTreeRegressor(max_depth=3, random_state=42)
tree_reg.fit(X_train, y_train)
y_pred_tree = tree_reg.predict(X_test)

# 使用随机森林进行回归
forest_reg = RandomForestRegressor(n_estimators=100, max_depth=3, random_state=42)
forest_reg.fit(X_train, y_train.ravel())
y_pred_forest = forest_reg.predict(X_test)

# 绘制回归结果
plt.figure(figsize=(12, 6))

plt.subplot(1, 2, 1)
plt.scatter(X_test, y_test, s=20, edgecolor="black", c="darkorange", label="data")
plt.plot(X_test, y_pred_tree, color="cornflowerblue", linewidth=2, label="Decision Tree Prediction")
plt.title("Decision Tree Regression")
plt.xlabel("X")
plt.ylabel("y")
plt.legend()

plt.subplot(1, 2, 2)
plt.scatter(X_test, y_test, s=20, edgecolor="black", c="darkorange", label="data")
plt.plot(X_test, y_pred_forest, color="forestgreen", linewidth=2, label="Random Forest Prediction")
plt.title("Random Forest Regression")
plt.xlabel("X")
plt.ylabel("y")
plt.legend()

plt.show()
