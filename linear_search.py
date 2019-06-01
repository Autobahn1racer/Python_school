def linear(lst,e):
    t=0
    for i in lst:
        if i==e:
            print("Position is: ",lst.index(i)+1)
            t+=1
            break
    if t==0:
        print("Element not found")
            

lst=list(eval(input("Enter a list: ")))
e=int(input("Enter a number to search: "))
linear(lst,e)
