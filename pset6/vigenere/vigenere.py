
import sys

def encrypt(s, k):
    k = k.upper()
    print(k)
    output = ""
    i = 0
    for char in s:
        if char.isalpha():

            if char.isupper():
                x = (ord(char) + (ord(k[i]) - 65)) % 90
                if x < 65:
                    if x == 0:
                        #edge case letter 'Z'
                        x = 90
                    else:
                        #wrap char
                        x += 64
                char = chr(x)
            else:
                x = (ord(char) + (ord(k[i]) - 65)) % 122
                if x < 97:
                    if x == 0:
                        #edge case letter 'z'
                        x = 122
                    else:
                        #wrap char
                        x += 96
                char = chr(x)
            #increment iterator
            i += 1
        output += char
        if i == len(k):
            i = 0
    return output


if __name__ == "__main__":
    if len(sys.argv) != 2 or not sys.argv[1].isalpha():
        print("USAGE: python ./vigenere k")
        sys.exit(1)
    s = input("PLAINTEXT: ")

    print("ciphertext: {0}".format(encrypt(s, sys.argv[1])))

