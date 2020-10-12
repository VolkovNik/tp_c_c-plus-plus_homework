#include <stdio.h>
#include <stdlib.h>

#include "development_task.h"

int len_of_string(const char* string) {
  if (string == NULL) {
    puts("ERROR");
    return -1;
  }

  int length = 0;
  while (string[length] != END_OF_STRING) {
    ++length;
  }

  return length;
}

int check_correct_date(const int* date_for_checking) {
  if (date_for_checking == NULL) {
    puts("ERROR");
    return -1;
  }

  if (date_for_checking[0] > 31 || date_for_checking[0] < 1 ||
      date_for_checking[1] > 12 || date_for_checking[1] < 1 ||
      date_for_checking[2] > 2020 || date_for_checking[2] < 1980) {
    puts("WRONG DATE OF CREATION");
    return 0;
  }

  return 1;
}

int printf_task(const DevelopmentTask* my_task) {
  if (my_task == NULL) {
    puts("ERROR");
    return -1;
  }

  printf("Номер задачи: %d\n", my_task->number);
  printf("Приоритет: %d\n", my_task->priority);
  printf("Дата создания: ");
  for (int i = 0; i < (LEN_OF_PRODUCTION_DATE - 1); ++i) {
    printf("%d.", my_task->production_date[i]);
  }
  printf("%d\n", my_task->production_date[LEN_OF_PRODUCTION_DATE - 1]);
  printf("Описание задачи: ");

  int len_description = len_of_string(my_task->description);
  for (int i = 0; i < len_description; ++i) {
    printf("%c", my_task->description[i]);
  }
  printf("\n");

  return 0;
}

DevelopmentTask* create_DevelopmentTask(int number, char* description,
                                        int priority, int* production_date) {
  if (description == NULL || !check_correct_date(production_date)) {
    puts("ERROR");
    return NULL;
  }

  DevelopmentTask* my_task = (DevelopmentTask*)malloc(sizeof(DevelopmentTask));

  size_t len_description = len_of_string(description);
  my_task->description = (char*)malloc((len_description + 1));

  if (my_task == NULL || my_task->description == NULL) {
    printf("%s", "ENOMEM");
    return NULL;
  }

  for (int i = 0; i < len_description; ++i) {
    my_task->description[i] = description[i];
  }
  my_task->description[len_description] = END_OF_STRING;

  for (int i = 0; i < LEN_OF_PRODUCTION_DATE; ++i) {
    my_task->production_date[i] = production_date[i];
  }

  my_task->number = number;
  my_task->priority = priority;

  return my_task;
}

int free_development_task(DevelopmentTask* task) {
  if (task == NULL) {
    puts("ERROR");
    return 1;
  }

  free(task->description);
  free(task);

  return 0;
}
