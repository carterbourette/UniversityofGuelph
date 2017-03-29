/**
 * Carter Bourette
 * 0916638
 * cbourette@gmail.com  |  cbourett@mail.uoguelph.ca
 *
 * Assignment 2
 * Feb 17, 2017
 * Software System Integration and Development
 * Message Management and Viewer.
 *
 **/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "stream.h"
#include "stringy.h"


class PostEntry {
    char* username;
    char* streamName;
    char* data;
    char* text;

    /**
     * submitPost
     * Calls the update stream function.
     *
     * IN: Current instance.
     * RETURN: NONE.
     *
     **/
    void submitPost(UserPost *p) {
        updateStream(p);
        printf("The message was successfully added to the %s stream.\n", p->streamName);
        freeEntry(p);
    }

    /**
     * formatEntry
     * Format current date and time.
     *
     * IN: NONE.
     * RETURN: (char*) the current date and time.
     * NOTE: caller must free.
     *
     **/
    char* getTimeDate() {
        char output[70];
        long int currentTime = time(NULL);

        sprintf(output, "%ld\n", currentTime);
        return stringify(output);
    }

    /**
     * formatEntry
     * Create the struct used by updateStream.
     *
     * IN: (PostEntry) the class instance.
     * RETURN: (UserPost*) the structure used by updateStream.
     * NOTE: See freeEntry()
     *
     **/
    void formatEntry() {
        UserPost ptr;
        ptr.username = instance.username;
        ptr.streamName = instance.streamName;
        ptr.data = PostEntrygetTimeDate(instance);
        ptr.text = instance.text;

        PostEntrysubmitPostU(instance,&ptr);
    }

};

int main(int argc, char* argv[]) {
    if (argc < 2) printError("Invalid arguments: ./post <author>", 1);

    /* Instantiate class */
    class PostEntry Post;
    char* input, *nm;
    char name[100];
    int i = 1;

    /* Get the username, regardless how many args */
    strcpy(name,"");
    for (; i < argc; i++) {
        strcat(name, argv[i]);
        if (i + 1 < argc) strcat(name, " ");
    }
    nm = stringify(name);
    Post.username = nm;

    /* Get stream name */
    input = readTemp(1);
    Post.streamName = input;

    /* Verify that the user is in the stream file */
    if (verifyUser(nm,input)) {
        /* Get post text */
        input = readTemp(0);
        Post.text = input;

        /* Submit the post */
        Post.formatEntry(Post);
    } else {
        printf("This user is not in the %s stream. You can subscribe to this stream using addauthor\n", input);
        free(nm);
        free(input);
    }
    removeTemp();

    return 0;
}
