## if/else
print()
print("########################################")
print("'if/else'")
print("########################################")
price = 2

if price > 1:
    tax = 0.16
else:
    tax = 0

print("Tax is: " + str(tax))
print()

## 'in' & 'or' operators
print()
print("########################################")
print("'in' & 'or' operators")
print("########################################")
country = "ISRAEL"

if country.lower() in("israel", "usa", "uk"):
    print("You can speak English")
elif country.lower() == "russia" or country.lower() == "italia":
    print("Nobody will understand you!")

print()

