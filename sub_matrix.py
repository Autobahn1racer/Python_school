def matrix(r,c):

    lstm=[]

    for i in range(0,r):
        r=[]
        for j in range(0,c):
            print("Enter value for row ",i," and column ",j)
            N=int(input("Enter: "))
            r.append(N)
        lstm.append(r)
    return lstm
def display(c,r1,c1):
    
    
    

    for i in range(0,r1):
        print("|",end="")
        for j in range(0,c1):
            print(c[i][j],end="")
        print("|")
def add(a,r1,c1,b,r2,c2,c):
    
    if r1!=r2 or c1!=c2:
        print("Matrix cannot be added.")
    else:
        for i in range(0,r1):
            k=[]
            for j in range(0,c1):
                N=a[i][j]-b[i][j]
                k.append(N)
            c.append(k)
        return c

a=[]
b=[]
c=[]
print("Matrix 1: ")
r1=int(input("Enter the no. of rows: "))
c1=int(input("Enter the no. of column: "))
print("Matrix 2: ")
r2=int(input("Enter the no. of rows: "))
c2=int(input("Enter the no. of column: "))
a=matrix(r1,c1)
b=matrix(r2,c2)
c=add(a,r1,c1,b,r2,c2,c)
display(c,r1,c1)
        
    
