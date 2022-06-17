#include <stdio.h>
#include "phonebook.h"
#include "jval.h"

int main() {
  PhoneBook pb = createPhoneBook();
  
  addPhoneNumber("Duc", 12345, &pb);
  addPhoneNumber("Minh", 54321, &pb);
  addPhoneNumber("Huong", 88888, &pb);

  long res = getPhoneNumber("Huong", pb);

  if (res != -1)
    printf("Phone number of Huong is:%ld\n", res);
  else
    printf("Can\'t find phone number of Huong\n");

  return 0;  
}
