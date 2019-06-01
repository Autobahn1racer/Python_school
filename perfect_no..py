def perfect(n):
    s=0
    for i in range(1,n):
        if(n%i==0):
            s=s+i
    if(s==n):
        print("It is a perfect no.")
    else:
        print("It is not a perfect no.")

n=int(input("enter a number: "))
perfect(n)
            
