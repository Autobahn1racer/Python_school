def SUM(n):
    if n==1:
        return 1
    else:
        return (n+SUM(n-1))
n=int(input("Enter a number: "))
print(SUM(n))
