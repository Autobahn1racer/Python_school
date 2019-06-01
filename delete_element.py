def linear(lst,e):
    t=0
    for i in lst:
        if i==e:
            return lst.index(i)+1
            t+=1
            break
    if t==0:
        return False

def delete(lst,e):
    VAL=linear(lst,e)
    if VAL==False:
        print("The element was not found.")
    else:
        for i in range(VAL-1,len(lst)-1):
            lst[i]=lst[i+1]
    lst=lst[:-1]
    return lst

lst=list(eval(input("Enter a list: ")))
e=int(input("Enter a number to search: "))
L=delete(lst,e)   
print(L)    

