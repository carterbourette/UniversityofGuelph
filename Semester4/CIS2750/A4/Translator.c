/**
 * Carter Bourette
 * 0916638
 * cbourette@gmail.com  |  cbourett@mail.uoguelph.ca
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Translator.h"

/**
 * getInput
 * Get a string input from the user.
 *
 * IN: NONE.
 * RETURN: (char*) Pointer to the string.
 * NOTE: Caller must free.
 *
 **/
 char* getInput(char* str) {
     char input[255];
     printf("%s", str);
     scanf("%s",input);

     /* Allocate some memory and copy the string over */
     char *newstring = (char*) malloc(strlen(input)*sizeof(char));
     if (newstring == NULL) printError("Unable to allocate memory.");
     strcpy(newstring, input);
     return newstring;
 }

 /**
  * stringify
  * allocate a string.
  *
  * IN: NONE.
  * RETURN: (char*) Pointer to the string.
  * NOTE: Caller must free.
  *
  **/
 char* stringify(char* str) {
     char *newstring = (char*) malloc(strlen(str)*sizeof(char) + 1);
     if (newstring == NULL) printError("Unable to allocate memory.");
     strcpy(newstring, str);
     return newstring;
 }

/**
 * initProperties
 * Initialize a properties structure.
 *
 * IN: NONE.
 * RETURN: (Properties*) the allocated properties.
 *
 **/
Properties* initProperties() {
    Properties* ptr = (Properties*)malloc(sizeof(Properties));
    if (ptr == NULL) printError("Unable to allocate memory");
    ptr->tokens = NULL;
    ptr->append = NULL;
    ptr->constructor = NULL;
    ptr->scope = NULL;
    ptr->current = 0;

    ptr->tokens = initList();
    ptr->append = initList();
    ptr->constructor = initList();
    ptr->scope = initList();
    return ptr;
}

/**
 * freeProperties
 * Used to free the properties structure.
 *
 * IN: (Properties*) the properties structure.
 * RETURN: NONE.
 *
 **/
void freeProperties(Properties* properties) {
    freeTokenList(properties->tokens);
    freeTokenList(properties->append);
    freeTokenList(properties->constructor);
    freeTokenList(properties->scope);
    free(properties);
}

/**
 * buildToken
 * Malloc the memory for the token.
 *
 * IN: (char*) The statement.
 * RETURN: (Token*) The token.
 *
 **/
 Token* buildToken(char* stmt, int createSub) {
     Token* ptr = (Token*)malloc(sizeof(Token));
     if(ptr == NULL) printError("Unable to allocate memory.");
     ptr->statement = (char*)malloc(sizeof(char) * strlen(stmt) + 1);
     if(ptr->statement == NULL) printError("Unable to allocate memory.");
     strcpy(ptr->statement,stmt);
     ptr->subTokens = NULL;
     ptr->subTokens = initList();
     ptr->indentLevel = 0;
     if (createSub) ptr = tokenizeStatement(ptr);
     return ptr;
 }

/**
 * cpyCharToArray
 * Copy a character to specified index of array.
 *
 * IN: (Char*) The array, (int*) the index, (char) the character to add.
 * RETURN: NONE.
 *
 **/
 void cpyCharToArray(char* arr, int* index, char a) {
     arr[*index] = a;
     *index = *index + 1;
 }

/**
 * isIn
 * Return a status (int) if delimeter is in string.
 *
 * IN: (char*) delimeter, (char) character.
 * RETURN: (int) success.
 *
 **/
 int isIn(char* delim, char character) {
     int i;
     for (i = 0; i < strlen(delim); i++)
        if (delim[i] == character) return 1;
     return 0;
 }

/**
 * tokenizeStatement
 * Split the statement into a list of type Token.
 *
 * IN: (Token*) the pointer to the list, (char*) the statement.
 * RETURN: (Token*) the list of subtokens.
 *
 **/
