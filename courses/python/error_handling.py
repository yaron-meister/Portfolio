## Using 'try' 'except'
x = 12
y = 0

print()
try:
    print(x / y)
except ZeroDivisionError as e:
    print("ERROR IN DIVISION")
## 'finally' is going to run anyway
finally:
    print("END OF ERROR HANDLING")
print()