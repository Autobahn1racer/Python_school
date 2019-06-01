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

def display(r,c):
    
    
    lstm1=matrix(r,c)

    for i in range(0,r):
        print("|",end="")
        for j in range(0,c):
            print(lstm1[i][j],end="")
        print("|")

    if r==c:
        for  i in range(0,r):
            for j in range(0,c):
                if i>=j:
                    print(lstm1[i][j],end="")
            print()
    if r==c:
        for  i in range(0,r):
            for j in range(0,c):
                
                if i<=j:
                    print(lstm1[i][j],end="")
                else:
                    print(end=" ")
            print()
    else:
        print("diagnol not possible.")

                

r=int(input("Enter the no. of rows: "))
c=int(input("Enter the no. of column: "))
display(r,c)


        
