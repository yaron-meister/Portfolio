# To get the current date & time - use datetime lib
from datetime import datetime, timedelta

currnet_date = datetime.now()
# The 'now' function returns a datetime object type
print("Today is: " + str(currnet_date))
print()

print()
print()
print("########################################")
print("USING 'timedelta'")
print("########################################")
one_day = timedelta(days = 1)
yesterday = currnet_date - one_day
print("Yesterday was: " + str(yesterday))
print()

## Formating the date as I want
print()
print()
print("########################################")
print("FORMATING THE DATE MYSELF")
print("########################################")
print("The current formated date is: ")
print(str(currnet_date.day) + "/" +
 str(currnet_date.month) + "/" + str(currnet_date.year))
print()

## Formating the 'datetime' as a 'string'
print()
print()
print("########################################")
print("TURNING A 'datetime' INTO A 'string'")
print("########################################")
print("The current formated date is: ")
birthday = input("Please enter your birthday: (dd/mm/yyyy) ")
birthday_date = datetime.strptime(birthday, "%d/%m/%Y")
print("Birthday: " + str(birthday_date))
print()