Token* tokenizeStatement(Token* token) {
    char line[509];
    int index = 0, i;
    char* delim = " =,;()";

    /* Split every statement into tokens */
    for (i = 0; i < strlen(token->statement); i++) {
        /* When we hit a delimeter, end the statement, and create a token + a token delimeter */
        if(isIn(delim,token->statement[i]) || i == strlen(token->statement)-1) {
            line[index] = '\0';
            if (strcmp(line,"") != 0) {
                Token* subtoken = buildToken(line,0);
                addItem(token->subTokens, subtoken);
            }
            if (token->statement[i] != ' ' && token->statement[i] != '\0') {
                /* Create a new token for the delimiter */
                line[0] = token->statement[i];
                line[1] = '\0';
                Token* subtoken = buildToken(line,0);
                addItem(token->subTokens, subtoken);
            }
            index = 0;
        } else {
            cpyCharToArray(line, &index, token->statement[i]);
        }
    }
    return token;
}

/**
 * isReserved
 * Return whether the string is a resrved word.
 *
 * IN: (char*) the string to check.
 * RETURN: (int) status.
 *
 **/
int isReserved(char* str) {
    if (!strcmp(str,"typedef") || !strcmp(str,"const") || !strcmp(str,"while") || !strcmp(str,"for") || !strcmp(str,"do") || !strcmp(str,"if") || !strcmp(str,"else") || isType(str)) return 1;
    return 0;
}

/**
 * isType
 * Check if the reserved word is a type.
 *
 * IN: (char*) the variable type.
 * RETURN: (int) status.
 *
 **/
int isType(char* str) {
    if (!strcmp(str,"auto") || !strcmp(str,"extern") || !strcmp(str,"static") || !strcmp(str,"signed") || !strcmp(str,"unsigned") || !strcmp(str,"register") || !strcmp(str,"long") || !strcmp(str,"float") || !strcmp(str,"short") || !strcmp(str,"char")|| !strcmp(str,"int") || !strcmp(str,"double") || !strcmp(str,"void") || !strcmp(str,"volatile") || !strcmp(str,"long*") || !strcmp(str,"float*") || !strcmp(str,"short*") || !strcmp(str,"char*")|| !strcmp(str,"int*") || !strcmp(str,"double*") || !strcmp(str,"void*")) return 1;
    return 0;
}

/**
 * containsAll
 * Return a status if the string contains all delimeters passed in.
 *
 * IN: (char*) the string, (char*) the delimeter.
 * RETURN: (int) the status.
 *
 **/
int containsAll(char* stmt, char* delim) {
    int found = 0,i;
    for (i = 0; i < strlen(stmt); i++) {
        if (stmt[i] == delim[found]) found++;
        if (found == strlen(delim)) return 1;
    } return 0;
}

/**
 * submatches
 * Checks for substring matches in a string.
 *
 * IN: (char*) The sting, (char*) the substring.
 * RETURN: (int) status.
 *
 **/
int submatches(char* stmt, char* sub) {
    char* cpy = stringify(stmt);
    char* token = strtok(cpy, " ");

   while( token != NULL ) {
      if (sub == NULL) {
          if (isType(cpy)) {
              return 1;
          }
      } else {
          if (!strcmp(sub,token)) {
              free(cpy);
              return 1;
          }
      }
      token = strtok(NULL, " ");
   }
   free(cpy);
   return 0;
}

int subReserved(char* stmt) {
    char* cpy = stringify(stmt);
    char* token = strtok(cpy, " ");

   while( token != NULL ) {
       if (isReserved(cpy)) {
           return 1;
       }
      token = strtok(NULL, " ");
   }
   free(cpy);
   return 0;
}

/**
 * differentiateChildren
 * Based on a parent token determine the types of the children.
 *
 * IN: (Token*) parent.
 * RETURN: NONE.
 *
 **/
