# This program is calculates the least amount of quarters needed to give a customer their change using quarters, dimes, nickels and pennies
import cs50
import math

# if the user does not input a number higher than 0 it will continue to ask for change due to customer
while True:
    changeOwed = cs50.get_float("change owed:")
    if changeOwed > 0:
        break

# to handle imprecision we convert the change to a whole number
convertedChange = changeOwed * 100

# initializing a running total counter
count = 0

# checks if the change is more than 25 cents, if so it will count how many quarters can be evenly diveded into the change and stores the remaining change in the variable convertedChange
while convertedChange >= 25:

    count += math.floor(convertedChange / 25)
    convertedChange %= 25

# checks if the change is more than 10 cents, if so it will count how many dimes can be evenly diveded into the change and stores the remaining change in the variable convertedChange
while convertedChange >= 10 and convertedChange < 25:

    count += math.floor(convertedChange / 10)
    convertedChange %= 10

# checks if the change is more than 5 cents, if so it will count how many nickels can be evenly diveded into the change and stores the remaining change in the variable convertedChange
while convertedChange >= 5 and convertedChange < 10:

    count += math.floor(convertedChange / 5)
    convertedChange %= 5

# checks if the change is more than 1 cent, if so it will count how many pennies can be evenly diveded into the change
while convertedChange >= 1 and convertedChange < 5:

    count += convertedChange / 1
    convertedChange %= 1

# prints the amount of coins that were needed to give the customer their correct change
print(int(count), "\n")
