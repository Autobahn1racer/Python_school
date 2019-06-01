def reverse(n):
    if len(n)==1:
        return n
    else:
        return n[len(n)-1]+reverse(n[:len(n)-1])
n=input("Enter a string: ")
print(reverse(n))
