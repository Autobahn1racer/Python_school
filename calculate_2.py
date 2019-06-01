def calculate_2(n):
    count1=0
    count2=0
    for i in n:
        if i.isdigit():
            count1=count+1
        elif i.isalpha():
            count2=count2+1

    print("No. of digits: ",count1)
    print("No. of alphabets: ",count2)
            
