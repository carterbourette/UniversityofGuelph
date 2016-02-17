#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct struct_phone {
  int areaCode;
  int phoneNumber;
  char descrip[25];

} Phone;

Phone* initPhone(int areaCode, int phoneNumber, char* descrip);
void printPhone(Phone* phone);

int main() { 
  Phone* myPhone;
  
  printf("Carter Bourette\n");

  // 	Init phone
  myPhone = initPhone(302, 9712307,"Mobile");
  
  //	Print out phone data
  printPhone(myPhone);

  free(myPhone);
  return 0;
}

Phone* initPhone(int areaCode, int phoneNumber, char* descrip) {
  //	Init the phone, alloc space
  Phone* newPhone;
  newPhone = (Phone*)malloc(sizeof(Phone));
  if (newPhone == NULL) {
    printf("No memory!");
    exit(1);
  }
  //	Set the structure values
  newPhone->areaCode = areaCode;
  newPhone->phoneNumber = phoneNumber;
  strcpy(newPhone->descrip, descrip);

  //	Return a pointer to our phone  
  return newPhone;
}

void printPhone(Phone* phone) {
  printf("%s: (%d) %d\n",phone->descrip, phone->areaCode, phone->phoneNumber);
}
