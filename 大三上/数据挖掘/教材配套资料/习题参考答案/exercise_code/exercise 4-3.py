import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import PolynomialFeatures
from sklearn.metrics import mean_squared_error

# 生成带噪声的数据集
np.random.seed(0)
X = np.linspace(0, 10, 100).reshape(-1, 1)
y = np.sin(X) + np.random.normal(0, 0.1, size=X.shape)


# 定义多项式回归拟合函数
def polynomial_regression(X, y, degree):
    poly_features = PolynomialFeatures(degree=degree)
    X_poly = poly_features.fit_transform(X)

    model = LinearRegression()
    model.fit(X_poly, y)

    return model, poly_features  # 返回模型和PolynomialFeatures对象


# 可视化原始数据集
plt.scatter(X, y, label='Original Data')

# 尝试不同次数的多项式拟合
degrees = [1, 3, 5, 9]
models = []
polynomial_features_list = []

for degree in degrees:
    model, poly_features = polynomial_regression(X, y, degree)
    y_pred = model.predict(poly_features.transform(X))  # 使用transform方法转换X
    models.append(model)
    polynomial_features_list.append(poly_features)

    plt.plot(X, y_pred, label=f'Degree {degree} Polynomial')

plt.legend()
plt.xlabel('X')
plt.ylabel('y')
plt.title('Polynomial Regression')
plt.show()

# 评估模型拟合效果
for degree, model, poly_features in zip(degrees, models, polynomial_features_list):
    y_pred = model.predict(poly_features.transform(X))
    mse = mean_squared_error(y, y_pred)
    print(f'Degree {degree} Polynomial Regression MSE: {mse}')
