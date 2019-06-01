def palindrome(n):
    z=str(n)
    l=len(z)
    t=n
    s=0
    for i in range(l,-1,-1):
        d=t%10
        N=d*(10**(i-1))
        s=s+N
        t=t//10
    if s==n:
        print("It is a palindrome.")
    else:
        print("It is not a palindrome.")

n=int(input("Enter a number: "))
palindrome(n)
        
        
