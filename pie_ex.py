import matplotlib.pyplot as plt
import numpy as np

l1=[12,34,56,70,90]
lb=['a','s','y','an','p']
l2=['red','blue','green','yellow','orange']

plt.pie(l1,labels=lb,colors=l2,autopct='%3d%%')
plt.show()
