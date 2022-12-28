# File: GeherateRandomSentences.py
# --------------------------------
# This file exports a program that reads in a grammar file and
# then prints three randomly generated sentences
from random import choice
import os
import re

#I got a sick 1-late-day extension from Johnathan :)
def readGrammar(filename):
    # open the grammar file and store as list
    with open(filename) as f:
        lst = list(f)
        return lst


def readFilePart(grammar, name):
    # get start index of <bracket>
    # note the \n is very important for making sure we are in a "file part"
    # file part is defined as
    # (i.e. empty line)
    # <name>\n number of elements in list\n list element 1 \n ...]
    name += "\n"

    # .index function verbose
    #idx = grammar.index(name)
    idx = -1
    for i, el in enumerate(grammar):
        if el == name and grammar[i - 1] == "\n":
            idx = i
            break

    # extract list length
    num = int(grammar[idx + 1])

    # extract list
    lst = grammar[idx + 2: idx + 2 + num]
    return lst


def generateRandomSentence(grammar):
    # read start template for the given file
    grammar.insert(0, "\n")
    templates = readFilePart(grammar, "<start>")

    # helper variable for building return string
    s = ""

    # iterate on each template
    for template in templates:

        # keep iterating until we have subsituted all <brackets>
        while "<" in template:
            # extract each <bracket> in the template for subsititution
            rgx = re.compile(r'(<[A-Za-z0-9]*>)')
            brackets = rgx.findall(template)

            for bracket in brackets:
                # iterate on each
                lst = readFilePart(grammar, bracket)
                rnd = choice(lst)
                template = template.replace(bracket, rnd.strip())
                #print(template)

        # append to return string
        s += template
        s += " "

    return s


def GenerateRandomSentences():
    # ignore file chooser
    #add file chooser
    fname = "rejection"
    filename = f"{os.getcwd()}/grammars/{fname}.g"

    # read file as list
    grammar = readGrammar(filename)

    # generate multiple rands
    for i in range(3):
        print(generateRandomSentence(grammar))


if __name__ == "__main__":
    GenerateRandomSentences()
