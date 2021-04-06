# get get_float from cs50 library
from cs50 import get_float

# list of coin values
coins = [25, 10, 5, 1]
# number of coins
Coins = 0

# condition for user prompt
while True:
    cash = get_float("Change owed: ")
    if cash > 0:
        break
    else:
        True
# convert change to cents
cents = round(cash * 100)
# check if quotient of remaining cents is greater than 0
for i in range(len(coins)):
    if cents / coins[i] > 0:
        coins_added = int(cents / coins[i])
        cents -= int(coins_added * coins[i])
        Coins += int(coins_added)
# print number of coins
print(f"{Coins}")
