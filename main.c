#include <stdio.h>
#include <stdlib.h>

#include "development_task.h"

char* get_string() {
  int len = 0;
  int capacity = 1;
  char* new_description = (char*)malloc(capacity * sizeof(char));
  if (new_description == NULL) {
    return NULL;
  }

  char c;
  scanf(" %c", &c);
  while (c != '\n') {
    new_description[len++] = c;

    if (len >= capacity) {
      capacity *= 2;

      char* save_description =
          (char*)realloc(new_description, capacity * sizeof(char));

      if (save_description == NULL) {
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

  development_task_t** tasks =
      (development_task_t**)malloc(number_of_tasks * sizeof(development_task_t*));
  if (tasks == NULL) {
    return EXIT_FAILURE;
  }

  for (size_t i = 0; i < number_of_tasks; ++i) {
    int new_priority_of_task;
    printf("Введите приоритет задачи: ");
    scanf("%d", &new_priority_of_task);
    printf("Введите дату постановки задачи(день месяц год): ");
    int new_production_date[3];
    if (get_date(new_production_date) != 0) {
      return EXIT_FAILURE;
    }
    printf("Введите описание задачи: ");
    char* new_description = get_string();
    if (new_description == NULL) {
      return EXIT_FAILURE;
    }

    tasks[i] = create_development_task(i, new_description, new_priority_of_task,
                                       new_production_date);
    if (tasks[i] == NULL) {
      return EXIT_FAILURE;
    }

    free(new_description);
  }

  const size_t size_of_keys = 4;
  int keys[] = {NUMBER_OF_DAYS, NUMBER_OF_MONTHS, NUMBER_OF_YEARS,
                MAX_PRIORITY};
  development_task_t** sorted_tasks;
  sorted_tasks = radix_sort(keys, size_of_keys, tasks, number_of_tasks);
  if (sorted_tasks == NULL) {
    return EXIT_FAILURE;
  }

  for (size_t i = 0; i < number_of_tasks; ++i) {
    print_task(sorted_tasks[i]);
  }

  for (size_t i = 0; i < number_of_tasks; ++i) {
    free_development_task(tasks[i]);
  }
  free(tasks);
  free(sorted_tasks);
  return 0;
}
