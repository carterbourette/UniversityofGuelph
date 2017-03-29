/**
 * Carter Bourette
 * 0916638
 * cbourette@gmail.com  |  cbourett@mail.uoguelph.ca
 *
 * Assignment 3
 * March 17, 2017
 * Software System Integration and Development
 * Message Management and Viewer meets the web.
 *
 **/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parse.h"
#include "stringy.h"
#define DEBUG 0

/**
 * getType
 * Return the type of html element.
 *
 * IN: (char) HTML representation.
 * RETURN: (Type) the type of element.
 *
 **/
Type getType(char tag) {
     Type type;
     switch(tag) {
         case 'h':
             type = Heading;
             break;
        case 'b':
            type = Button;
            break;
        case 'd':
            type = HorizontalRule;
            break;
        case 'e':
            type = Executable;
            break;
        case 'i':
            type = Input;
            break;
        case 'l':
            type = Link;
            break;
        case 'p':
            type = Picture;
            break;
        case 'r':
            type = Radio;
            break;
        case 't':
            type = Text;
            break;
        case 'c':
            type = CSS;
            break;
        case 'z':
            type = LineBreak;
            break;
        default:
            type = Undefined;
     } return type;
 }

/**
* initElement
* Allocate memory for a new element.
*
* IN: NONE.
* RETURN: (Element*).
*
**/
Element* initElement() {
     Element* e = (Element*)malloc(sizeof(Element));
     if (e == NULL) printError("Unable to allocate memory!", 1);
     e->name = NULL;  e->link = NULL;
     e->size = NULL;  e->text = NULL;
     e->value = NULL; e->file = NULL;
     e->exe = NULL;   e->formCreated = 0;
     e->tag = NULL;   e->closeTag = 1;
     e->buffer = newBuffer(75);
     return e;
}

/**
* getDefault
* Takes the type of HTML element and returns a default element.
*
* IN: (Type) The type of element
* RETURN: (Element*) default element.
*
**/
Element* getDefault(Type type) {
    Element* e = initElement();
    e->elementType = type;
    switch(type) {
         case CSS:
            e->tag = stringify("link");
            e->closeTag = 0;
            break;
         case LineBreak:
            e->tag = stringify("br");
            e->closeTag = 0;
            break;
         case Heading:
             e->size = stringify("3");
             e->text = stringify("HEADING");
             e->tag = stringify("h");
             break;
         case Button:
            e->tag = stringify("button");
            break;
         case HorizontalRule:
            e->tag = stringify("hr");
            e->closeTag = 0;
            break;
         case Executable:
            e->closeTag = 0;
            break;
         case Input:
            e->tag = stringify("input");
            e->closeTag = 0;
           break;
         case Radio:
            e->tag = stringify("input");
            e->closeTag = 0;
            break;
         case Link:
             e->text = stringify("link");
             e->tag = stringify("a");
             break;
         case Picture:
             e->size = stringify("100x100");
             e->tag = stringify("img");
             e->closeTag = 0;
             break;
         case Text:
             e->text = stringify("Default text");
             e->tag = stringify("span");
             break;
         default:
            break;
    } return e;
}

/**
 * createTag
 * Creates an html tag.
 *
 * IN: (Element*) the element.
 * RETURN: (char*).
 *
 **/
