import pickle
def modify(f):

    count=0

    roll=int(input("Enter rollno to be searched: "))

    f.seek(0)

    print("Reading from binary file: ")

    try:
        while True:
            s=[]
            s1=[]
            pos=f.tell()
            x=pickle.load(f)
            s1.append(x)

            for i in s1:
                if(i[1]==roll):
                    count+=1
                    name=input("Enter your new name: ")
                    rollno=int(input("Enter your new rollno: "))
                    marks=int(input("Enter your new marks: "))

                    s.append(name)
                    s.append(rollno)
                    s.append(marks)

                    f.seek(pos)

                    pickle.dump(s,f)
    except EOFError:
        pass
    f.close()
f=open("bfile.dat",'rb+')
modify(f)
