def read_file():

    while True:
        c=f.read(1)
        if c==' ':
            c='$'
        print(c)
        if not c:
            break

    f.close()

    
f=open("file_handling.txt",'r')
read_file()

    
    
