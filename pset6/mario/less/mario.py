# Implement a program that prints out a half-pyramid of a specified height, per the below.

height = -1
while height < 0 or height > 23:
    try:
        height = int(input("Height: "))
    except ValueError:
        height = -1
        pass

for i in range(1, height + 1):
    output = ""
    for x in range(height - i):
        output += " "
    for x in range(i):
        output += "#"
    output += "#"
    print(output)