with open("file_handling.txt",'r+') as f:

    for line in f:
        words = line.split()

        for k in words:

            if k[0]=='T' or k[0]=='t':
                K=k[::-1]
                print(K,end=" ")
            else:
                print(k,end=" ")

    f.close()
                
