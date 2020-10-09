#ifndef TP_C_CPP_HOMEWORK_DEVELOPMENT_TASK_H
#define TP_C_CPP_HOMEWORK_DEVELOPMENT_TASK_H

#define LEN_OF_PRODUCTION_DATE 3
#define END_OF_STRING '\0'

typedef struct DevelopmentTask {
  int number;
  char* description;
  int priority;
  int production_date[LEN_OF_PRODUCTION_DATE];
} DevelopmentTask;

//Help functions
int len_of_string(const char* string);
int check_correct_date(const int* date_for_checking);

//Init/release operations
DevelopmentTask* create_DevelopmentTask(int number, char* description,
                                        int priority, char* production_date);
int free_development_task(DevelopmentTask* task);

//Basic operations
int get_number_of_task(const DevelopmentTask* task);
char* get_description_of_task(const DevelopmentTask* task);
int get_priority_of_task(const DevelopmentTask* task);
int* get_production_date_of_task(const DevelopmentTask* task);

//Basic change operations
int change_description(DevelopmentTask* task,char* new_description);
int change_priority(DevelopmentTask* task, int new_priority);


#endif  // TP_C_CPP_HOMEWORK_DEVELOPMENT_TASK_H
