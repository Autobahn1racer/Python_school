def binary_search(lst,e):
    l=lst[0]
    h=lst[len(lst)-1]
    m=(l+h)//2
    pos=0
    while True:
        

        if e<m:
            h=m-1
        elif e>m:
            l=m+1
        elif e==m:
            pos=lst.index(e)
            break
        else:
            pos=-1
            break

        m=(l+h)//2
    if pos!=-1:
        print("The position is: ",pos+1)
    else:
        print("Element not found.")

lst=list(eval(input("Enter a list: ")))
e=int(input("Enter a number to search: "))
binary_search(lst,e)
            
            
            
        
