#include <stdio.h>
#include <stdlib.h>

#include "development_task.h"

DevelopmentTask** distribution_sort(int key, int number_of_keys, DevelopmentTask** my_tasks, int size_of_tasks) {
  int* count = (int*)malloc(number_of_keys * sizeof(int));
  for (int i = 0; i < number_of_keys; ++i) {
    count[i] = 0;
  }

  int key_value = 0;
  for (int j = 0; j < size_of_tasks; ++j) {
    switch (key) {
      case NUMBER_OF_YEARS:
        key_value = my_tasks[j]->production_date[2] - MIN_YEAR;
        break;
      case NUMBER_OF_MONTHS:
        key_value = my_tasks[j]->production_date[1] - 1;
        break;
      case NUMBER_OF_DAYS:
        key_value = my_tasks[j]->production_date[0] - 1;
        break;
      case MAX_PRIORITY:
        key_value = my_tasks[j]->priority - MIN_PRIORITY;
        break;
    }
    count[key_value] = count[key_value] + 1;

  }
  for (int i = 1; i < number_of_keys; ++i) {
    count[i] = count[i] + count[i-1];
  }

  DevelopmentTask** sorted_my_tasks = (DevelopmentTask**)malloc(size_of_tasks * sizeof(DevelopmentTask*));

  for (int j = size_of_tasks - 1; j >= 0; --j) {
    switch (key) {
      case NUMBER_OF_YEARS:
        key_value = my_tasks[j]->production_date[2] - MIN_YEAR;
        break;
      case NUMBER_OF_MONTHS:
        key_value = my_tasks[j]->production_date[1] - 1;
        break;
      case NUMBER_OF_DAYS:
        key_value = my_tasks[j]->production_date[0] - 1;
        break;
      case MAX_PRIORITY:
        key_value = my_tasks[j]->priority - MIN_PRIORITY;
        break;
    }
    int i = count[key_value] - 1;
    count[key_value] = i;
    sorted_my_tasks[i] = my_tasks[j];
  }

  free(count);
  free(my_tasks);

  return sorted_my_tasks;
}

DevelopmentTask** radix_sort(int* keys, int size_of_keys, DevelopmentTask** my_tasks, int size_of_my_tasks) {
  DevelopmentTask** sorted_my_tasks = (DevelopmentTask**)malloc(size_of_my_tasks * sizeof(DevelopmentTask*));
  for (int i = 0; i < size_of_my_tasks; ++i) {
    sorted_my_tasks[i] = my_tasks[i];
  }

  for (int i = 0; i < size_of_keys; ++i) {
    sorted_my_tasks = distribution_sort(keys[i], keys[i], sorted_my_tasks, size_of_my_tasks);
  }

  return sorted_my_tasks;
}

int get_date(int* new_production_date) {
  if (new_production_date == NULL) {
    puts("ERROR");
    return -1;
  }

  for (int i = 0; i < LEN_OF_PRODUCTION_DATE; ++i) {
    scanf("%d", &new_production_date[i]);
  }

  return 0;
}

char* get_string() {
  int len = 0;
  int capacity = 1;
  char *new_description = (char*)malloc(capacity * sizeof(char));

  char c;
  scanf(" %c", &c);
  while (c != '\n') {
    new_description[len++] = c;

    if (len >= capacity) {
      capacity *= 2;

      char *save_description = (char*)realloc(new_description, capacity * sizeof(char));

      if (save_description == NULL) {
        puts("Not enough memory, operation aborted!");
        return NULL;
      } else {
        new_description = save_description;
      }

    }

    scanf("%c", &c);
  }

  new_description[len] = END_OF_STRING;

  return new_description;
}

int main() {
  int number_of_tasks = 0;
  printf("Введите количество задач: ");
  scanf("%d", &number_of_tasks);

  DevelopmentTask** tasks = (DevelopmentTask**)malloc(number_of_tasks * sizeof(DevelopmentTask*));

  if (tasks == NULL) {
    puts("ERROR");
    return -1;
  }

  for(int i = 0; i < number_of_tasks; ++i) {
    int new_priority_of_task;
    printf("Введите приоритет задачи: ");
    scanf("%d", &new_priority_of_task);
    printf("Введите дату постановки задачи(день месяц год): ");
    int new_production_date[3];
    if (get_date(new_production_date) != 0) {
      return -1;
    }
    printf("Введите описание задачи: ");
    char* new_description = get_string();
    if (new_description == NULL) {
      return -1;
    }

    tasks[i] = create_DevelopmentTask(i, new_description, new_priority_of_task, new_production_date);

    if (tasks[i] == NULL) {
      return -1;
    }

    free(new_description);
  }

  int keys[4] = {MAX_PRIORITY, NUMBER_OF_DAYS, NUMBER_OF_MONTHS, NUMBER_OF_YEARS};
  DevelopmentTask** sorted_tasks;
  sorted_tasks = radix_sort(keys, 4, tasks, number_of_tasks);

  for (int i = 0; i < number_of_tasks; ++i) {
    printf_task(sorted_tasks[i]);
  }

  for (int i = 0; i < number_of_tasks; ++i) {
    free_development_task(tasks[i]);
  }
  free(tasks);
  free(sorted_tasks);
  return 0;
}
