def matrix(r,c):  

    for i in range(0,r):
        r=[]
        for j in range(0,c):
            print("Enter value for row ",i," and column ",j)
            N=int(input("Enter: "))
            r.append(N)
        lstm.append(r)
   
def transpose(r,c):
    

    for i in range(0,c):
        k=[]
        for j in range(0,r):
            N=lstm[j][i]
            k.append(N)
        lstm2.append(k)
    
def display(r1,c1):   

    for i in range(0,r1):
        print("|",end="")
        for j in range(0,c1):
            print(lstm2[i][j],end="")
        print("|")
lstm=[]
lstm2=[]
print("Matrix 1: ")
r1=int(input("Enter the no. of rows: "))
c1=int(input("Enter the no. of column: "))
matrix(r1,c1)
transpose(r1,c1)
display(c1,r1)

            
