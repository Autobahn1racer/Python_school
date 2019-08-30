import matplotlib.pyplot as plt
import numpy as np
w=np.arange(7)
x=['jan','feb','mar','apr','may','jun','jul']
north=[140,130,130,190,160,200,150]
south=[160,200,130,200,200,170,110]
east=[140,180,150,170,190,190,170]
west=[180,150,200,120,180,140,110]
central=[110,160,130,110,120,170,130]
plt.xlabel('MONTHS')
plt.ylabel('RAINFALL')
plt.title('RAIN')
plt.bar(w,north,width=0.1,label='north')
plt.bar(w+0.1,south,width=0.1,label='south')
plt.bar(w+0.2,east,width=0.1,label='east')
plt.bar(w+0.3,west,width=0.1,label='west')
plt.bar(w+0.4,central,width=0.1,label='central')

plt.xticks(w,x)
plt.yticks(np.arange(0,300,10))
plt.legend(loc='upper-left')
plt.show()
