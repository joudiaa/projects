# File: Reassemble.py
# -------------------
# This file exports a program that reads in a large number
# of text fragments from a file you choose, and then reconstructs
# the original text so it can be printed out.

from filechooser import chooseInputFile
import os
import re
from difflib import SequenceMatcher

def extractFragments(filename):
   with open (filename, 'r') as p:
      lst = list(p) #convert text file into a list

   curls = re.findall(r'{(.+?)}', str(lst))  # find the words in brackets
   # so now curls is a list of the words extracted

   return curls # placeholder for code that opens and parses the file

def reconstruct(fragments):
   fname = "allswell_frags"
   filename = f"{os.getcwd()}/reassemble-files/{fname}"
   fragments = extractFragments(filename) #which is our curls list
   max_overlap = -1
   max_merged = ""
   print(fragments)
   num_fragments = len(fragments)
   while len(fragments) > 1:
      for i in range(num_fragments):
         for j in range(num_fragments):
            if i == j:
               continue
            else:
               #there is a bug here that jerry and I couldn't for the life of us solve it because
               #the code seems correct but it keeps giving us an error :(
               overlap, merged = findscommonStuff(fragments[i], fragments[j])
               if overlap > max_overlap:
                  foundi, foundj = i, j
                  max_merged = merged
                  max_overlap = overlap
      print(foundi, foundj)
      # fragments.pop(i)
      # fragments.pop(j)
      # fragments.append(max_merged)
      # num_fragments -= 1
      fragments[foundi] = max_merged
      fragments[foundj] = fragments[len(fragments) - 1]
      fragments.pop(len(fragments) - 1)
      print(fragments)
   return fragments[0]


def findscommonStuff(str1, str2):
   shortest = str2 if len(str2) < len(str1) else str1
   longest = str1 if len(str1) > len(str2) else str2
   # print("longest " + longest)
   # print("shortest " + shortest)

   if shortest in longest:
      print("containment!")
      return len(shortest), longest

   length = len(shortest)
   for i in range(1, length):
      #print(i)
      # i += 1
      if shortest[0:length - i] == longest[-(length - i):]:
         # print("comparing two substrings")
         overlap = longest[-(length - i):]
         # print(overlap)
         prefix = longest[:-(length - i)]
         #print(prefix)
         merged = prefix + overlap + shortest[length - i:]
         # print("merged: " + merged)
         return len(overlap), merged

   return 0, str1 + str2 # never any overlap, so 0 overlap and concatenate

def Reassemble():
   fname = "allswell_frags"
   filename = f"{os.getcwd()}/reassemble-files/{fname}"
   #filename = chooseInputFile("reassemble-files")
   if filename == "":
      print("User canceled file selection. Quitting!")
      return
   fragments = extractFragments(filename)
   if fragments == None:
      print("File didn't respect reassemble file format. Quitting!")
      return
   #print(fragments)
   len, reconstruction = reconstruct(fragments)
   print(reconstruction)

if __name__ == "__main__":
   Reassemble()
   #reconstruct([])
   #findscommonStuff('all is well that en', 't ends well')
