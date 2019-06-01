def armstrong(n):
    t=n
    z=str(n)
    l=len(z)
    s=0
    while(n>0):
        d=n%10
        m=d**l
        s=s+m
        n=n//10
    if (s==t):
        print("It is an armstrong number.")
    else:
        print("it is not an armstrong number.")

n=int(input("Enter a number: "))
armstrong(n)
        
        
    
