#include "development_task.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int get_date(int* new_production_date) {
  if (new_production_date == NULL) {
    return EXIT_FAILURE_WITH_MNS;
  }

  for (size_t i = 0; i < LEN_OF_PRODUCTION_DATE; ++i) {
    if (scanf("%d", &new_production_date[i])) {
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}

int len_of_string(const char* string) {
  if (string == NULL) {
    return EXIT_FAILURE_WITH_MNS;
  }

  size_t length = 0;
  while (string[length] != END_OF_STRING) {
    ++length;
  }

  return length;
}

bool check_correct_date(const int* date_for_checking) {
  if (date_for_checking == NULL) {
    return false;
  }

  if (date_for_checking[0] > 31 || date_for_checking[0] < 1 ||
      date_for_checking[1] > 12 || date_for_checking[1] < 1 ||
      date_for_checking[2] > 2020 || date_for_checking[2] < 1980) {
    return false;
  }

  return true;
}

int print_task(const development_task_t* my_task) {
  if (my_task == NULL) {
    return EXIT_FAILURE;
  }

  printf("Номер задачи: %d\n", my_task->number);
  printf("Приоритет: %d\n", my_task->priority);
  printf("Дата создания: ");
  for (size_t i = 0; i < (LEN_OF_PRODUCTION_DATE - 1); ++i) {
    printf("%d.", my_task->production_date[i]);
  }
  printf("%d\n", my_task->production_date[LEN_OF_PRODUCTION_DATE - 1]);
  printf("Описание задачи: ");

  size_t len_description = len_of_string(my_task->description);
  for (size_t i = 0; i < len_description; ++i) {
    printf("%c", my_task->description[i]);
  }
  printf("\n");

  return EXIT_SUCCESS;
}

development_task_t* create_development_task(int number, char* description,
                                            int priority, int* production_date) {
  if (description == NULL || check_correct_date(production_date)) {
    return NULL;
  }

  development_task_t* my_task = (development_task_t*)malloc(sizeof(development_task_t));

  if (my_task == NULL) {
    return NULL;
  }

  size_t len_description = len_of_string(description);
  my_task->description = (char*)malloc((len_description + 1));

  if (my_task->description == NULL) {
    free(my_task);
    return NULL;
  }

  for (size_t i = 0; i < len_description; ++i) {
    my_task->description[i] = description[i];
  }
  my_task->description[len_description] = END_OF_STRING;

  for (size_t i = 0; i < LEN_OF_PRODUCTION_DATE; ++i) {
    my_task->production_date[i] = production_date[i];
  }

  my_task->number = number;
  my_task->priority = priority;

  return my_task;
}

int free_development_task(development_task_t* task) {
  if (task == NULL) {
    return EXIT_FAILURE;
  }

  free(task->description);
  free(task);

  return EXIT_SUCCESS;
}

// сортировка по одному ключу(key) в порядке возрастания, в нашем случае ключ
// это - кол-во дней, кол-во месяцев, кол-во лет, макс значение приоритета
development_task_t** distribution_sort(int key, size_t number_of_keys,
                                       development_task_t** my_tasks,
                                       size_t size_of_tasks) {
  if (my_tasks == NULL) {
    return NULL;
  }

  int* count = (int*)malloc(number_of_keys * sizeof(int));
  if (count == NULL) {
    return NULL;
  }

  for (size_t i = 0; i < number_of_keys; ++i) {
    count[i] = 0;
  }

  int key_value = 0;
  for (size_t j = 0; j < size_of_tasks; ++j) {
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
        key_value = my_tasks[j]->priority + MAX_PRIORITY;
        break;
    }
    count[key_value] = count[key_value] + 1;
  }
  for (size_t i = 1; i < number_of_keys; ++i) {
    count[i] = count[i] + count[i - 1];
  }

  development_task_t** sorted_my_tasks =
      (development_task_t**)malloc(size_of_tasks * sizeof(development_task_t*));
  if (sorted_my_tasks == NULL) {
    return NULL;
  }

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
        key_value = my_tasks[j]->priority + MAX_PRIORITY;
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

// поразрядная сортировка нашей структуры, где keys - ключи
development_task_t** radix_sort(int* keys, size_t size_of_keys,
                                development_task_t** my_tasks,
                                size_t size_of_my_tasks) {
  if (my_tasks == NULL) {
    return NULL;
  }

  development_task_t** sorted_my_tasks =
      (development_task_t**)malloc(size_of_my_tasks * sizeof(development_task_t*));
  if (sorted_my_tasks == NULL) {
    return NULL;
  }

  for (size_t i = 0; i < size_of_my_tasks; ++i) {
    sorted_my_tasks[i] = my_tasks[i];
    sorted_my_tasks[i]->priority *=
        -1;  // чтобы отсортировать в правильно порядке
  }

  for (size_t i = 0; i < size_of_keys; ++i) {
    sorted_my_tasks =
        distribution_sort(keys[i], keys[i], sorted_my_tasks, size_of_my_tasks);
    if (sorted_my_tasks == NULL) {
      return NULL;
    }
  }

  for (size_t i = 0; i < size_of_my_tasks; ++i) {
    sorted_my_tasks[i]->priority *= -1;  //возвращаю правильное значение
  }

  return sorted_my_tasks;
}