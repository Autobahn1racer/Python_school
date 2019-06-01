def insert(lst,pos,N):
    nlst=[]
    for i in range(0,len(lst)):
        if (pos-1)==i:
            nlst.append(N)
        nlst.append(lst[i])
    print(nlst)

lst=list(eval(input("Enter a list: ")))
pos=int(input("Enter the position: "))
N=int(input("Enter the new number: "))
insert(lst,pos,N)
