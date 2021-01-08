firstName = "Yaron"
secondName = "Meister"

# The '+' operator with strings gives the ability to concatanate
print("Hello, my name is: ")
print(firstName + " " + secondName)

## The next followings are the abilities of:
sentence = "hello WoRlD, you ARE beAUtiFUL"
# Turn a sentence to UPPER CASE
print("*** UPPER CASE *** " + sentence.upper())
# Turn a sentence to LOWER CASE
print("*** LOWER CASE *** " + sentence.lower())
# Capitalize a sentence
print("*** CAPITALIZE *** " + sentence.capitalize())
# Count sub-str
print("*** COUNT SUB_STR: ***")
print(sentence.count("ello"))

print()
print()
print("########################################")
print("CONCATENATING WITH STRING's FUNCTIONS")
print("########################################")
first_name = input("Please enter first name: ")
second_name = input("Please enter second name: ")
print("Hello " + first_name.capitalize() + " " + second_name.capitalize())

print()
print()
print("########################################")
print("FORMATING WITH FIRST METHOD")
print("########################################")

## Formating (like 'printf' in cpp)
# First method:
output = "Hello, {} {}".format(first_name, second_name)
print(output)

print()
print()
print("########################################")
print("FORMATING WITH SECOND METHOD")
print("########################################")

# Second method:
output = "Hello, {1} {0}".format(first_name, second_name)
print(output)

print()
print()
print("########################################")
print("FORMATING WITH THIRD METHOD")
print("########################################")


# Third method:
output = f"Hello, {first_name} {second_name}"
print(output)
print()