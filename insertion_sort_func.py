def insertion(l1):
    for j in range(1,len(l1)):
        i=j-1
        key=l1[j]
        while i>=0 and key<l1[i]:
            l1[i+1]=l1[i]
            i-=1
        l1[i+1]=key
l1=list(eval(input("Enter a list: ")))
insertion(l1)
print(l1)
        
            
