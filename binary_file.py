import pickle
def writebinaryfile(f):

    ch='y'
    print("Writing on this file: ")

    while ch=='Y' or ch=='y':

        s=[]
        name=input("Enter your name: ")
        rollno=int(input("Enter your rollno: "))
        marks=int(input("Enter your marks: "))

        s.append(name)
        s.append(rollno)
        s.append(marks)

        pickle.dump(s,f)

        ch=input("Enter y to continue n to stop: ")
    f.close()
f=open("bfile.dat",'wb+')
writebinaryfile(f)
