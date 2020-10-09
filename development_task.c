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

DevelopmentTask* create_DevelopmentTask(int number, char* description,
                                        int priority, char* production_date) {
  if (description == NULL || check_correct_date(production_date)) {
    puts("ERROR");
    return NULL;
  }

  DevelopmentTask* my_task = (DevelopmentTask*)malloc(sizeof(DevelopmentTask));

  size_t len_description = len_of_string(description);
  my_task->description = (char*)malloc(len_description);

  if (my_task == NULL || my_task->description == NULL) {
    printf("%s", "ENOMEM");
    return NULL;
  }

  for (int i = 0; i < len_description; ++i) {
    my_task->description[i] = description[i];
  }

  for (int i = 0; i < LEN_OF_PRODUCTION_DATE; ++i) {
    my_task->production_date[i] = production_date[i];
  }

  my_task->number = number;
  my_task->priority = priority;

  return my_task;
}

int free_development_task(DevelopmentTask* task) {
  if (task == NULL) {
    puts("Error");
    return 1;
  }

  free(task->description);
  free(task);

  return 0;
}

//Basic operations
int get_number_of_task(const DevelopmentTask* task) {
  if (task == NULL) {
    puts("ERROR");
    return -1;
  }

  return task->number;
}

char* get_description_of_task(const DevelopmentTask* task) {
  if (task == NULL) {
    puts("ERROR");
    return NULL;
  }

  return task->description;
}

int get_priority_of_task(const DevelopmentTask* task) {
  if (task == NULL) {
    puts("ERROR");
    return -1;
  }

  return task->priority;
}

int* get_production_date_of_task(const DevelopmentTask* task) {
  if (task == NULL) {
    puts("ERROR");
    return NULL;
  }

  return task->production_date;
}

//Basic change operations
int change_description(DevelopmentTask* task,char* new_description) {
  if (task == NULL || new_description == NULL) {
    puts("ERROR");
    return -1;
  }

  int len_new_description = len_of_string(new_description);
  int len_description = len_of_string(task->description);

  if (len_new_description > len_description) {
    char *save_description = (char*)realloc(task->description, 2 * len_description * sizeof(char));

    if (save_description == NULL) {
      puts("Not enough memory, operation aborted!");
      return -1;
    } else {
      task->description = save_description;
    }

  }

  for (int i = 0; i < len_new_description; ++i) {
    task->description[i] = new_description[i];
  }

  task->description[len_new_description] = END_OF_STRING;

  return 0;
}

int change_priority(DevelopmentTask* task, int new_priority){
  if (task == NULL) {
    puts("ERROR");
    return -1;
  }

  task->priority = new_priority;

  return 0;
}
