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
def transpose(r,c):
    

    for i in range(0,c):
        k=[]
        for j in range(0,r):
            N=lstm[j][i]
            k.append(N)
        lstm2.append(k)
def add(a,r1,c1,b,r2,c2,c):
    
    if r1!=r2 or c1!=c2:
        print("Matrix cannot be added.")
    else:
        for i in range(0,r1):
            k=[]
            for j in range(0,c1):
                N=a[i][j]+b[i][j]
                k.append(N)
            c.append(k)
        return c

def display():
    c=int(input("Enter 1 for add matrix\nEnter 2 for transpose\nEnter 3 for multiplication:"))
    lstm1=[]
    if c==1:
        r1=int(input("Enter the no. of rows: "))
        c1=int(input("Enter the no. of column: "))
        r2=int(input("Enter the no. of rows: "))
        c2=int(input("Enter the no. of column: "))
        a=matrix(r1,c1)
        b=matrix(r2,c2)
        lstm1=add(a,r1,c1,b,r2,c2,c)
    elif c==2:
        r=int(input("Enter the no. of rows: "))
        c=int(input("Enter the no. of column: "))
        lstm=matrix(r,c)
        transpose(r,c)
        lstm1=lstm
    elif c==3:
        r1=int(input("Enter the no. of rows: "))
        c1=int(input("Enter the no. of column: "))
        r2=int(input("Enter the no. of rows: "))
        c2=int(input("Enter the no. of column: "))
        a=matrix(r1,c1)
        b=matrix(r2,c2)
        multiply(a,r1,c1,b,r2,c2)
        
        

    for i in range(0,r):
        print("|",end="")
        for j in range(0,c):
            print(lstm1[i][j],end="")
        print("|")

    

                


display()


        
