def binary_search(lst,l,h,mid,e):
    if not l<=h:
        return -1
    mid=(l+h)//2

    if e==mid:
        print("The position is : ",lst.index(mid)+1)
    elif e>mid:
        l=mid+1
        return binary_search(lst,l,h,mid+1,e)
    else:
        h=mid-1
        return binary_search(lst,l,h,mid-1,e)
lst=list(eval(input("Enter a list: ")))
e=int(input("Enter a number to search: "))

l=lst[0]
h=lst[len(lst)-1]
mid=(l+h)//2
binary_search(lst,l,h,mid,e)


    