void differentiateChildren(Token* parent) {
    Type type = unset, lastType = unset;
    int inParam = 0, i;

    for (i = 0; i < getSizeOfList(parent->subTokens); i++) {
        Token* child = (Token*)getItem(parent->subTokens,i);

        switch (parent->type) {
            case variable:
                /* If child token is reserved word, set it to a type */
                if (isReserved(child->statement))
                    type = datatype;
                /* If follows a type (resevered) then set type to identifier  */
                else if (lastType == datatype) type = identifier;
                /* If type is '=' or ';' set to appendable */
                else if (!strcmp(child->statement,"=") || !strcmp(child->statement,";")) type = appendable;
                /* If follows appendable, set to value */
                else if (lastType == appendable) type = value;
                else type = appendable;

                break;
            case functionCall:
                /* If it is the first child in a func call, it must be the identifier */
                if (lastType == unset) {
                    type = identifier;
                } else if (!strcmp(child->statement,"(") || !strcmp(child->statement,")") || !strcmp(child->statement,",") || !strcmp(child->statement,";")) {
                    type = appendable;
                    if (strcmp(child->statement,")") != 0) inParam = 1;
                }
                /* If last was appendable must be a data type */
                else if (lastType == appendable) {
                    type = datatype;
                }
                /* If last was datatype and we're in parameters it must be an identifier  */
                else if (lastType == datatype)
                    type = identifier;
                break;
            case functionDeclaration:
                /* If child token is reserved word, set it to a type */
                if (isReserved(child->statement)) {
                    type = datatype;
                }
                /* If follows a type (resevered) then set type to identifier  */
                else if (lastType == datatype && !inParam) {
                    type = identifier;
                }
                /* If '(', set appendable and create a flag openParam */
                else if (!strcmp(child->statement,"(") || !strcmp(child->statement,")") || !strcmp(child->statement,",")) {
                    type = appendable;
                    if (strcmp(child->statement,")") != 0) inParam = 1;
                }
                /* If last was appendable must be a data type */
                else if (lastType == appendable)
                    type = datatype;
                /* If last was datatype and we're in parameters it must be an identifier  */
                else if (lastType == datatype)
                    type = identifier;
                else
                    type = appendable;
                break;
            case class:
                if (!strcmp(child->statement,"class") || !strcmp(child->statement,"struct")) {
                    type = datatype;
                } else if (lastType == datatype) {
                    type = identifier;
                }
                break;
            case classDefinition:
                if (!strcmp(child->statement,"class") || !strcmp(child->statement,"struct"))
                    type = class;
                else if (lastType == class) type = datatype;
                else if (lastType == datatype) type = identifier;
                else    type = appendable;
                break;
            default:
                type = appendable;
        }
        /* Set lastType for next iteration checks */
        lastType = type;
        child->type = type;
    }
}

/**
 * differentiateParent
 * Determine the type given a string (See enum Type).
 *
 * IN: (Token*) the code segment.
 * RETURN: NONE.
 *
 **/
void differentiateParent(Token* parent) {
    Type type;

    if (!strcmp(parent->statement,";") || !strcmp(parent->statement,"{") || !strcmp(parent->statement,"}")) {
        type = appendable;
    } else if (containsAll(parent->statement,"//")) {
        type = appendable;
    } else if (containsAll(parent->statement, "(*);")) {     /* function pointer */
        type = functionPtr;
    } else if (containsAll(parent->statement, "();")) {      /* function call */
        type = functionCall;
    } else if (containsAll(parent->statement, "()") && submatches(parent->statement,NULL)) {       /* function declaration */
        type = functionDeclaration;
    } else if (submatches(parent->statement, NULL)) {        /* look for variable - contains reservedWords */
        type = variable;
    } else if ((submatches(parent->statement, "class") && containsAll(parent->statement, ";")) || (submatches(parent->statement, "struct") && containsAll(parent->statement, ";"))) {
        type = classDefinition;
    } else if (submatches(parent->statement, "class") || submatches(parent->statement, "struct")) {
        type = class;
    } else {                                                /* otherwise just call it a statement */
        type = statement;
    }
    parent->type = type;
    differentiateChildren(parent);
}

