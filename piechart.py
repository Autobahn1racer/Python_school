import matplotlib.pyplot as plt
l1=[34,65,12,66,27]
l2=['VIII','IX','X','XI','XII']
clr=['blue','green','red','yellow','gray']
ex=[0,0,0.2,0,0]
plt.title('Pie class')
plt.pie(l1,labels=l2,colors=clr,autopct='%3d%%',explode=ex)
plt.savefig('pie.pdf')
plt.show()
