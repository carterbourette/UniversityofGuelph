/**
 * Carter Bourette
 * 0916638
 * cbourette@gmail.com  |  cbourett@mail.uoguelph.ca
 **/

#ifndef __CBOURETTE_PARSE__
#define __CBOURETTE_PARSE__

#include "stringy.h"

typedef enum enum_type {
    Button, HorizontalRule, Executable, Heading, Input, Link, Picture, Radio, Text, CSS, LineBreak, Undefined
} Type;

typedef struct struct_element {
    Type elementType;
    char* name;
    char* link;
    char* size;
    char* text;
    char* value;
    char* file;
    char* exe;
    char* tag;
    int closeTag;
    int formCreated;
    Buffer* buffer;
} Element;

/**
 * getType
 * Return the type of html element.
 *
 * IN: (char) HTML representation.
 * RETURN: (Type) the type of element.
 *
 **/
 Type getType(char tag);

/**
 * initElement
 * Allocate memory for a new element.
 *
 * IN: NONE.
 * RETURN: (Element*).
 *
 **/
Element* initElement();

/**
 * getDefault
 * Takes the type of HTML element and returns a default element.
 *
 * IN: (Type) The type of element
 * RETURN: (Element*) default element.
 *
 **/
Element* getDefault(Type type);

/**
* setAttribute
* Set the attribute of the elements structure.
*
* IN: (Element*) said element, (char*) the attribute to set, (char*) value.
* RETURN: NONE.
*
**/
void setAttribute(Element* e, char* attribute, char* value);

/**
* getTag
* Given an element get the corresponding HTML tag.
*
* IN: (Element*), (int) close tag.
* RETURN: (char*) the html tag string
*
**/
char* getTag(Element* e, int isClose);

/**
* createTag
* Creates an html tag.
*
* IN: (Element*) the element.
* RETURN: (char*).
*
**/
char* createTag(Element* e);

/**
* freeElement
* Free the data associated with the Element Structure.
*
* IN: (Element*) the structure to free.
* RETURN: NONE.
*
**/
void freeElement(Element* e);

#endif
