def factorial(n):

    mul=1
    for i in range(1,n+1):
        mul=mul*i
    return(mul)

n=int(input("Enter a no.: "))
m=factorial(n)
print(m)
