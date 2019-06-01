def position(lst,val):
    size=len(lst)-1
    pos=-1
    if val<lst[0]:
        return 1
    else:
        for i in range(size):
            if lst[i]<=val and lst[i+1]>val:
                pos=i+1
        if pos<=-1 and i<=size:
            pos=size+1
        return pos+1

def insertion(lst,val):
    pos=position(lst,val)
    print(pos)
    lst.append(None)
    z=len(lst)-1
    while z>pos-1:
        lst[z]=lst[z-1]
        z-=1
    lst[pos-1]=val

    print(lst)

lst=list(eval(input("Enter a list: ")))
val=int(input("Enter an element: "))
insertion(lst,val)
