#ifndef TP_C_CPP_HOMEWORK_DEVELOPMENT_TASK_H
#define TP_C_CPP_HOMEWORK_DEVELOPMENT_TASK_H

#define LEN_OF_PRODUCTION_DATE 11

typedef struct DevelopmentTask {
  int number;
  char* description;
  int priority;
  char production_date[LEN_OF_PRODUCTION_DATE];
} DevelopmentTask;

// Init/release operations
DevelopmentTask* create_DevelopmentTask(int number, char* description,
                                        int priority, char* production_date);
int free_development_task(DevelopmentTask* task);

//Basic operations
int get_number_of_task(const DevelopmentTask* task);
int get_description_of_task(const DevelopmentTask* task);
int get_priority_of_task(const DevelopmentTask* task);
int get_production_date_of_task(const DevelopmentTask* task);

//Basic change operations
void change_description(const DevelopmentTask* task,char* new_description);
void change_priority(const DevelopmentTask* task, int new_priority);


#endif  // TP_C_CPP_HOMEWORK_DEVELOPMENT_TASK_H
