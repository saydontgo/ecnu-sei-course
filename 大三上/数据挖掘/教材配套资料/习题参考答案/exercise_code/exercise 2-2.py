import pandas as pd

data = pd.read_excel('../exercise_data/shared bikes.xlsx')
data_encoded = pd.get_dummies(data, columns=['天气'])
