def seek1():
   while True:
        f.seek(' ')
        c=f.read(1)
        if c==' ':
            c='$'
        
        
        if not c:
            break
   f.close()

f=open("file_handling.txt",'r')
seek1()
