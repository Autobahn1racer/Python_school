def unique(n):
    N=[]
    for i in n:
        if i not in N:
            N.append(i)
        else:
            pass
        
    return(N)

n=list(eval(input("Enter some numbers: ")))
print(unique(n))
                
