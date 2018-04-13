import crypt
import sys
import math




if __name__ == "__main__":

    if len(sys.argv) != 2:
        #check command line args for validity
        sys.exit(1)
    #retrieve first two characters of hashed password as salt
    salt = sys.argv[1][:2]

    base = ['a'] #base to create pw string
    alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"  #alphabet to iterate over while creating password string
    #way to increment or add to base array
    a, b, c, d, e = 1, 0, 0, 0, 0

    #start iteration
    for i in range(0, int(math.pow(52, 5)) + 51):

        #increment first character in base string
        base[0] = alphabet[a]

        #check for validity
        pw = "".join(base)
        if crypt.crypt(pw, salt) == sys.argv[1]:
            print(pw)
            break

        #if reach end of alphabet string, increment or create second character in base string, third character etc.
        if a + 1 == len(alphabet):
            a = -1
            if len(base) < 2:
                base.append('a')
            else:
                base[1] = alphabet[b]
            b += 1

        if b == len(alphabet):
            b = 0
            if len(base) < 3:
                base.append('a')
            else:
                base[2] = alphabet[c]
            c += 1

        if c == len(alphabet):
            c = 0
            if len(base) < 4:
                base.append('a')
            else:
                base[3] = alphabet[d]
            d += 1

        if d == len(alphabet):
            d = 0
            if len(base) < 5:
                base.append('a')
            else:
                base[4] = alphabet[e]
            e += 1

        if e == len(alphabet):
            e = 0

        a += 1








