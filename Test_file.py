def read_file(f):
    c=f.readlines()
    count=0

    for i in  c:
        if i[0]=="A" or i[0]=='a' :
            count+=1
    
    print(count)           
        

f=open("file_handling.txt","r")
read_file(f)
