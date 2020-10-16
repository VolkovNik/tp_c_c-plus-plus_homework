#ifndef TP_C_CPP_HOMEWORK_DEVELOPMENT_TASK_H
#define TP_C_CPP_HOMEWORK_DEVELOPMENT_TASK_H

#include <stdbool.h>
#include <stdio.h>

#define LEN_OF_PRODUCTION_DATE 3
#define END_OF_STRING '\0'
#define MAX_PRIORITY 10
#define MIN_PRIORITY 1
#define NUMBER_OF_DAYS 31
#define NUMBER_OF_MONTHS 12
#define NUMBER_OF_YEARS 61
#define MAX_YEAR 2030
#define MIN_YEAR 1970
#define EXIT_FAILURE_WITH_MNS -1

typedef struct development_task_t {
  int number;
  char* description;
  int priority;  // Приоритет задан числами в диапазоне [1, 10]
  int production_date[LEN_OF_PRODUCTION_DATE];  // Дата, год задается в
                                                // диапазоне [1970, 2030]
} development_task_t;

// Help functions
int get_date(int* new_production_date);
int len_of_string(const char* string);
bool check_correct_date(const int* date_for_checking);
int print_task(const development_task_t* my_task);

// Init/release operations
development_task_t* create_development_task(int number, char* description,
                                            int priority, int* production_date);
int free_development_task(development_task_t* task);

// Sort functions
development_task_t** distribution_sort(int key, size_t number_of_keys,
                                       development_task_t** my_tasks,
                                       size_t size_of_tasks);
development_task_t** radix_sort(int* keys, size_t size_of_keys,
                                development_task_t** my_tasks,
                                size_t size_of_my_tasks);

#endif  // TP_C_CPP_HOMEWORK_DEVELOPMENT_TASK_H