/**
 * getChildTokenOfType
 * Given a token and a type get the corresponding child.
 *
 * IN: (Token*) token, (Type) the child type to be returned.
 * RETURN: (Token*) the child token.
 *
 **/
Token* getChildTokenOfType(Token* parent, Type cType) {
    int i;
    for (i = 0; i < getSizeOfList(parent->subTokens); i++) {
        Token* sub = (Token*)getItem(parent->subTokens, i);
        if (sub != NULL && sub->type == cType)  return sub;
    } return NULL;
}

/**
 * indent
 * Given a token add the proper indentation levels.
 *
 * IN: (Token*) token.
 * RETURN: NONE.
 *
 **/
void indent(Token* token) {
    int indent = token->indentLevel;
    if (!strcmp(token->statement,"{")) return;
    while (indent > 0) {
        indent--;
        printf("\t");
    }
}

/**
 * newConstructor
 * Create a constructor for a given class.
 *
 * IN: (Properties*) the linked lists, (char*) classname.
 * RETURN: NONE.
 *
 **/
void newConstructor(Properties *properties, char* classname) {
    char string[512];
    Token *t;
    strcpy(string, "");
    strcat(string, "void constructor");
    strcat(string, classname);
    strcat(string, "(struct ");
    strcat(string, classname);
    strcat(string, " *instance)");
    t = buildToken(string, 1);
    t->indentLevel = 0;
    addItem(properties->constructor,t);

    strcpy(string, "");
    strcat(string, "{");
    t = buildToken(string, 0);
    t->indentLevel = 0;
    addItem(properties->constructor,t);
}

/**
 * appendConstructor
 * Append statements to the current open constructor.
 *
 * IN: (Properties*) the linked lists and (char*) the statement to add.
 * RETURN: NONE.
 *
 **/
void appendConstructor(Properties *properties, char* string) {
    Token *t = buildToken(string, 1);
    t->indentLevel++;
    addItem(properties->constructor,t);
}

void formatFunction(Properties *properties, Token* token, char* classname) {
    char string[512], params[2], s2[255], funcName[510];
    int flag = 1;
    Token* t;
    params[1] = '\0';
    strcpy(string,"");
    strcpy(s2,"");
    strcpy(funcName,"");
    /* Format - datatype classnameFunctionNameParamtypeParamType */
    /* Append a function pointer - make sure to prepend class name */
    t = getChildTokenOfType(token, datatype);
    strcat(string,t->statement);
    strcat(string," ");
    printf("%s (*", t->statement);
    strcat(string,classname);
    t = getChildTokenOfType(token, identifier);
    strcat(string,t->statement);
    printf("%s%s", classname,t->statement);

    strcat(funcName,classname);
    strcat(funcName,t->statement);

    int inParams = 0, i =0;
    for ( i = 0; i < getSizeOfList(token->subTokens); i++) {
        Token* sub = (Token*)getItem(token->subTokens, i);
        if(sub->type == appendable) inParams++;
        if (inParams > 0) {
            if (sub->type == datatype) {
                printf("%c", sub->statement[0]);

                params[0] = sub->statement[0];
                strcat(string, params);
                strcat(funcName,params);

                if(inParams == 1) {
                    strcat(s2,sub->statement);
                } else {
                    strcat(s2,",");
                    strcat(s2,sub->statement);
                }
            }
        }
    }
    if (strcmp(s2,"UserPost") != 0) printf(")(%s);\n",s2);
    else printf(")();\n");

    /* hack of a solution */
    FunctionInfo classFunc;
    strcpy(classFunc.classname,classname);
    strcpy(classFunc.postFunction,funcName);
    strcpy(classFunc.preFunction,t->statement);
    addFunctionToProperties(properties, classFunc);

    /* Create a function constructor append class name */
    char temp[510];
    strcpy(temp, "instance->");
    strcat(temp, funcName);
    strcat(temp," = &");
    strcat(temp, funcName);
    strcat(temp,";");
    t = buildToken(temp,1);
    appendConstructor(properties, temp);

    inParams = 0;
    int doOnce = 1;
    for (i = 0; i < getSizeOfList(token->subTokens); i++) {
        Token* sub = (Token*)getItem(token->subTokens, i);

        if(sub->type == appendable) inParams = 1;
        if (inParams) {
            if (sub->type == identifier) strcat(string," ");
            if (strcmp(sub->statement, ")") !=0 && strcmp(sub->statement,"(") != 0) {
                if (doOnce) {
                    doOnce = 0;
                    strcat(string,", ");
                }
            }
            strcat(string,sub->statement);
            if (flag) {
                /* Append instance */
                flag = 0;
                strcat(string, "struct ");
                strcat(string,classname);
                strcat(string, " instance");
            }
        }
    }
    /* Create the token and add it to a list to append later */
    t = buildToken(string,1);
    addItem(properties->append, t);
}

