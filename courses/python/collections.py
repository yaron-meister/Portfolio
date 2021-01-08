## Lists
print()
print()
print("########################################")
print("LISTS")
print("########################################")

names = ["Yaron", "Meister", "May", "Mika"]
print("The list of names is: ")
print(names)
print()
print("The second name is: ")
print(names[1])
print()

## Adding an item to the end of the list
print()
print()
print("########################################")
print("########################################")

names.append("Haifa")
print(names)
print()

## Arrays (must import arrays lib)
from array import array
print()
print()
print("########################################")
print("ARRAYS")
print("########################################")

arr = array('d')
arr.append(55)
print(arr)
print()

#### 
# The difference between array and lists is
# An array stores one type 'data type'
# A list can store a combination of 'data types' together
###

## The length of a list
print()
print()
print("########################################")
print("List's length")
print("########################################")
print()
print("The length of the list is: " + str(len(names)))
print()

## Inserting a member to a list before the index specified
print()
print()
print("########################################")
print("Inserting a member")
print("########################################")
print()
names.insert(0, "Python")
print("The list is: ")
print(names)
print()

## Sorting a list
print()
print()
print("########################################")
print("Sorting a list")
print("########################################")
print()
print("The sorted list is: ")
names.sort()
print(names)
print()

## Creating a sub-list out of a list
print()
print()
print("########################################")
print("A sub-list")
print("########################################")
print()
print("The sub-list is: ")
sub_list = names[1:3] ## Indexes are including first, excluding second
print(sub_list)
print()
