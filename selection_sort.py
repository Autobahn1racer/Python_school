def selection(lst):
    small=0
    for  i in range(0,len(lst)):
        small=i
        for j in range(i+1,len(lst)):
            if lst[j]<lst[small]:
                small=j
        lst[i],lst[small]=lst[small],lst[i]
    return lst

lst=list(eval(input("Enter the list: ")))
print(selection(lst))
                
                
