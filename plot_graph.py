import matplotlib.pyplot as plt
x=['VIII','IX','X','XI','XII']
y=[120,115,110,44,27]
plt.xlabel('classes')
plt.ylabel('Total no. of students')
plt.plot(x,y)
plt.title('Population')
plt.plot(x,y,linestyle='solid',linewidth=2,color='blue',marker='d',markeredgecolor='red',markersize=8)
plt.show()
