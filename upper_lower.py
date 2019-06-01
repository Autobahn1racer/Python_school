def calculate(n):
    count1=0
    count2=0
    for i in n:
        ch=ord(i)
        
        if(ch>=97 or ch<=124):
            count1=count1+1
        elif(ch>=65 or ch<=92):
            count2=count2+1

    print("The number of uppercase letter: ",count1)
    print("The number of lowercase letter: ",count2)

n=input("enter a word: ")
calculate(n)
            
