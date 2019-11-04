import matplotlib.pyplot as plt
import numpy as np


x=[15,16,16.5,17,17.5,18,18.5]
y=[1,8,18,28,36,46,56]

plt.xticks(np.arange(15,25))
plt.yticks(np.arange(1,60,5))
plt.title('Just a line')
plt.plot(x,y,marker='d',markerfacecolor='red',linestyle='dashed')
plt.show()
