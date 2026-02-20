import pandas as pd
import scipy.stats as st

df=pd.read_csv('../exercise_data/visitor numbers-1.csv').values[:,1]
SK=st.skew(df)  # 计算偏度
K=st.kurtosis(df)  # 计算峰度
print("一月偏度为：",SK)
print("一月峰度为：",K)
