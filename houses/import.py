# Get functions from libraries
from sys import argv, exit
from cs50 import SQL
import sys
import csv

# Initialize variables
db = SQL("sqlite:///students.db")

# Check command-line argument
if len(sys.argv) != 2:
    print("Usage: python import.py characters.csv")
    sys.exit(1)
with open(sys.argv[1], "r") as characters:
    reader = csv.DictReader(characters)
    # Scan through rows in csv file
    for row in reader:
        name_list = row["name"].split(" ")
        # Execute according to if middle name is present or not
        if len(name_list) == 2:
            db.execute("INSERT INTO students (first, last, house, birth) VALUES(?, ?, ?, ?)",
                       name_list[0], name_list[1], row["house"], row["birth"])
        elif len(name_list) == 3:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       name_list[0], name_list[1], name_list[2], row["house"], row["birth"])
