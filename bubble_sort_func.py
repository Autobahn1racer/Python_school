def bubble_sort(l1):
    for i i range(len(l1)):
        for j in range(0,len(l1)-i-1):
            if(l1[j]>l1[j+1]):
                l1[j],l1[j+1]=l1[j+1],l1[j]
    return l1

l1=list(eval(input("Enter a list: ")))
print(bubble_sort(l1))
