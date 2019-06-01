def read_file():
    cl=0
    cu=0
    cs=0
    while True:
        c=f.read(1)

        if c.islower():
            cl+=1
        elif c.isupper():
            cu+=1
        elif c.isspace():
            cs+=1
            
            
        print(c)
        if not c:
            break
    print("Lower case: ",cl)
    print("Upper case: ",cu)
    print("Spaces: ",(cs-1))

    f.close()

    
f=open("file_handling.txt",'r')
read_file()
