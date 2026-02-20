#导入数据集---1
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.ensemble import AdaBoostRegressor, GradientBoostingRegressor
from sklearn.tree import DecisionTreeRegressor

# 从Excel文件读取数据
filename = '../exercise_data/10-1.csv'
df = pd.read_excel(filename)

# 数据划分
X = df[['Feature1']]
y = df['Target']

# 划分数据集
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# 使用AdaBoost进行回归
ada_boost_reg = AdaBoostRegressor(base_estimator=DecisionTreeRegressor(max_depth=4), n_estimators=100, random_state=42)
ada_boost_reg.fit(X_train, y_train)
y_pred_ada = ada_boost_reg.predict(X_test)

# 使用梯度提升树进行回归
grad_boost_reg = GradientBoostingRegressor(n_estimators=100, max_depth=4, learning_rate=0.1, random_state=42)
grad_boost_reg.fit(X_train, y_train)
y_pred_grad = grad_boost_reg.predict(X_test)

# 绘制回归结果
plt.figure(figsize=(12, 6))

plt.subplot(1, 2, 1)
plt.scatter(X_test, y_test, s=20, edgecolor="black", c="darkorange", label="data")
plt.plot(X_test, y_pred_ada, color="cornflowerblue", linewidth=2, label="AdaBoost Prediction")
plt.title("AdaBoost Regression")
plt.xlabel("X")
plt.ylabel("y")
plt.legend()

plt.subplot(1, 2, 2)
plt.scatter(X_test, y_test, s=20, edgecolor="black", c="darkorange", label="data")
plt.plot(X_test, y_pred_grad, color="forestgreen", linewidth=2, label="Gradient Boosting Prediction")
plt.title("Gradient Boosting Regression")
plt.xlabel("X")
plt.ylabel("y")
plt.legend()

plt.show()