char* createTag(Element* e) {
    char html[1999];
    Split* split;
    int i;
    strcpy(html, "\t\t");

    if (e->elementType == Input || e->elementType == Radio) {
        if (e->formCreated == 0) {
            strcat(html,"<form action=\"");
            if (e->exe) strcat(html,e->exe);
            strcat(html,"\" method=\"post\">\n\t\t");
            e->formCreated = 1;
        }
        if (e->elementType == Radio) {
            if (e->value) strcat(html,e->value);
        } else {
            if(e->text) strcat(html,e->text);
        }
    } else if (e->elementType == Button) {
        strcat(html, "<form action=\"");
        if (e->link) strcat(html,e->link);
        strcat(html,"\" method=\"post\">");
    }

    /* Get the tag name */
    if (e->elementType != Executable) {
        strcat(html, "<");
        if(e->tag) strcat(html,e->tag);
    }

    /* Copy the attributes */
    switch(e->elementType) {
        case Executable:
            strcat(html,"PHPCALL_");
            if (e->value) { /* There are parameters */
                strcat(html,"$str = \"\";");
                split = newSplit(e->value,",");
                for (i = 0; i < split->rows; i++) {
                    strcat(html,"$val = @");
                    strcat(html,split->substring[i]);
                    strcat(html,";eval('$str .= \"$val\" . \" \";');");
                }
                freeSplit(split);
            }
            strcat(html,"echo shell_exec(\"./");
            if (e->exe) strcat(html,e->exe);
            if (e->value) strcat(html," $str");
            strcat(html,"\");_PHPCALL");
            break;
        case Heading:
            strcat(html,e->size);
            break;
        case Input:
            strcat(html," name=\"");
            if (e->name) strcat(html,e->name);
            strcat(html,"\"");
            strcat(html," value=\"");
            if (e->value) strcat(html,e->value);
            strcat(html,"\" ");
            break;
        case Link:
            strcat(html," href=\"");
            if (e->link) strcat(html,e->link);
            strcat(html,"\" ");
            break;
        case Picture:
            strcat(html, " src=\"");
            if (e->link) strcat(html,e->link);
            strcat(html, "\"");
            split = newSplit(e->size,"x");
            strcat(html, " width=\"");
            strcat(html, split->substring[0]);
            strcat(html, "\"");
            strcat(html, " height=\"");
            strcat(html, split->substring[1]);
            strcat(html, "\" ");
            freeSplit(split);
            break;
        case Radio:
            strcat(html," type=\"radio\"");
            strcat(html," name=\"");
            if (e->name) strcat(html,e->name);
            strcat(html,"\"");
            strcat(html," value=\"");
            if (e->value) strcat(html,e->value);
            strcat(html,"\" ");
        default:
            break;
    }
    /* append any other tags added */
    if (e->elementType != Executable && e->buffer->currentIndex !=0) {
        strcat(html," ");
        strcat(html,e->buffer->buffer);
        e->buffer->currentIndex = 0;
        e->buffer->buffer[0] = '\0';
    }
    /* If there is a close tag, Add any text to interior tag */
    if (e->closeTag) {
        strcat(html, ">");
        /* Append interior text by tag */
        switch(e->elementType) {
            case Button:
                if (e->name) strcat(html,e->name);
                break;
            case Heading:
                if(e->text) strcat(html,e->text);
                break;
            case Link:
                if(e->text) strcat(html,e->text);
                break;
            case Text:
                if(e->text) strcat(html,e->text);
                break;
            default:
                break;
        }
        /* Close Tag */
        strcat(html,"</");
        if (e->tag) strcat(html,e->tag);
        if (e->elementType == Heading) strcat(html,e->size);
        strcat(html,">");
    } else {
        /* Close Tag */
        if (e->elementType != Executable) strcat(html," />");
    }

    if (e->elementType == Button) strcat(html,"</form>");
    return stringify(html);
}

 /**
  * setAttribute
  * Set the attribute of the elements structure.
  *
  * IN: (Element*) said element, (char*) the attribute to set, (char*) value.
  * RETURN: NONE.
  *
  **/
void setAttribute(Element* e, char* key, char* value) {
     char tmp[2000], c; FILE* fp;
     int curr = 0;
     value = stringify(value);

      if (!strcmp(key,"name")) {
          if (e->name != NULL) free(e->name);
          e->name = value;
      } else if (!strcmp(key,"link")) {
          if (e->link != NULL) free(e->link);
          e->link = value;
      } else if (!strcmp(key,"size")) {
          if (e->size != NULL) free(e->size);
          e->size = value;
      } else if (!strcmp(key,"text")) {
          if (e->text != NULL) free(e->text);
          e->text = value;
      } else if (!strcmp(key,"value")) {
          if (e->value != NULL) free(e->value);
          e->value = value;
      } else if (!strcmp(key,"file")) {
          if (e->file != NULL) free(e->file);
          e->file = value;
          if (e->elementType != Executable) {
              fp = fopen(value,"r");
              while ((c = fgetc(fp)) != EOF) tmp[curr++] = c;
              tmp[curr] = '\0';
              if (e->text != NULL) free(e->text);
              e->text = stringify(tmp);
              fclose(fp);
          }
      } else if (!strcmp(key,"exe")) {
          if (e->exe != NULL) free(e->exe);
          e->exe = value;
      } else if (e->elementType == Executable && !strcmp(key,"params")) {
          if (e->value != NULL) free(e->value);
          e->value = value;
      } else if (!strcmp(key,"image")) {
          if (e->link != NULL) free(e->link);
          e->link = value;
      } else if (!strcmp(key,"action")) {
          if (e->exe != NULL) free(e->exe);
          e->exe = value;
      } else {
          bufferAppend(e->buffer, key);
          bufferAppend(e->buffer, "=\"");
          bufferAppend(e->buffer, value);
          bufferAppend(e->buffer, "\" ");
          free(value);
      }
  }

