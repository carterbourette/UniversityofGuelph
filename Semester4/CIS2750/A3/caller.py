#!/usr/bin/python

import view
import sys
import os

if __name__ == "__main__":
    args = sys.argv

    #   Quit if we dont have the information we need
    if len(args) == 1:
        print "Format: ./caller _function_ _stream_ _msg_"
        exit(1)

    #   View message <username> <stream> <msg>
    if args[1] == "view":
        if len(args) < 3:
            exit(1)
        myBoard = view.MessageBoard(args[2], args[3])
        print "<div class=\"card\">"
        if len(args) == 5:
            print myBoard.postList[int(args[4])].toHTML()
        else:
            if myBoard.msgIndex == len(myBoard.postList):
                print myBoard.postList[myBoard.msgIndex-1].toHTML()
            else:
                print myBoard.postList[myBoard.msgIndex].toHTML()
                myBoard.msgIndex += 1
                myBoard.markAsRead()
        print "</div>"

    elif args[1] == "paginate":
        if len(args) < 3:
            exit(1)
        myBoard = view.MessageBoard(args[2], args[3])
        if len(args) > 4:
            curr = int(args[4])
        elif myBoard.msgIndex == 0 and len(myBoard.postList) > 1:
            curr = myBoard.msgIndex + 1
        elif myBoard.msgIndex > len(myBoard.postList):
            curr = myBoard.msgIndex - 1
        else:
            curr = myBoard.msgIndex - 1

        last = curr - 1
        nxt = curr + 1

        if nxt >=  len(myBoard.postList)-1:
            nxt = len(myBoard.postList)-1
        if last < 0:
            last = 0

        print "<form action=\"view.php?view=stream.wpml&userid=" + myBoard.username + "&stream=" + args[3] + "&msg="+ str(last) +"\" method=\"post\"><button>Prev</button></form>"
        if len(args) < 5:
            if myBoard.msgIndex + 1 > len(myBoard.postList):
                print str(myBoard.msgIndex) + "/" + str(len(myBoard.postList))
            else:
                print str(myBoard.msgIndex + 1) + "/" + str(len(myBoard.postList))
        else:
            print str(int(args[4]) + 1) + "/" + str(len(myBoard.postList))

        print "<form action=\"view.php?view=stream.wpml&userid=" + myBoard.username + "&stream=" + args[3] + "&msg="+ str(nxt)+"\" method=\"post\"><button>Next</button></form>"


    #   Mark as read <username> <stream> <post>
    elif args[1] == "mark":
        myBoard = view.MessageBoard(args[2], "all")
        myBoard.markAsRead(True)

    #   List streams <username>
    elif args[1] == "list":
        if len(args) < 2:
            exit(1)
        myBoard = view.MessageBoard(args[2], "")
        for item in view.fetchStreams(myBoard.username):
            print item

    #   Check <username> <stream>
    elif args[1] == "check":
        myBoard = view.MessageBoard(args[2], args[3])
        if myBoard.msgIndex >= len(myBoard.postList):
            print str(myBoard.msgIndex-1) + "/" + str(len(myBoard.postList)-1)
        else:
            print str(myBoard.msgIndex) + "/" + str(len(myBoard.postList)-1)
    #   Sort <username> <stream/all>
    elif args[1] == "sort":
        if len(args) < 3: #all
            myBoard.sort()
            print myBoard.postList[myBoard.msgIndex]
        else:
            print myBoard.postList[int(args[4])]
    #   Format <username>
    elif args[1] == "format-list":
        if len(args) < 2:
            exit(1)
        myBoard = view.MessageBoard(args[2], "")
        print "<a href=\"view.php?userid=" + myBoard.username + "&stream=all\">all</a>"
        for item in view.fetchStreams(myBoard.username):
            print "<a href=\"view.php?userid=" + myBoard.username + "&stream=" + item + "\">" + item + "</a>"
        print "or <a href=\"view.php?userid=" + myBoard.username + "\">clear</a>"

    elif args[1] == "format-options":
        myBoard = view.MessageBoard(args[2], "")
        for item in view.fetchStreams(myBoard.username):
            if len(args) >= 4 and args[3] == item:
                print "<option selected value=\"" + item + "\">" + item + "</option>"
            else:
                print "<option value=\"" + item + "\">" + item + "</option>"

    elif args[1] == "welcome":
        if len(args) < 3:
            exit(1)
        print "<span style=\"float:right; font-weight:600;\">Welcome " + args[2] + "!</span>"
