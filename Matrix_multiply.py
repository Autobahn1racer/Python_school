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

def multiply(a,r1,c1,b,r2,c2):
    C=[]
    if r1==c2:

        for i in range(0,r1):
            S=0
            r=[]
            for j in range(0,c1):
                for k in range(0,c1):
                    S+=a[i][k]*b[k][j]
                
                r.append(S)
            C.append(r)
        print(C)
    else:
        print("The matrix cannot be multiplied.")

def display(r,c):
    
    
    

    for i in range(0,r):
        print("|",end="")
        for j in range(0,c):
            print(C[i][j],end="")
        print("|")
a=[]
b=[]
C=[]
print("Matrix 1: ")
r1=int(input("Enter the no. of rows: "))
c1=int(input("Enter the no. of column: "))

print("Matrix 2: ")
r2=int(input("Enter the no. of rows: "))
c2=int(input("Enter the no. of column: "))
a=matrix(r1,c1)
b=matrix(r2,c2)
c=multiply(a,r1,c1,b,r2,c2)
display(r1,c1)

        
