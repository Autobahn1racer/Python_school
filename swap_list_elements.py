def swap(lst):
    N=len(lst)//2
    if len(lst)%2==0:

        for i in range(0,N):
            lst[i],lst[i+N]=lst[i+N],lst[i]
        print(lst)
    else:
        for i in range(0,N):
            lst[i],lst[i+N+1]=lst[i+N+1],lst[i]
        print(lst)
        
lst=list(eval(input("Enter a list: ")))
swap(lst)
