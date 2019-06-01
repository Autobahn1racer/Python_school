def even_odd(n):
    if n%2==0:
        return("The number is even")
    else:
        return("The number is odd.")

n=int(input("Enter a number: "))
print(even_odd(n))
