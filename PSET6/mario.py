# this program creates a nintendo mario like pyramid by first asking the user for the height. And the pyramid blocks are represented by hashes
import cs50

# if the input is not a number greater than zero or less than 8 inclusive, the user will be prompted until a number from 1-8 is entered
while True:
    height = cs50.get_int("height: ")
    if height > 0 and height < 9:
        break
# this for loop will start at zero up to the value of height +1 to get desired amount of blocks
for x in range(0, height+1, 1):
    print(x * "#")
    print(((height - x)-1) * " ", end="")
