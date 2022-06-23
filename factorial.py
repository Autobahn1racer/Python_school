def factorial(n):
    #this is just an additional change
    mul=1
    for i in range(1,n+1):
        mul=mul*i
    return(mul)

n=int(input("Enter a no.: "))
m=factorial(n)
print(m)
print("Hello this this is the change made")
