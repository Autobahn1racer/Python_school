def sort_hyphen(S):
    N=S.split("-")
    M=""
    for i in range(0,2*len(N)-1):
        
        if N[i]>N[i+1]:
            N[i],N[i+1]=N[i+1],N[i]
    
    for j in N:
        
            M+=j+"-"
        
        
    return(M[:-1])

S=input("Enter a string: ")
print(sort_hyphen(S))
        
