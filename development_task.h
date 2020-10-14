#ifndef TP_C_CPP_HOMEWORK_DEVELOPMENT_TASK_H
#define TP_C_CPP_HOMEWORK_DEVELOPMENT_TASK_H

#define LEN_OF_PRODUCTION_DATE 3
#define END_OF_STRING '\0'
#define MAX_PRIORITY 10
#define MIN_PRIORITY 1
#define NUMBER_OF_DAYS 31
#define NUMBER_OF_MONTHS 12
#define NUMBER_OF_YEARS 61
#define MAX_YEAR 2030
#define MIN_YEAR 1970

typedef struct DevelopmentTask {
  int number;
  char* description;
  int priority; // Приоритет задан числами в диапазоне [1, 10]
  int production_date[LEN_OF_PRODUCTION_DATE]; // Дата, год задается в диапазоне [1970, 2030]
} DevelopmentTask;

//Help functions
int get_date(int* new_production_date);
size_t len_of_string(const char* string);
int check_correct_date(const int* date_for_checking);
int printf_task(const DevelopmentTask* my_task);

//Init/release operations
DevelopmentTask* create_DevelopmentTask(int number, char* description,
                                        int priority, int* production_date);
int free_development_task(DevelopmentTask* task);

//Sort functions
DevelopmentTask** distribution_sort(int key, size_t number_of_keys, DevelopmentTask** my_tasks, size_t size_of_tasks);
DevelopmentTask** radix_sort(int* keys, size_t size_of_keys, DevelopmentTask** my_tasks, size_t size_of_my_tasks);

#endif  // TP_C_CPP_HOMEWORK_DEVELOPMENT_TASK_H
