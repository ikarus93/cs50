from functools import reduce

def check_number(n):

    #reverse number and transform into list
    reversed_n = list(reversed(list(str(n))))
    evens = [] #container for even indexes
    odds = [] #container for odd indexes

    for i, num in enumerate(reversed_n):
        #iterate over number and append numbers to fitting containers
        if i % 2 == 0:
            evens.append(int(num))
        else:
            num = str(int(num) * 2)
            if len(num) > 1:
                # add product digits together
                num = int(num[0]) + int(num[1])
            else:
                num = int(num)
            odds.append(num)

    # reduce them to final product, append product to other list for further reduction
    odds = reduce(lambda x, y: x + y, odds)
    evens.append(odds)

    result = reduce(lambda x, y: x + y, evens)

    master_card = [51, 52, 53, 54, 55]
    visa = 4
    amex = [34, 37]
    first_two = str(n)[:2]
    #verify card by comparing first two to respective lists
    if result % 10 == 0:
        if int(first_two) in master_card:
            return "MASTERCARD"
        elif int(first_two) in amex:
            return "AMEX"
        elif int(first_two[0]) == visa:
            return "VISA"
        else:
            return "INVALID"
    else:
        return "INVALID"


if __name__ == "__main__":
    card_number = int(input("Number: "))
    result = check_number(card_number)
    print(result)