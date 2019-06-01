with open("file_handling.txt",'r') as f:

    for line in f:
        words = line.split()

        for k in words:

            if k[0]=='T' or k[0]=='t':
                print(k)
