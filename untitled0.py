from numpy import save,load
import numpy as np

data = np.zeros((16,4),dtype=int)
save('data.npy', data)
data=load('data.npy')
print(data)