int addUntilEnd (Properties *properties,int item) {
    int i = 0;
    for (i = item + 1; i < getSizeOfList(properties->tokens); i++) {
        Token* token = (Token*)getItem(properties->tokens,i);
        addItem(properties->append,token);
        if (!strcmp(token->statement,"}")) break;
    }
    return i;
}

void clearList(List* list) {

    Item* temp = list->first;
    while (temp != NULL) {
        temp = temp->next;
        free(temp);
    }
    list->first = list->last = NULL;
}

void printAppendables(Properties *properties) {
    int i;
    for(i = 0; i < getSizeOfList(properties->append); i++) {
        Token* token = (Token*)getItem(properties->append,i);
        token->indentLevel--;
        indent(token);
        printf("%s\n", token->statement);
    } clearList(properties->append);
}

void addFunctionToProperties(Properties *properties, FunctionInfo func) {
    properties->functions[properties->current] = func;
    properties->current++;
}

FunctionInfo* searchForClassFunction(Properties *properties, char* classname) {
    int i = 0;
    for (i = 0; i < 250; i++) {
        if (!strcmp(properties->functions[i].classname,classname))
            return &properties->functions[i];
    } return NULL;
}

FunctionInfo* searchForInstanceFunction(Properties *properties, char* instance) {
    int i = 0;
    for (i = 0; i < 250; i++) {
        if (!strcmp(properties->functions[i].instance,instance)) {
            return &properties->functions[i];
        }
    } return NULL;
}

