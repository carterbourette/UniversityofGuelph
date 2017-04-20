#!/usr/bin/python

#
#   Carter Bourette
#   0916638
#   cbourette@gmail.com  |  cbourett@mail.uoguelph.ca
#

import sys
import os
import datetime
import tty
import termios
import subprocess

#
#   oneCharInput
#   Get one character without enter key.
#   OUT: (char) character that the user entered.
#
def oneCharInput():
    fd = sys.stdin.fileno()
    old = termios.tcgetattr(fd)
    try:
        tty.setraw(sys.stdin.fileno())
        character = sys.stdin.read(1)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old)
    return character

#
#   getUsername
#   Given the command line arguments build a string of the users name.
#   IN: (String[]) The command line args.
#   OUT: (String) the users name.
#
def getUsername(args):
    username = ""
    if len(args) == 1:
        return False
    for arg in range(1,len(args)):
        if arg > 1:
            username = username + " "
        username = username + str(args[arg])
    return username

#
#   fetchStreams
#   Get a list of all streams for the current user.
#   IN: (String) the name od the current user.
#   OUT: (List).
#
def fetchStreams(username):
    newList = []

    fo = query("Select streamname FROM (Stream INNER JOIN StreamList ON Stream.id = StreamList.stream) INNER JOIN Author ON Author.id = StreamList.author WHERE username = '" + username + "'")
    for line in fo:
        newList.append(line.strip())

    fo.close()
    return newList

#
#   (Static) getDateKey
#
def getDateKey(obj):
    return obj.date

#
#   (Static) getNameKey
#
def getNameKey(obj):
    return obj.sender

#
#   query
#   Run a $system call to get results of a query.
#
def query(query):
    stmt = "./db -query "
    stmt += "\"" + query + "\"" + " > results.txt"

    os.system(stmt)

    fo = open("results.txt", "r")
    return fo


class Message:

    #   Initialize the MessageBoard properties
    def __init__(self, stream):
        self.stream = stream
        self.sender = ""
        self.date = ""
        self.message = ""

    #
    #   Set how the object is represented when printed to screen
    #
    def __repr__(self):
        return self.formatSender() + self.formatDate() + self.message

    def toHTML(self):
        return "<div>" + "<b>Stream: " + self.stream + "</b></div><div>Sender:" + self.sender+ "</div><div>" + self.formatDate() + "</div><hr><div><pre>" + self.message + "</pre></div>"

    #
    #   setProperty
    #   Given a string, create the corresponding msg property.
    #
    def setProperty(self, line):
        splitStr = line.split(":")

        if splitStr[0] == "Sender":
            self.sender = splitStr[1]
        elif splitStr[0] == "Date":
            self.date = splitStr[1]
        else:
            self.message = self.message + line

    #
    #   setProperty
    #   Given a string, create the corresponding msg property.
    #
    def setProperty(self, label, line):
        if label == "stream":
            self.stream = line
        elif label == "sender":
            self.sender = line
        elif label == "date":
            self.date = line
        else:
            self.message = line

    #
    #   formatSender
    #   Prepend the tag on the sender string.
    #
    def formatSender(self):
        return "Stream: " + self.stream + "\nSender:" + self.sender

    #
    #   formatDate
    #   Prepend the tag on the date string.
    #
    def formatDate(self):
        return "Date:" + datetime.datetime.fromtimestamp(float(self.date)).strftime('%c') + "\n"

    #
    #   format
    #   Prepend the tag on the message string.
    #
    def formatMessage(self):
        return self.message

