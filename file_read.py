import os

def read_file():
    if os.path.isfile("file.txt"):
        f=open("file.txt",'r')
        print("The file is present.")
        f.close()
    else:
        print("The file is not present.")

read_file()


