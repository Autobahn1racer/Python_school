def palindrome_2(n):

    s=""
    for i in range(1,len(n)+1):
        s=s+n[len(n)-i]
    if s==n:
        print("It is a palindrome.")
    else:
        print("It is not a palindrome.")
        
n=input("Enter a word: ")
palindrome_2(n)
