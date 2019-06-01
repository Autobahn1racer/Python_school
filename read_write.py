def read_file():

    while True:
        c=f.read(1)
        if c==' ':
            c='$'
        f2.write(c)
        
        if not c:
            break

    f.close()
    f2.close()

    
f=open("file_handling.txt",'r')
f2=open("file2.txt",'w')
read_file()

