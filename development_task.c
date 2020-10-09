#include <stdio.h>
#include <stdlib.h>

#include "development_task.h"

DevelopmentTask* create_DevelopmentTask(int number, char* description,
                                        int priority, char* production_date) {
  if (description == NULL || sizeof(production_date) != LEN_OF_PRODUCTION_DATE) {
    puts("ERROR");
    return NULL;
  }

  DevelopmentTask* my_task = (DevelopmentTask*)malloc(sizeof(DevelopmentTask));

  size_t len_description = sizeof(description);
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
int get_number_of_task(const DevelopmentTask* task);
int get_description_of_task(const DevelopmentTask* task);
int get_priority_of_task(const DevelopmentTask* task);
int get_production_date_of_task(const DevelopmentTask* task);

//Basic change operations
void change_description(const DevelopmentTask* task,char* new_description);
void change_priority(const DevelopmentTask* task, int new_priority);
