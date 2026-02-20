import numpy as np

class Perceptron:
    def __init__(self, input_size, learning_rate=0.1, epochs=100):
        self.weights = np.zeros(input_size)
        self.bias = 0
        self.learning_rate = learning_rate
        self.epochs = epochs

    def activation(self, x):
        return 1 if x >= 0 else 0

    def predict(self, x):
        z = np.dot(x, self.weights) + self.bias
        return self.activation(z)

    def train(self, X, y):
        for _ in range(self.epochs):
            for i in range(len(X)):
                x = X[i]
                target = y[i]
                update = self.learning_rate * (target - self.predict(x))
                self.weights += update * x
                self.bias += update