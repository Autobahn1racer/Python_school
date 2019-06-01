def square(n):
    N=[]
    for i in range(1,n+1):
        
        j=i**2
        N.append(j)
    return(N)

n=int(input("Enter a number: "))
print(square(n))
        
