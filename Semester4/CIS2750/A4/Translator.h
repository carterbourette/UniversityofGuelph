/**
 * Carter Bourette
 * 0916638
 * cbourette@gmail.com  |  cbourett@mail.uoguelph.ca
 **/

#ifndef __CBOURETTE_TRANSLATOR__
#define __CBOURETTE_TRANSLATOR__

#include "LinkedList.h"

/*identifier, value, type, operator, appendable, parameter*/
typedef enum type {
   statement, variable, class, appendable, datatype, identifier, parameter, value, functionDeclaration, functionCall, functionPtr, classDefinition, unset
} Type;

typedef struct struct_token {
    Type type;
    int indentLevel;
    char* statement;
    List* subTokens;
} Token;

typedef struct struct_functioninfo {
    char classname[75];
    char instance[150];
    char preFunction[150];
    char postFunction[150];
} FunctionInfo;

typedef struct struct_properties {
    char* filename;
    List* tokens;
    List* append;
    List* constructor;
    List* scope;
    FunctionInfo functions[250];
    int current;
} Properties;

/**
* getInput
* Get a string input from the user.
*
* IN: NONE.
* RETURN: (char*) Pointer to the string.
* NOTE: Caller must free.
*
**/
char* getInput(char* str);

/**
* stringify
* allocate a string.
*
* IN: NONE.
* RETURN: (char*) Pointer to the string.
* NOTE: Caller must free.
*
**/
char* stringify(char* str);

/**
* initProperties
* Initialize a properties structure.
*
* IN: NONE.
* RETURN: (Properties*) the allocated properties.
*
**/
Properties* initProperties();

/**
* freeProperties
* Used to free the properties structure.
*
* IN: (Properties*) the properties structure.
* RETURN: NONE.
*
**/
 void freeProperties(Properties* properties);

/**
* buildToken
* Malloc the memory for the token.
*
* IN: (char*) The statement.
* RETURN: (Token*) The token.
*
**/
Token* buildToken(char* stmt, int createSub);

/**
* cpyCharToArray
* Copy a character to specified index of array.
*
* IN: (Char*) The array, (int*) the index, (char) the character to add.
* RETURN: NONE.
*
**/
void cpyCharToArray(char* arr, int* index, char a);

/**
* isIn
* Return a status (int) if delimeter is in string.
*
* IN: (char*) delimeter, (char) character.
* RETURN: (int) success.
*
**/
int isIn(char* delim, char character);

/**
 * tokenizeStatement
 * Split the statement into a list of type Token.
 *
 * IN: (Token*) the pointer to the list, (char*) the statement.
 * RETURN: (Token*) the list of subtokens.
 *
 **/
Token* tokenizeStatement(Token* token);

/**
 * isReserved
 * Return whether the string is a resrved word.
 *
 * IN: (char*) the string to check.
 * RETURN: (int) status.
 *
 **/
int isReserved(char* str);

/**
 * isType
 * Check if the reserved word is a type.
 *
 * IN: (char*) the variable type.
 * RETURN: (int) status.
 *
 **/
int isType(char* str);

/**
 * containsAll
 * Return a status if the string contains all delimeters passed in.
 *
 * IN: (char*) the string, (char*) the delimeter.
 * RETURN: (int) the status.
 *
 **/
int containsAll(char* stmt, char* delim);

/**
 * submatches
 * Checks for substring matches in a string.
 *
 * IN: (char*) The sting, (char*) the substring.
 * RETURN: (int) status.
 *
 **/
int submatches(char* stmt, char* sub);
int subReserved(char* stmt);

/**
 * differentiateChildren
 * Based on a parent token determine the types of the children.
 *
 * IN: (Token*) parent.
 * RETURN: NONE.
 *
 **/
void differentiateChildren(Token* parent);

/**
 * differentiateParent
 * Determine the type given a string (See enum Type).
 *
 * IN: (Token*) the code segment.
 * RETURN: NONE.
 *
 **/
void differentiateParent(Token* parent);

/**
 * getChildTokenOfType
 * Given a token and a type get the corresponding child.
 *
 * IN: (Token*) token, (Type) the child type to be returned.
 * RETURN: (Token*) the child token.
 *
 **/
Token* getChildTokenOfType(Token* parent, Type cType);

/**
 * indent
 * Given a token add the proper indentation levels.
 *
 * IN: (Token*) token.
 * RETURN: NONE.
 *
 **/
void indent(Token* token);

/**
 * newConstructor
 * Create a constructor for a given class.
 *
 * IN: (Properties*) the linked lists, (char*) classname.
 * RETURN: NONE.
 *
 **/
void newConstructor(Properties *properties, char* classname);

/**
 * appendConstructor
 * Append statements to the current open constructor.
 *
 * IN: (Properties*) the linked lists and (char*) the statement to add.
 * RETURN: NONE.
 *
 **/
void appendConstructor(Properties *properties, char* string);

void formatFunction(Properties *properties, Token* token, char* classname);
int addUntilEnd (Properties *properties,int item);
void clearList(List* list);
void printAppendables(Properties *properties);
void addFunctionToProperties(Properties *properties, FunctionInfo func);
FunctionInfo* searchForClassFunction(Properties *properties, char* classname);
FunctionInfo* searchForInstanceFunction(Properties *properties, char* instance);
void processAndCompile(Properties *properties);

/**
 * freeToken
 * To be used on an individual token.
 *
 * IN: (Token*) the token to free.
 * RETURN: NONE.
 *
 **/
void freeToken(Token* token);

/**
 * freeTokenList
 * To be used on a list of tokens.
 *
 * IN: (List*) the token list.
 * RETURN: NONE.
 *
 **/
void freeTokenList(List* list);

/**
 * printError
 * Take an error message and display, exit.
 *
 * IN: (char*) error message.
 * RETURN: NONE.
 *
 **/
void printError(char* e);

void printToks(List* toks) ;

#endif
