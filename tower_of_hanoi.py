def towerofhanoi(n,source,destination,auxilary):
    if n==1:
        print("Move disk from",source,"to",destination)
        return
    towerofhanoi(n-1,source,auxilary,destination)
    print("Move disk from",source,"to",destination)
    towerofhanoi(n-1,auxilary,destination,source)
n=int(input("Enter no. of disks: "))
towerofhanoi(n,'A','C','B')
