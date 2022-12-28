# File: AdvRoom.py

"""
This module is responsible for modeling a single room in Adventure.
"""

###########################################################################
# Your job for Milestone #1 is to fill in the definitions of the         #
# methods listed in this file, along with any helper methods you need.    #
# The public methods shown in this file are the ones you need for         #
# Milestone #1.  You will need to add other public methods for later      #
# milestones, as described in the handout.  For Milestone #7, you will    #
# need to move the getNextRoom method into the AdvGame class and replace  #
# it with a getPassages method that returns the dictionary of passages.   #
###########################################################################

# Constants

MARKER = "-----"

import re

class AdvRoom:

    def __init__(self, name, shortdesc, longdesc, passages,visited):
        """Creates a new room with the specified attributes."""
        self._name = name
        self._shortdesc = shortdesc
        self._longdesc = longdesc
        self._passages = passages
        self._visited = visited
        self._objects = []

    def getName(self):
        """Returns the name of this room."""
        return self._name

    def getShortDescription(self):
        """Returns a one-line short description of this room."""
        return self._shortdesc

    def getLongDescription(self):
        """Returns the list of lines describing this room."""
        return self._longdesc

    def getNextRoom(self, verb, inventory):
        """Returns the name of the destination room after applying verb."""
        """Looks up the text entered to find the next room."""
        passage = self._passages
        for tuple in passage:
            room_name = tuple[0] #down or south
            room_value_key = tuple[1] # EndOfRoad, or InsideBuilding/LAMP
            if '/' in room_value_key:
                 split_list = room_value_key.split('/')
                 key = split_list[1]
                 if key in inventory:
                     if room_name == verb:
                        return split_list[0]
            else:
                if room_name == verb:
                    return room_value_key

       # fix syntax from dict to tuple list
            if '*' in room_name:
                next = room_value_key
                return next
            # next = self._passages.get("*", None) # * IS LIKE A CATCH AL
            # return next

    # set a method that checks if room has been already visited
    def setVisited(self, bool):
        # check if room has been visited or not
        self._visited = bool


    def hasBeenVisited(self):
        # do something when we find that it has been visited
        # print shortdesc instead of longdesc
        return self._visited

    def addObject(self, object):
        self._objects.append(object)

    def removeObject(self, object):
        # print(self._objects)
        self._objects.remove(object)


    def containsObject(self, object):
        if (object in self._objects):
            return True
        else:
            return False

    def getContents(self):
        for object in self._objects:
            if (object in self._objects):
                print("There's a " + object.getDescription())


    def getPassages(self, passages_dict):
        passage = [(k, v) for k, v in passages_dict.items()]
        return passage

    @staticmethod
    def readRoom(f):
        """Reads a room from the data file."""
        name = f.readline().rstrip()
        if name == "":
            return None
        shortdesc = f.readline().rstrip()
        longdesc = []
        while True:
            line = f.readline().rstrip()
            if line == MARKER: break
            longdesc.append(line)
        passages = []
        while True:
            line = f.readline().rstrip()
            if line == "": break
            colon = line.find(":")
            if colon == -1:
                raise ValueError("Missing colon in " + line)
            verb = line[:colon].strip().upper() # verb is the key
            next = line[colon + 1:].strip()
            # next is the value
            tupes = (verb, next)
            passages.append(tupes)
            # passages[verb] = next
        visited = False
        return AdvRoom(name, shortdesc, longdesc, passages, visited)


