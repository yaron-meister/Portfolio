## Function example
from datetime import datetime

print()
print("########################################")
print("A function that prints a time stamp")
print("########################################")
def print_time():
    print("Task completed")
    print(datetime.now())
    print()

first_name = "Yaron"
print(first_name)
print_time()

for x in range(0, 10):
    print(x)
print_time()

print()

## Passing a parameter to a function
def print_time_param(param):
    print(param)
    print(datetime.now())
    print()

print_time_param(first_name)

for x in range(0, 10):
    print(x)
print_time_param("Loop")

print()

## Returning a parameter
def function_return(param):
    return param[0]

letter = function_return(first_name)
print(letter)
print()
