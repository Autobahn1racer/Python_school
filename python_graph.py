import numpy as np
l1=[[1,2,3],[4,5,6],[7,8,9]]
l2=[[1,0,0],[0,1,0],[0,0,1]]
a=np.array(l1)
a1=np.array(l2)
a2=np.arange(3,30,4)    #starting from,limit,gap
print(a.shape)
print(a2.dtype)
print(a*a1)
print(a2)