class MessageBoard:

    #   Initialize the MessageBoard properties
    def __init__(self, un):
        self.sortChronologically = True

        self.username = un
        self.stream = ""
        self.msgIndex = 0
        self.postList = None
        self.firstView = True
        self.allIndexList = None

        self.bufferIndex = None
        self.bufferPosition = 0
        self.buffer = None

        self.initialize()

    def __init__(self, un, st):
        self.sortChronologically = True

        self.username = un
        self.stream = st
        self.msgIndex = 0
        self.postList = None
        self.firstView = True
        self.allIndexList = None

        self.bufferIndex = None
        self.bufferPosition = 0
        self.buffer = None

        if self.stream is not "":
            self.openStream()

    #
    #   sort
    #   Toggle Chronological/Alphabetical sort.
    #
    def sort(self):
        if self.sortChronologically:
            #   Do Alphabetical Sort
            self.sortChronologically = False
            self.postList = sorted(self.postList,key = getNameKey)
        else:
            #   Do Chronological Sort
            self.sortChronologically = True
            self.postList = sorted(self.postList,key = getDateKey)
        #   Reset the current buffer
        self.setBuffer()

    def sort(self, var = False):
        if var:
            self.postList = sorted(self.postList,key = getNameKey)
        else:
            self.postList = sorted(self.postList,key = getDateKey)
        #   Reset the current buffer
        self.setBuffer()

    #
    #   markAsRead
    #   Mark the current index as read. (optional) mark all as read
    #
    def markAsRead(self,  markAll = False):
        #   Prep a list of streams
        streamList = []

        if self.stream != "all":
            streamList.append(self.stream)
        else:
            streamList = fetchStreams(self.username)

        #   For each stream in the list
        for stream in streamList:
            if markAll:
                #   Count the total, set the lastMsg val to the count.
                sizeOfList = len(self.postList)
                fo = query("Select StreamList.id FROM (StreamList INNER JOIN Author ON StreamList.author=Author.id) INNER JOIN Stream ON StreamList.stream=Stream.id where username='"+ str(self.username) +"' and streamname='"+ str(stream) +"'")
                for line in fo:
                    query("UPDATE StreamList SET lastMsg="+str(sizeOfList)+" WHERE id="+ str(line))
                fo.close()
            else:
                #   Set the current stream lastMsg index to msgIndex
                fo = query("Select StreamList.id FROM (StreamList INNER JOIN Author ON StreamList.author=Author.id) INNER JOIN Stream ON StreamList.stream=Stream.id where username='"+ str(self.username) +"' and streamname='"+ str(stream) +"'")
                for line in fo:
                    query("Update StreamList SET lastMsg=" + str(self.msgIndex) + " WHERE id=" + str(line) + " and lastMsg < " + str(self.msgIndex))
                fo.close()

    #
    #   openStream
    #   Read stream data files into instance.
    #
    def openStream(self):
        #   Reset to avoid overlap
        self.postList = []
        streamList = []

        #   Determine which streams we are looking at
        if self.stream != "all":
            streamList.append(self.stream)
        else:
            streamList = fetchStreams(self.username)

        #   Open the stream and get the post for each we have selected
        for stream in streamList:
            try:
                if self.stream != 'all':
                    #   Get the last post read by the user
                    res = query("Select lastMsg FROM (Stream INNER JOIN StreamList ON Stream.id = StreamList.stream) INNER JOIN Author ON Author.id = StreamList.author WHERE username = '" + self.username + "'")
                    for value in res:
                        self.msgIndex = int(value.strip())
                        self.bufferPosition = self.msgIndex
                    res.close()
                else:
                    self.msgIndex = 0
                    self.bufferPosition = 0

                #   Get posts
                proc = query("Select streamname, username, postdate, message from (Post INNER JOIN Author ON Post.author = Author.id) INNER JOIN Stream ON Post.stream = Stream.id WHERE streamname = '" + stream + "'")
                for post in proc:
                    splitter = post.split("\t")
                    if len(splitter) >= 4:
                         msg = Message(stream)

                         msg.setProperty("stream", splitter[0])
                         msg.setProperty("sender", splitter[1])
                         msg.setProperty("date", splitter[2])
                         msg.setProperty("message", splitter[3])
                         self.postList.append(msg)
                    else:
                         msg = self.postList[-1]
                         msg.message += splitter[0]
                proc.close()

            except Exception as e:
                print str(e)
                print "Unable to open '" + stream + "' stream. Check the spelling or create a new stream in addauthor."
                sys.exit(1)

    #
    #   getStream
    #   Fetch the stream the user would like to view
    #
    def getStream(self):
        sList = fetchStreams(self.username)
        if len(sList) > 0:
            for stream in sList:
                print stream,
            print "all"
            self.stream = raw_input("- ")
        else:
            print "This user is not subscribed to any streams. To subscribe see addauthor."
            sys.exit(1)

    #
    #   initialize
    #   Initialize the properties needed by the class.
    #
    def initialize(self):
        self.firstView = True
        self.getStream()
        self.openStream()
        self.setBuffer()

    #
    #   displayMessageBoard
    #   Display the message board and user options.
    #
    def displayMessageBoard(self):
        self.printBuffer()
        print "Page Up  Page Down  O -order toggle   M -mark all   S -stream   C -check all ",
        #   Get one character input

        sequence = ""
        while(1):
            key = oneCharInput()
            if key == '\x1b' or ((key == '[' or key == '5' or key == '6') and sequence!=''):
                sequence = sequence + key
            else:
                if key != '':
                    break
        sequence = sequence + key

        #   Clear the screen
        os.system('clear')

        #   Left  - \x1b[D
        #   Right - \x1b[C
        #   Pg up or up arrow
        if sequence =='\x1b[A' or sequence == '\x1b[5~':
            self.bufferPosition = int(self.bufferPosition) - 4
        #   Pg down or down arrow
        elif sequence=='\x1b[B' or sequence =='\x1b[6~':
            self.bufferPosition = int(self.bufferPosition) + 4
        else:
            if sequence == 'o' or sequence == 'O':
                self.sort()
            elif sequence == 'm' or sequence == 'M':
                self.markAsRead(True)
            elif sequence == 's' or sequence == 'S':
                self.initialize()
            elif sequence == 'c' or sequence == 'C':
                listCpy = self.postList
                self.openStream()
                self.setBuffer()
                if listCpy != self.postList:
                    self.firstView = True
            elif sequence == 'q' or sequence == 'Q':
                sys.exit(0)
            #else:
                #print "Try again"

        self.displayMessageBoard()

    #
    #   setBuffer
    #   Set the current buffer, make sure no line is longer than 80 cols
    #
    def setBuffer(self):
        stringList = []
        buffIndex = []
        self.allIndexList = []
        streamType = ""

        count = 0

        for msg in self.postList:

            if msg.stream != streamType:
                streamType = msg.stream
                self.allIndexList.append(count)

            cols = 80
            string = ""
            buffIndex.append(count)
            #   For each message sender
            for character in msg.formatSender():
                if cols == 0 or character == '\n':
                    stringList.append(string.strip("\n"))
                    count = count + 1
                    string = ""
                    cols = 80
                string = string + character
                cols = cols - 1
            if string.strip("\n") != "":
                stringList.append(string.strip("\n"))
                count = count + 1

            cols = 80
            string = ""
            #   For each message date
            for character in msg.formatDate():
                if cols == 0 or character == '\n':
                    stringList.append(string.strip("\n"))
                    count = count + 1
                    string = ""
                    cols = 80
                string = string + character
                cols = cols - 1
            if string.strip("\n") != "":
                stringList.append(string.strip("\n"))
                count = count + 1

            cols = 80
            string = ""
            #   For each message
            for character in msg.formatMessage():
                if cols == 0 or character == '\n':
                    stringList.append(string.strip("\n"))
                    count = count + 1
                    string = ""
                    cols = 80
                string = string + character
                cols = cols - 1
            if string.strip("\n") != "":
                stringList.append(string.strip("\n"))
                count = count + 1
            stringList.append("")
            count = count + 1

        self.bufferIndex = buffIndex
        self.buffer = stringList

    #
    #   printBuffer
    #   Print the 80x24 window at the current viewing index.
    #
    def printBuffer(self):
        rows = 23
        currentBufferIndex = 0

        if len(self.buffer) == 0:
            for i in range(0, rows):
                print ""
            return

        #   Determine the CBI
        if self.firstView:
            #   CBI is the msg position from the file
            if self.msgIndex > len(self.bufferIndex) - 1:
                self.msgIndex = len(self.bufferIndex) - 1
            currentBufferIndex = self.bufferIndex[self.msgIndex]
            self.firstView = False
        else:
            #   CBI is the buffer position
            currentBufferIndex = self.bufferPosition

        if currentBufferIndex < 0:
            currentBufferIndex = 0
            self.bufferPosition = currentBufferIndex
        elif currentBufferIndex > self.bufferIndex[-1]:
            currentBufferIndex = self.bufferIndex[-1]
            self.bufferPosition = currentBufferIndex

        '''print "msg index " + str(self.msgIndex)
        print "buf pos " + str(self.bufferPosition)
        print "currentBufferIndex " + str(currentBufferIndex)
        print self.bufferIndex
        print self.buffer
        print "all",
        print self.allIndexList'''

        #   Print the buffer from the last msg to MAX_ROWS or end of buffer
        for index in range(currentBufferIndex,len(self.buffer)):
            if rows == 0:
                break
            print self.buffer[index]
            rows = rows - 1

        #   Print blank space if there is any room left
        for i in range(0, rows):
            print ""

        #   Set new message index
        for post in range(0,len(self.bufferIndex)):
            if self.bufferIndex[post] < index:
                if post + 1 > int(self.msgIndex):
                    if self.stream != 'all':
                        self.msgIndex = post + 1
                        #self.markAsRead()
                    else:
                        pass
                        #self.markAsRead(True)

        self.bufferPosition = currentBufferIndex

#
#   Main Stuff
#
if __name__ == "__main__":
    #   Get the users name from commandline
    username = getUsername(sys.argv)
    if username == False:
        print "Please enter a user name."
    else:
        #   Create a MessageBoard object
        myBoard = MessageBoard(username)
        myBoard.displayMessageBoard()
