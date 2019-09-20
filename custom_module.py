def factorial(n):

    mul=1
    for i in range(1,n+1):
        mul=mul*i
    return(mul)


def fibonacci_term(n):
    if n==1 or n==0:
        return n

    else:
        return fibonacci_term(n-1)+fibonacci_term(n-2)

def fibonacci(n):
    series=[]
    for i in range(0,n+1):
        series.append(fibonacci_term(i))
    return series


def reverse(n):
    s=""
    for i in n:
        s=i+s
    print("The reversed string is: ",s)
