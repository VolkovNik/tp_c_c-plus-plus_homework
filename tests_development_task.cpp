extern "C" {
#include "development_task.c"
}

#include "gtest/gtest.h"

TEST(get_date, t1) {
  int* null_date = NULL;
  ASSERT_EQ(get_date(null_date), EXIT_FAILURE);
}

TEST(len_of_string, t1) {
  char string[4] = {'1', '2', '3', END_OF_STRING};
  ASSERT_EQ(len_of_string(string), 3);
}

TEST(len_of_string, t2) {
  char* string = NULL;
  ASSERT_EQ(len_of_string(string), EXIT_FAILURE);
}

TEST(check_correct_date, t1) {
  const int* date = NULL;
  ASSERT_EQ(check_correct_date(date), EXIT_FAILURE);
}

TEST(check_correct_date, t2) {
  const int uncorrect_date[3] = {32, 12, 2000};
  ASSERT_EQ(check_correct_date(uncorrect_date), EXIT_FAILURE);
}

TEST(check_correct_date, t3) {
  const int uncorrect_date[3] = {31, 13, 2000};
  ASSERT_EQ(check_correct_date(uncorrect_date), EXIT_FAILURE);
}

TEST(check_correct_date, t4) {
  const int uncorrect_date[3] = {31, 12, 3000};
  ASSERT_EQ(check_correct_date(uncorrect_date), EXIT_FAILURE);
}

TEST(check_correct_date, t5) {
  const int correct_date[3] = {31, 12, 2000};
  ASSERT_EQ(check_correct_date(correct_date), EXIT_SUCCESS);
}

TEST(printf_task, t1) {
  const DevelopmentTask* my_task = NULL;
  ASSERT_EQ(printf_task(my_task), EXIT_FAILURE);
}

TEST(printf_task, t2) {
  char string[4] = {'1', '2', '3', END_OF_STRING};
  int correct_date[3] = {31, 12, 2000};
  DevelopmentTask* my_task = create_DevelopmentTask(1, string, 1, correct_date);
  ASSERT_EQ(printf_task(my_task), EXIT_SUCCESS);
  free_development_task(my_task);
}

TEST(printf_task, t3) {
  char* string = NULL;
  int correct_date[3] = {31, 12, 2000};
  DevelopmentTask* my_task = create_DevelopmentTask(1, string, 1, correct_date);
  ASSERT_EQ(printf_task(my_task), EXIT_FAILURE);
  free_development_task(my_task);
}

TEST(free_development_task, t1) {
  DevelopmentTask* null_task = NULL;
  ASSERT_EQ(free_development_task(null_task), EXIT_FAILURE);
}

TEST(free_development_task, t2) {
  char string[4] = {'1', '2', '3', END_OF_STRING};
  int correct_date[3] = {31, 12, 2000};
  DevelopmentTask* my_task = create_DevelopmentTask(1, string, 1, correct_date);
  ASSERT_EQ(free_development_task(my_task), EXIT_SUCCESS);
}

TEST(distribution_sort, t1) {
  DevelopmentTask** null_tasks = NULL;
  ASSERT_TRUE(distribution_sort(1, 1, null_tasks, 0) == NULL);
}

//проверим сортировку двух задач по одному ключу, например по дню недели
TEST(distribution_sort, t2) {
  size_t size_of_tasks = 2;
  DevelopmentTask** not_sorted_tasks =
      (DevelopmentTask**)malloc(size_of_tasks * sizeof(DevelopmentTask*));
  int first_date[3] = {31, 10, 2020};
  int second_date[3] = {20, 10, 2020};  // должна стать первой
  char description[4] = {'1', '2', '3', END_OF_STRING};
  int number = 0;
  int priority = MIN_PRIORITY;
  not_sorted_tasks[0] =
      create_DevelopmentTask(number, description, priority, first_date);
  not_sorted_tasks[1] =
      create_DevelopmentTask(number, description, priority, second_date);

  int key = NUMBER_OF_DAYS;
  not_sorted_tasks =
      distribution_sort(key, key, not_sorted_tasks, size_of_tasks);
  ASSERT_EQ(not_sorted_tasks[0]->production_date[0], second_date[0]);
  ASSERT_EQ(not_sorted_tasks[1]->production_date[0], first_date[0]);

  for (size_t i = 0; i < size_of_tasks; ++i) {
    free_development_task(not_sorted_tasks[i]);
  }
  free(not_sorted_tasks);
}

