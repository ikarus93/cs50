# Implement a program that calculates the minimum number of coins required to give a user change.

cash = -1
while cash < 0:
    try:
        cash = float(input("Change owed: "))
    except ValueError:
        cash = -1

coins_available = [0.25, 0.10, 0.05, 0.01]
coins = 0
while cash > 0:
    for coin in coins_available:
        if coin <= cash:
            coins+=1
            cash = round(cash - coin, 2)
            break

print(coins)