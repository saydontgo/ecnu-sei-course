import numpy as np

class CustomKNN:
    def __init__(self, n_neighbors=3, p=2):
        self.n_neighbors = n_neighbors
        self.p = p

    def fit(self, X, y):
        self.X_train = X
        self.y_train = y

    def predict(self, X):
        y_pred = [self._predict(x) for x in X]
        return np.array(y_pred)

    def _predict(self, x):
        distances = [self._minkowski_distance(x, x_train) for x_train in self.X_train]
        k_indices = np.argsort(distances)[:self.n_neighbors]
        k_nearest_labels = [self.y_train[i] for i in k_indices]
        most_common = np.bincount(k_nearest_labels).argmax()
        return most_common

    def _minkowski_distance(self, x1, x2):
        return np.sum(np.abs(x1 - x2) ** self.p) ** (1 / self.p)

# 示例数据
X_train = np.array([[1, 2], [2, 3], [3, 4], [4, 5]])
y_train = np.array([0, 0, 1, 1])
X_test = np.array([[2.5, 3.5], [1.5, 2.5]])

# 创建并训练KNN分类器
knn_classifier = CustomKNN(n_neighbors=2, p=2)
knn_classifier.fit(X_train, y_train)

# 预测测试数据
predictions = knn_classifier.predict(X_test)
print(predictions)