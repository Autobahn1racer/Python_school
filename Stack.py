top=None

def push(stack,value):
    global top
    stack.append(value)
    top=len(stack)-1
def peek(stack):
    print(stack[top])
def display(stack):
    print(stack[top],"<--- top")
    for i in range(top-1,-1,-1):
        print(stack[i])
def pop(stack):
    stack.pop()
stack=[]

while True:
    choice=int(input("Enter 1 to push \nEnter 2 to peek\nEnter 3 to display:\nEnter 4 to pop: "))
    if choice==1:
        N=int(input("Enter a value: "))
        push(stack,N)
    elif choice==2:
        peek(stack)
    elif choice==3:
        display(stack)
    elif choice==4:
        pop(stack)

    ch2=input("Do u want to continue: ")
    if ch2=='y':
        continue
    else:
        break


    
    
