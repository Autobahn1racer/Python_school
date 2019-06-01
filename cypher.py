N=int(input("Enter the key: "))
S=input("Enter the text: ")
M=""
for i in S:
    n=0
    if(i==" "):
        M=M+i
    elif i.isdigit():
        n=n+N
        n=str(n)
        M=M+n
    else:
        l=ord(i)+N
        if l>=97 and l<=122:
            d=ord(i)+N
            d=chr(d)
            M=M+d
        else:
            j=(ord(i)+N)-122
            e=96+j
            e=chr(e)
            M=M+e
print(M)
            
