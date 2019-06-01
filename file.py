def write_file(f):
    ch='y'
    while ch=='Y' or ch=='y':
        str=input("Enter a line: ")
        f.write(str+"\n")
        ch=input("Enter y to continue n to break: ")
    f.close()
f=open("file_handling.txt",'w')
write_file(f)

