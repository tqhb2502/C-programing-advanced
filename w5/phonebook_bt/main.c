#include <stdio.h>
#include "phonebook.h"

int main() {
  PhoneBook pb = createPhoneBook();
  
  addPhoneNumber("Duc", 12345, pb);
  addPhoneNumber("Minh", 54321, pb);
  addPhoneNumber("Huong", 88888, pb);
  char *name;
  printf("Name: ");
  scanf("%s", name);

  long res = getPhoneNumber(name, pb);

  if (res != -1)
    printf("Phone number of %s is:%ld\n", name, res);
  else
    printf("Can\'t find phone number of %s\n", name);



  closePhoneBook(pb);
  return 0;  
}
