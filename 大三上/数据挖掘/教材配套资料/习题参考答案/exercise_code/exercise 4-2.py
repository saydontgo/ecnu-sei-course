import pandas as pd
from sklearn.preprocessing import PolynomialFeatures
from sklearn.linear_model import LinearRegression
# 1.读取数据集
data = pd.read_csv('../exercise_data/auto_mpg.csv')
data = data.dropna()
# 2.一元多项式回归分析
def univariate_polynomial_regression(X, y):
    # 创建多项式特征
    poly_features = PolynomialFeatures(degree=2)
    X_poly = poly_features.fit_transform(X)
    # 创建线性回归模型
    lin_regression = LinearRegression()
    # 拟合模型
    lin_regression.fit(X_poly, y)
    # 预测
    y_pred = lin_regression.predict(X_poly)
    # 计算R^2评分
    r2_score = lin_regression.score(X_poly, y)
    print("一元多项式回归分析结果:")
    print("R^2 Score:", r2_score)
# 3.多元多项式回归分析
def multivariate_polynomial_regression(X, y):
    # 创建多项式特征
    poly_features = PolynomialFeatures(degree=2)
    X_poly = poly_features.fit_transform(X)
    # 创建线性回归模型
    lin_regression = LinearRegression()
    # 拟合模型
    lin_regression.fit(X_poly, y)
    # 预测
    y_pred = lin_regression.predict(X_poly)
    # 计算R^2评分
    r2_score = lin_regression.score(X_poly, y)
    print("多元多项式回归分析结果:")
    print("R^2 Score:", r2_score)

X_uni = data['displacement'].values.reshape(-1, 1)
y_uni = data['mpg'].values.reshape(-1, 1)
univariate_polynomial_regression(X_uni, y_uni)
X_multi = data[['displacement', 'cylinders', 'horsepower', 'weight']]
y_multi = data['mpg']
multivariate_polynomial_regression(X_multi, y_multi)
