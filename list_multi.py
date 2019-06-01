def list_multi(n):
    s=1
    for i in range(0,len(n)):
        s=s*n[i]
    return(s)

n=list(eval(input("Enter some numbers: ")))
N=list_multi(n)
print("The product is: ",N)      
