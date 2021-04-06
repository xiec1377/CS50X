# Get functions from libraries
from sys import argv, exit
import csv
import sys

# Check command-line argument
if len(sys.argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    sys.exit(1)
else:
    # Open CSV file
    with open(sys.argv[1], "r") as file:
        freader = list(csv.reader(file))
        # Initialize list to match data in CSV files
        match_seq = [0] * (len(freader[0]))
        # Open DNA sequence
        with open(sys.argv[2], "r") as seq:
            sreader = seq.read()
            # Scan through first row of CSV file
            for i in range(1, len(freader[0])):
                # Counter for amount of times STR repeats in a row
                counter = 0
                # Find greatest count of STR repeats
                greatest = 0
                a = 0
                b = 0
                # STR to find
                STR = freader[0][i]
                # Scan through DNA sequence
                for j in range(len(sreader) - 1):
                    # Scan through sequence one base pair over if no STR previously
                    if counter == 0:
                        current = sreader[j: len(STR) + j]
                    # Scan through sequence for another STR
                    elif counter > 0:
                        a = j + (len(STR) * counter) - counter
                        b = j + (len(STR) * counter) + len(STR) - counter
                        current = sreader[a: b]
                    if current != STR:
                        counter = 0
                        # Continue through for loop
                        continue
                    elif current == STR:
                        counter += 1
                        # Set greatest to counter of STR repeats
                        if greatest <= counter:
                            greatest = counter
                            continue
                # Scan through rows of CSV file, excluding first row
                for k in range(1, len(freader)):
                    if int(freader[k][i]) == greatest:
                        # Append greatest STR repeat into list
                        match_seq[i] = str(greatest)
                    # Checks if match list matches the sequences in CSV file
                    if match_seq[1:len(match_seq)] == freader[k][1:len(match_seq)]:
                        # Print name if sequence belongs to person
                        print(f"{freader[k][0]}")
                        sys.exit(0)
            # If no sequence match
            print("No match")
