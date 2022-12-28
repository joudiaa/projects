# File: AdvGame.py

"""
This module defines the AdvGame class, which records the information
necessary to play a game.
"""

from AdvRoom import AdvRoom
import re
###########################################################################
# Your job in this assignment is to fill in the definitions of the        #
# methods listed in this file, along with any helper methods you need.    #
# Unless you are implementing extensions, you won't need to add new       #
# public methods (i.e., methods called from other modules), but the       #
# amount of code you need to add is large enough that decomposing it      #
# into helper methods will be essential.                                  #
###########################################################################

# Constants
HELP_TEXT = [
    "Welcome to Adventure!",
    "Somewhere nearby is Colossal Cave, where others have found fortunes in",
    "treasure and gold, though it is rumored that some who enter are never",
    "seen again.  Magic is said to work in the cave.  I will be your eyes",
    "and hands.  Direct me with natural English commands; I don't understand",
    "all of the English language, but I do a pretty good job.",
    "",
    "It's important to remember that cave passages turn a lot, and that",
    "leaving a room to the north does not guarantee entering the next from",
    "the south, although it often works out that way.  You'd best make",
    "yourself a map as you go along.",
    "",
    "Much of my vocabulary describes places and is used to move you there.",
    "To move, try words like IN, OUT, EAST, WEST, NORTH, SOUTH, UP, or DOWN.",
    "I also know about a number of objects hidden within the cave which you",
    "can TAKE or DROP.  To see what objects you're carrying, say INVENTORY.",
    "To reprint the detailed description of where you are, say LOOK.  If you",
    "want to end your adventure, say QUIT."
]

from AdvRoom import AdvRoom
from AdvObject import AdvObject

class AdvGame:

    def __init__(self, prefix):
        """Reads the game data from files with the specified prefix."""
        with open(prefix + "Rooms.txt") as f:
            self._rooms = self.readGame(f)
        self._inventory = []
        with open(prefix + "Objects.txt") as g:
            self._objects = self.readObjects(g)
            for name in self._objects:
                object = self._objects[name]
                if object.getInitialLocation() == "PLAYER":
                    self._inventory.append(object)
                else:
                    room = self._rooms[object.getInitialLocation()]
                    room.addObject(object)

        with open(prefix + "Synonyms.txt") as h:
            self._synonyms ={}
            for line in h:
                index = line.find("=")
                key = line[:index]
                synonym = line[index + 1:]
                self._synonyms[key] = synonym

    def getRoom(self, name):
        # create a new room with the specified short description
        return self._rooms[name]

    def run(self):
        """Plays the adventure game stored in this object."""
        current = "START"
        room = self.getRoom(current)
        for line in room.getLongDescription():
            print(line)
            room.setVisited(True)
        room.getContents()
        ACTIONS = ["HELP", "LOOK", "QUIT", "TAKE", "DROP", "INVENTORY"]
        while current != "EXIT":
            passage = input("> ").strip().upper()
            passage = passage.split()
            for key in self._synonyms:
                if (passage[0] == key):
                    passage[0] = self._synonyms[key].strip().upper()
                    # print(passage[0])
            next = room.getNextRoom(passage[0], self._inventory)
            if (passage[0] == ACTIONS[0]):
                for line in HELP_TEXT:
                    print(line)
            elif(passage[0] == ACTIONS[1]):
                for line in room.getLongDescription():
                    print(line)
                    room.setVisited(False)
            elif (passage[0] == ACTIONS[2]):
                quit()
            elif (passage[0] == ACTIONS[3]):
                name = passage[1]
                name = name
                if (self._objects[name]):
                    room.removeObject(self._objects[name])
                    self._inventory.append(self._objects[name])
            elif (passage[0] == ACTIONS[4]):
                name = passage[1]
                name = name
                if (self._objects[name]):
                    room.addObject(self._objects[name])
                    self._inventory.remove(self._objects[name])

            elif (passage[0] == ACTIONS[5]):
                if (self._inventory == []):
                    print("You are empty-handed")
                else :
                    for object in self._inventory:
                        print("You are carrying " + object.getDescription())
            elif next is None:
                print("I don't understand that word.")
            else:
                current = next
                room = self.getRoom(current)
                if (room.hasBeenVisited()):
                    print(room.getShortDescription())
                else:
                    for line in room.getLongDescription():
                        print(line)
                        room.setVisited(False)
                room.getContents()
                if room.getNextRoom("FORCED", self._inventory):
                    # print long descriptin of room
                    # get the next room
                    next = room.getNextRoom("FORCED", self._inventory)
                    current = next
                    room = self.getRoom(current)
                    for line in room.getLongDescription():
                        print(line)
                        room.setVisited(True)
                    room.getContents()

    @staticmethod
    def readGame(f):
        """Reads the entire course from the data file f."""
        rooms = {}
        while True:
            room = AdvRoom.readRoom(f)
            if room is None: break
            if len(rooms) == 0:
                rooms["START"] = room
            name = room.getName()
            rooms[name] = room
        return rooms

    @staticmethod
    def readObjects(f):
        objects = {}
        while True:
            object = AdvObject.readObject(f)
            if object is None: break
            name = object.getName()
            objects[name] = object
        return objects
