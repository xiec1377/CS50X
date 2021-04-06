# get get_string from cs50 library
from cs50 import get_string

# initialize variables
letters = 0
words = 0
sentences = 0

# prompt user
text = get_string("Text: ")
# scan through input
for i in range(len(text)):
    # check letters
    if text[i].isalpha() == True:
        letters += 1
    # check words
    if text[i] == " " and text[i - 1] not in [".", "!", "?"]:
        words += 1
    # check sentences
    if text[i] in [".", "!", "?"]:
        words += 1
        sentences += 1
# Coleman-Liau formula
L = (100 / float(words)) * float(letters)
S = (100 / float(words)) * float(sentences)
index = round(float(0.0588 * L - 0.296 * S - 15.8))
# output level
if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
