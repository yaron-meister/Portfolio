################################################################################
## open
################################################################################
print()
print()
print("########################################")
print("'open' a file from the file system")
print("########################################")
f = open("test.txt", 'r') ## Default open it for READING
print("The name of the file is: " + f.name)
print("The mode of the file is: " + f.mode)
print()

print()
print()
print("########################################")
print("'read' a file from the file system")
print("########################################")
f_contents = f.read()
print("The contents of the file are: ")
print(f_contents)
print()

f.close()
################################################################################

################################################################################
## read-line
################################################################################
print()
print()
f = open("test.txt", 'r')
print("########################################")
print("READ-LINE") ## reads the lines one by one
print("########################################")
f_contents = f.readline()
print("The FIRST line is: ")
print(f_contents)
print()

f_contents = f.readline()
print("The SECOND line is: ")
print(f_contents)
print()

f_contents = f.readline()
print("The THIRD line is: ")
print(f_contents)
print()

f.close()
################################################################################

################################################################################
## read-lines
################################################################################

print()
print()
f = open("test.txt", 'r')
print("########################################")
print("READ-LINES") ## reads all of the lines
print("########################################")
f_contents = f.readlines()
print("All of the lines are: ")
print(f_contents)
print()

f.close()
################################################################################

################################################################################
## As seen up, the readline() reads all the chars at the line including the '\n'
#  To avoid it, it's optional to pass the char that we want to be the last one
#  at the line to the print function (' ' instead of '\n' for example)
################################################################################
print()
print()
f = open("test.txt", 'r')
print("########################################")
print("READ-LINE with a specific end char")
print("########################################")
f_contents = f.readline()
print("The FIRST line is: ")
print(f_contents, end = '')
f_contents = f.readline()
print("The SECOND line is: ")
print(f_contents, end = '')
print()

f.close()
################################################################################

################################################################################
## Using a loop with a file
################################################################################
print()
print()
f = open("test.txt", 'r')
print("########################################")
print("Read all lines using a loop")
print("########################################")
for line in f:
    print(line, end = '')
print()

f.close()
################################################################################

################################################################################
## First argument of read() is number of charachters to read
################################################################################
print()
print()
f = open("test.txt", 'r')
print("########################################")
print("Read num of charachters")
print("########################################")
f_contents = f.read(50)
print(f_contents, end = '*')
print()

f.close()
################################################################################

################################################################################
## To know the position of the FILE pointer use 'tell()' function
################################################################################
print()
print()
f = open("test.txt", 'r')
print("########################################")
print("Tell me where is the File pointer")
print("########################################")
f_contents = f.read(50)
print("File pointer is at index: " + str(f.tell()))
print()

f.close()
################################################################################

################################################################################
## To pass the FILE pointer to a desired index, use 'seek()' function
################################################################################
print()
print()
f = open("test.txt", 'r')
print("########################################")
print("Pass the File pointer to a desired index")
print("########################################")

f_contents = f.read(10)
print(f_contents)

f.seek(0)

f_contents = f.read(10)
print(f_contents)

print()

f.close()
################################################################################

################################################################################
## write
################################################################################
print()
print()
f = open("test_write.txt", 'w') ## Write mode 'w'
f.write("1)Test file")

f.close()
################################################################################

################################################################################
## A combination of 'read' and 'write'
################################################################################
print()
print()
rf = open("test.txt", 'r') 
wf = open("test_write.txt", 'w') 

for line in rf:
    wf.write(line)


rf.close()
wf.close()
################################################################################

################################################################################
## Spliting a line (like 'strtok' in cpp)
################################################################################
print()
print()
rf = open("test.txt", 'r')  

for line in rf:
    print()
    print(line.split(' ')) ## The default delimiter is ' '

print()
print()
rf.close()
################################################################################

################################################################################
## 'join' - adding a specific char between the splitted sub-strings in a string
################################################################################
print()
print()
rf = open("test.txt", 'r') 

first_line = rf.readline()
splitted_first_line = first_line.split()
','.join(splitted_first_line)
print(splitted_first_line)

print()
print()
rf.close()
