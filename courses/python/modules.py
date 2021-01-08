## A module is a file with forward declarations (like a header)

## Importing a module
# Import a module as a namespace
import functions_for_modules

print()
functions_for_modules.print_yaron()
print()

# Import specific items into the current namespace
from functions_for_modules import print_may

print()
print_may()
print()

# Import all to the current namespace
from functions_for_modules import *

print()
print_mika()
print()


################################################################
##      A 'Package' is a published collection of modules      ##
##            Look for the "Python Package Index"             ##
################################################################