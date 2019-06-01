def even(n):
    N=[]
    for i in n:
        if int(i)%2==0:
            N.append(i)
        else:
            pass
    return(N)

n=list(eval(input("Enter some numbers: ")))
print(even(n))
