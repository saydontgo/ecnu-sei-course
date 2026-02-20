import numpy as np
A = np.array([[1, 3, 2],
              [5, 3, 1],
              [3, 4, 5]])
U, S, V = np.linalg.svd(A, full_matrices = 0)
print('左奇异矩阵:')
print(U)
print('奇异值矩阵:')
print(S)
print('右奇异矩阵:')
print(V)
reconstructed_matrix=np.dot(U,np.dot(np.diag(S),V.T))
print("\n通过SVD重构的矩阵:")
print(reconstructed_matrix)