void processAndCompile(Properties *properties) {
    char file[75];
    char* token = strtok(properties->filename,".");
    strcpy(file,token);
    strcat(file,".c");
    printf("Writing to file.... %s\n", file);
    FILE* fp = freopen(file,"w+",stdout);

    Token* childSubTok, *child2;
    Type lastType = unset;
    int inClass = 0, inFunc = 0,i,k;
    char* currentClassName = NULL;
    char temp[510],temp1[510];
    char* sttok;

    /* Iterate the tokens list */
    for (i = 0; i < getSizeOfList(properties->tokens); i++) {
        Token* token = (Token*)getItem(properties->tokens, i);

        indent(token);
        switch (token->type) {
            case class:
                /* Get child token of type class */
                childSubTok = getChildTokenOfType(token, identifier);
                /* Rename the child token, class to struct */
                printf("\n\nstruct %s\n", childSubTok->statement);
                /* Set current class name */
                currentClassName = childSubTok->statement;
                /* Create a constructor */
                newConstructor(properties, currentClassName);
                break;
            case classDefinition:
                /* Rename the child token, class to struct */
                printf("struct ");
                for (k = 1; k < getSizeOfList(token->subTokens); k++) {
                    Token* child = (Token*)getItem(token->subTokens,k);
                    printf("%s ", child->statement);
                }
                printf("\n");
                childSubTok = getChildTokenOfType(token, datatype);
                printf("\tconstructor%s",childSubTok->statement);

                child2 = getChildTokenOfType(token, identifier);
                printf("(&%s);\n", child2->statement);

                for (k = 0; k< 250; k++) {
                    if (!strcmp(properties->functions[k].classname,childSubTok->statement)) {
                        strcpy(properties->functions[k].instance,child2->statement);
                    }

                }
                break;
            case functionDeclaration:
                if (inClass > 0) {
                    /* Prepend class name to child token (function identifier) */
                    formatFunction(properties, token, currentClassName);
                    /* Add this token + the ones following until we hit the end of the function to a list called append later */
                    i = addUntilEnd(properties, i);
                } else {
                    /* We can just output this */
                    printf("%s\n",token->statement);
                }
                break;
            case functionCall:
                /* if the first token is an instance find the func name */
                strcpy(temp,token->statement);
                sttok = strtok(temp,".");
                strcpy(temp1,sttok);
                sttok = strtok(NULL,".()");
                if (searchForInstanceFunction(properties,temp1) != NULL) {
                    for (k = 0; k < 250; k++) {
                        if (!strcmp(properties->functions[k].instance,temp1)) {
                            if (!strcmp(properties->functions[k].preFunction,sttok)) {
                                sttok = strtok(NULL,".();");
                                if (sttok == NULL) printf("%s.%s();\n", properties->functions[k].instance,properties->functions[k].postFunction);
                                else printf("%s.%s(%s);\n", properties->functions[k].instance,properties->functions[k].postFunction,sttok);
                                break;
                            }
                        }
                    }
                } else
                    printf("%s\n", token->statement);
                break;
            case appendable:
                if (!strcmp(token->statement,"{")) {
                    if (lastType == class) {
                        inClass++;
                    } else if (lastType == functionDeclaration) {
                        inFunc++;
                    }
                }
                if (!strcmp(token->statement,"}")) {
                    if (inFunc > 0) {
                        inFunc--;
                    } else if (inClass > 0) {
                        /* Marks the end of a class, we should print the postAppend list now */
                        inClass--;
                        Token* t = buildToken("}", 0);
                        addItem(properties->constructor,t);

                    }
                }
                /* Append the statement */
                printf("%s\n", token->statement);
                if (lastType == appendable) {
                    printAppendables(properties);
                    for(k = 0; k < getSizeOfList(properties->constructor); k++) {
                        Token* token = (Token*)getItem(properties->constructor,k);
                        indent(token);
                        printf("%s\n", token->statement);
                    } clearList(properties->constructor);
                }
                break;
            default:
                /* Append the statement */
                printf("%s\n", token->statement);
        }
        /* Set the reference variables */
        lastType = token->type;
    }
    fclose(fp);
}

/**
 * freeToken
 * To be used on an individual token.
 *
 * IN: (Token*) the token to free.
 * RETURN: NONE.
 *
 **/
void freeToken(Token* token) {
    if (token == NULL) return;
    if (token->statement != NULL) free(token->statement);
    freeTokenList(token->subTokens);
    free(token);
}

/**
 * freeTokenList
 * To be used on a list of tokens.
 *
 * IN: (List*) the token list.
 * RETURN: NONE.
 *
 **/
void freeTokenList(List* list) {
    int i;
    for (i = 0; i < getSizeOfList(list); i++) {
        Token* token = (Token*)getItem(list, i);
        freeToken(token);
    }
    freeList(list);
}

/**
 * printError
 * Take an error message and display, exit.
 *
 * IN: (char*) error message.
 * RETURN: NONE.
 *
 **/
void printError(char* e) {
    printf("%s\n", e);
    exit(1);
}

void printToks(List* toks) {
    int i, k;
    for (i = 0; i < getSizeOfList(toks); i++) {
        Token* p = (Token*)getItem(toks, i);
        printf("%s -> %d at lvl %d\n", p->statement, p->type,p->indentLevel);
        for (k = 0; k < getSizeOfList(p->subTokens); k++) {
            Token* t = (Token*)getItem(p->subTokens, k);
            printf("\t%s - %d\n", t->statement,t->type);
        }
    }
}
