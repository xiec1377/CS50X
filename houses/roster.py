# Get functions from libraries
from sys import argv, exit
from cs50 import SQL
import sys
import csv

# Initialize variables
db = SQL("sqlite:///students.db")
houses = db.execute("SELECT first, middle, last, birth FROM students WHERE house = (?) ORDER BY last, first;", sys.argv[1])
house_names = ["Gryffindor", "Hufflepuff", "Ravenclaw", "Slytherin"]

# Check command-line argument
if len(sys.argv) == 2:
    if sys.argv[1] not in house_names:
        print("Usage: invalid house")
    else:
        houses
else:
    print("Usage: python import.py characters.csv")
    sys.exit(1)

# Print rows in houses whether middle name is present or not
for row in houses:
    if row["middle"]:
        print(row["first"] + " " + row["middle"] + " " + row["last"] + ", born " + str(row["birth"]))
    else:
        print(row["first"] + " " + row["last"] + ", born " + str(row["birth"]))
