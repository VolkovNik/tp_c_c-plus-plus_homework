#include <stdio.h>

#include "development_task.h"

int main() {
  char* str;
  gets(str);
  char my_date[] = "10.12.2000";
  printf("%d", sizeof(my_date));
  return 0;
}
