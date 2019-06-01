def insert(lst,val,pos):
    lst.append(0)
    z=len(lst)-1
    while z>pos-1:
        lst[z]=lst[z-1]
        z-=1
    lst[pos-1]=val

    print(lst)

lst=list(eval(input("Enter a list: ")))
val=int(input("Enter value to be inserted: "))
pos=int(input("enter position: "))
insert(lst,val,pos)