/**
* freeElement
* Free the data associated with the Element Structure.
*
* IN: (Element*) the structure to free.
* RETURN: NONE.
*
**/
void freeElement(Element* e) {
      if (e->name != NULL)  free(e->name);
      if (e->link != NULL)  free(e->link);
      if (e->size != NULL)  free(e->size);
      if (e->value != NULL) free(e->value);
      if (e->text != NULL)  free(e->text);
      if (e->value != NULL) free(e->value);
      if (e->file != NULL)  free(e->file);
      if (e->exe != NULL)   free(e->exe);
      free(e);
  }

int main(int argc, char* argv[]) {
    if (argc != 2) printError("Invalid args, format: ./a3 <config file>",1);
    char string[1999];
    int i, k;
    /* Get the file name for the output file */
    Split* split = newSplit(argv[1], ".");

    /* Open the files we need */
    FILE* fp = fopen(argv[1],"r");
    if (fp == NULL) printError("Unable to open file.",1);

    /* Print HTML skeleton */
    fprintf(stdout, "<!DOCTYPE html>\n<html>\n\t<head>\n\t\t<title>%s</title>\n\t</head>\n\t<body>\n",split->substring[0]);

    /* Create some standard element */
    while(fgets(string, 1999, fp) != NULL) {
        if (string[0] != '.') {
            printf("%s\n", string);
            continue;
        }
        Type type;

        /* Tokenize line at period, escape nested period */
        Split* elements = newSplitIgnoreSubDelimeters(string,".\n","\"");
        for (i = 0; i < elements->rows; i++) {
            /* Get the element type */
            type = getType(elements->substring[i][0]);

            /* Create the default element */
            Element* element = getDefault(type);

            /* Get the attributes of the element */
            Split* attributes = newSplitIgnoreSubDelimeters(elements->substring[i],"(), ","\"");
            for (k = 0; k < attributes->rows; k++) {
                /* For each attribute split the key value pair */
                Split* keyValues = newSplitIgnoreSubDelimeters(attributes->substring[k],"=","\"");
                if (keyValues->rows > 1) {
                    Split* value = newSplit(keyValues->substring[1],"\"");

                    if (DEBUG) {
                        printf("Elements '%s'\n", elements->substring[i]);
                        printf("\tatts '%s'\n", attributes->substring[k]);
                        printf("\t\tSetting '%s' -> %s\n", keyValues->substring[0],value->substring[0]);
                    }
                    /* Set the attributes, if there is a given keyvalue pair */
                    if ((element->elementType == Radio && element->name != NULL && !strcmp(keyValues->substring[0],"value")) || (element->elementType == Input && element->name != NULL && !strcmp(keyValues->substring[0],"text"))) {
                        char* tag = createTag(element);
                        if (!DEBUG) fprintf(stdout, "%s\n", tag);
                        free(tag);
                        setAttribute(element, "value","");
                    }
                    setAttribute(element, keyValues->substring[0],value->substring[0]);
                } freeSplit(keyValues);
            } freeSplit(attributes);

            /* Create tag */
            char* tag = createTag(element);
            if (!DEBUG) fprintf(stdout, "%s\n", tag);
            free(tag);

            if (element->elementType == Input || element->elementType == Radio) if (!DEBUG) fprintf(stdout, "\t\t<input type=\"submit\" />\n\t</form>");
        }
        freeSplit(elements);
    }
    /* Close the document, free memory */
    fprintf(stdout, "\n\t</body>\n</html>");
    freeSplit(split);
    fclose(fp);
    return 0;
}
