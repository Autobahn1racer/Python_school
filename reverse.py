def reverse(n):
    s=""
    for i in n:
        s=i+s
    print("The reversed string is: ",s)

n=input("Enter a word: ")
reverse(n)
        
