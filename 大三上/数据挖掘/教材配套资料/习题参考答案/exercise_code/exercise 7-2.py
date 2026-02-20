from sklearn.model_selection import train_test_split
import pandas as pd
from sklearn.metrics import accuracy_score, recall_score, precision_score, f1_score
from sklearn.preprocessing import StandardScaler, MinMaxScaler
from sklearn.svm import SVC

data = pd.read_csv('../exercise_data/inferior user.csv', encoding='ansi')  # 读入数据集
print(data['是否为不良账户'].value_counts(), '\n')  # 查看数据平衡性
# 划分训练集和测试集
X = data.iloc[:,:-1]
y = data.iloc[:,-1]
X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=666)
# 特征归一化
standardScaler = StandardScaler()
standardScaler.fit(X_train)
X_train_standard = standardScaler.transform(X_train)
X_test_standard = standardScaler.transform(X_test)
# 训练模型
clf = SVC(kernel='linear') #采用高斯核函数
clf.fit(X_train_standard, y_train)
y_pred = clf.predict(X_test_standard)
# 评价模型
print('accuracy', accuracy_score(y_pred, y_test))
print('precision', precision_score(y_pred, y_test))
print('recall', recall_score(y_pred, y_test))
print('f1 score', f1_score(y_pred, y_test))