TEST(radix_sort, t1) {
  DevelopmentTask** null_tasks = NULL;
  const size_t size_of_keys = 4;
  int keys[size_of_keys] = {NUMBER_OF_DAYS, NUMBER_OF_MONTHS, NUMBER_OF_YEARS,
                            MAX_PRIORITY};
  ASSERT_TRUE(radix_sort(keys, size_of_keys, null_tasks, 0) == NULL);
}

/*
 * Тестовые данные
кол-во записей 4
приоритет 1: 9 -> должна стать третьей задачей
дата 1:23 12 2000
приоритет 2: 9 -> ... 2
дата 2: 22 12 2000
приоритет 3: 9 -> ... 4
дата 3: 2 2 2001
приоритет 4: 10 -> ... 1
дата 4: 2 2 2020
 */
TEST(radix_sort, t2) {
  size_t size_of_tasks = 4;
  int first_date[3] = {23, 12, 2000};
  int second_date[3] = {22, 12, 2000};
  int third_date[3] = {2, 2, 2001};
  int fourth_date[3] = {2, 2, 2020};

  int first_priority = 9;
  int second_priority = 9;
  int third_priority = 9;
  int fourth_priority = 10;

  char description[4] = {'1', '2', '3', END_OF_STRING};
  int number = 0;

  DevelopmentTask** tasks =
      (DevelopmentTask**)malloc(size_of_tasks * sizeof(DevelopmentTask*));

  tasks[0] = create_DevelopmentTask(number, description, first_priority,
                                    first_date);  // должна стать третьей
  tasks[1] = create_DevelopmentTask(number, description, second_priority,
                                    second_date);  // должна стать второй
  tasks[2] = create_DevelopmentTask(number, description, third_priority,
                                    third_date);  // должна стать четвертой
  tasks[3] = create_DevelopmentTask(number, description, fourth_priority,
                                    fourth_date);  // должна стать первой

  const size_t size_of_keys = 4;
  int keys[size_of_keys] = {NUMBER_OF_DAYS, NUMBER_OF_MONTHS, NUMBER_OF_YEARS,
                            MAX_PRIORITY};
  DevelopmentTask** sorted_tasks;
  sorted_tasks = radix_sort(keys, size_of_keys, tasks, size_of_tasks);
  ASSERT_EQ(sorted_tasks[0]->priority, tasks[3]->priority);
  ASSERT_EQ(sorted_tasks[0]->production_date[0], tasks[3]->production_date[0]);
  ASSERT_EQ(sorted_tasks[0]->production_date[1], tasks[3]->production_date[1]);
  ASSERT_EQ(sorted_tasks[0]->production_date[2], tasks[3]->production_date[2]);

  ASSERT_EQ(sorted_tasks[1]->priority, tasks[1]->priority);
  ASSERT_EQ(sorted_tasks[1]->production_date[0], tasks[1]->production_date[0]);
  ASSERT_EQ(sorted_tasks[1]->production_date[1], tasks[1]->production_date[1]);
  ASSERT_EQ(sorted_tasks[1]->production_date[2], tasks[1]->production_date[2]);

  ASSERT_EQ(sorted_tasks[2]->priority, tasks[0]->priority);
  ASSERT_EQ(sorted_tasks[2]->production_date[0], tasks[0]->production_date[0]);
  ASSERT_EQ(sorted_tasks[2]->production_date[1], tasks[0]->production_date[1]);
  ASSERT_EQ(sorted_tasks[2]->production_date[2], tasks[0]->production_date[2]);

  ASSERT_EQ(sorted_tasks[3]->priority, tasks[2]->priority);
  ASSERT_EQ(sorted_tasks[3]->production_date[0], tasks[2]->production_date[0]);
  ASSERT_EQ(sorted_tasks[3]->production_date[1], tasks[2]->production_date[1]);
  ASSERT_EQ(sorted_tasks[3]->production_date[2], tasks[2]->production_date[2]);

  for (size_t i = 0; i < size_of_tasks; ++i) {
    free_development_task(tasks[i]);
  }
  free(tasks);
  free(sorted_tasks);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}