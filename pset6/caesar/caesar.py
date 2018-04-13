# Implement a program that encrypts messages using Caesar’s cipher, per the below.


import sys

def encrypt(s, k):
    if k > 26:
        k = k % 26
    output = ""
    for char in s:
        if char.isalpha():
            if char.isupper():
                x = (ord(char) + k) % 90
                if x < 65:
                    #wrap char
                    x += 64
                char = chr(x)
            else:
                x = (ord(char) + k) % 122
                if x < 97:
                    #wrap char
                    x += 96
                char = chr(x)
        output += char
    return output


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit(1)
    s = input("PLAINTEXT: ")

    print("ciphertext: {0}".format(encrypt(s, int(sys.argv[1]))))

