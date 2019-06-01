top=None
def check(stack):
    if top==-1:
        return True
    else:
        return False
def push(stack,value):
    global top
    stack.append(value)
    top=len(stack)-1
    
def pop(stack):
    global top
    C=check(stack)
   
    if stack!=[]:
        val=stack.pop()
        print("Top element is removed." )
        if stack==[]:
            top=None
        else:
            top=len(stack)-1
    else:
        print("Stack is empty.")
    
def peek(stack):
    print(stack[top])
    
def display(stack):
    if top==None:
        print("The stack is empty: ")
        return
    print(stack[top],"<--- top")

    for i in range(top-1,-1,-1):
        print(stack[i])
        print()
stack=[]
while(True):
    choice=int(input("Enter 1 for pushing an element \nEnter 2 for poping an element \nEnter 3 for displaying peek \nEnter 4 for displaying the stack: "))

    if choice==1:
        N=int(input("Enter a number: "))
        push(stack,N)
    elif choice==2:
        pop(stack)
    elif choice==3:
        peek(stack)
    elif choice==4:
        display(stack)

    
    N1=input("Do you wish to continue? ")

    if N1=="Y" or N1=='y' or N1=='yes':
        continue
    else:
        break
    

    
    
