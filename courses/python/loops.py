## 'for' loop
print()
print("########################################")
print("'for' loop")
print("########################################")
for names in ["Yaron", "May", "Mika"]:
    print(names)
print()

## 'for' loop using 'range' function
print()
print("########################################")
print("'for' loop using 'range' function")
print("########################################")
for index in range(0,3): # including the first, excloding the second
    print(index)
print()

## 'while' loop
print()
print("########################################")
print("'while' loop")
print("########################################")
index = 0

while index < len(names): # len() of names is the length of the current name
    print(index)
    index = index + 1
    
print()

