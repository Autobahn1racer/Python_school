import pickle
def readbinaryfile(f):
    f.seek(0)

    print("reading from binary file: ")
    S1=[]

    try:
        while True:
            x=pickle.load(f)
            S1.append(x)
    except EOFError:
        pass

    for i in S1:

        print("Name: ",i[0])
        print("Roll no.: ",i[1])
        print("Marks: ",i[2])
    f.close()

f=open("bfile.dat",'rb+')
readbinaryfile(f)
