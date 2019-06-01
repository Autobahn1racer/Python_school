def prime(n):
    c=0
    for i in range(2,n):
        if (n%i==0):
            c=c+1
            break
        else:
            continue
    if(c==1):
        print("It is not a prime no.")
    else:
        print("It is a prime no.")

n=int(input("Enter a number: "))
prime(n)
