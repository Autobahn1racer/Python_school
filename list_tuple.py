def list_tuple(n):
    tup=()
    m=n.split(',')
    for i in m:
        j=int(i)
        if j%2==0:
            tup+=(j,)
        else:
            continue
    
    

    return(tup)
n=input("Enter a list: ")
print(list_tuple(n))
        
            
