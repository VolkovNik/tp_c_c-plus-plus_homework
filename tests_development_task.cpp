extern "C" {
#include "development_task.c"
}

#include "gtest/gtest.h"

TEST(get_date, t1) {
  int* null_date = NULL;
  ASSERT_EQ(get_date(null_date), EXIT_FAILURE_WITH_MNS);
}

TEST(len_of_string, t1) {
  char string[4] = {'1', '2', '3', END_OF_STRING};
  ASSERT_EQ(len_of_string(string), 3);
}

TEST(len_of_string, t2) {
  char* string = NULL;
  ASSERT_EQ(len_of_string(string), EXIT_FAILURE_WITH_MNS);
}

TEST(check_correct_date, t1) {
  const int* date = NULL;
  ASSERT_EQ(check_correct_date(date), false);
}

TEST(check_correct_date, t2) {
  const int uncorrect_date[3] = {32, 12, 2000};
  ASSERT_EQ(check_correct_date(uncorrect_date), false);
}

TEST(check_correct_date, t3) {
  const int uncorrect_date[3] = {31, 13, 2000};
  ASSERT_EQ(check_correct_date(uncorrect_date), false);
}

TEST(check_correct_date, t4) {
  const int uncorrect_date[3] = {31, 12, 3000};
  ASSERT_EQ(check_correct_date(uncorrect_date), false);
}

TEST(check_correct_date, t5) {
  const int correct_date[3] = {31, 12, 2000};
  ASSERT_EQ(check_correct_date(correct_date), true);
}

TEST(print_task, t1) {
  const development_task_t* my_task = NULL;
  ASSERT_EQ(print_task(my_task), EXIT_FAILURE);
}

TEST(print_task, t2) {
  char string[4] = {'1', '2', '3', END_OF_STRING};
  int correct_date[3] = {31, 12, 2000};
  development_task_t* my_task =
      create_development_task(1, string, 1, correct_date);
  ASSERT_EQ(print_task(my_task), EXIT_SUCCESS);
  free_development_task(my_task);
}

TEST(print_task, t3) {
  char* string = NULL;
  int correct_date[3] = {31, 12, 2000};
  development_task_t* my_task =
      create_development_task(1, string, 1, correct_date);
  ASSERT_EQ(print_task(my_task), EXIT_FAILURE);
  free_development_task(my_task);
}

TEST(free_development_task, t1) {
  development_task_t* null_task = NULL;
  ASSERT_EQ(free_development_task(null_task), EXIT_FAILURE);
}

TEST(free_development_task, t2) {
  char string[4] = {'1', '2', '3', END_OF_STRING};
  int correct_date[3] = {31, 12, 2000};
  development_task_t* my_task =
      create_development_task(1, string, 1, correct_date);
  ASSERT_EQ(free_development_task(my_task), EXIT_SUCCESS);
}

class test_sorts : public ::testing::Test {
 protected:
  void SetUp() {
    null_tasks = NULL;

    size_of_tasks = 4;

    first_priority = 9;
    second_priority = 9;
    third_priority = 9;
    fourth_priority = 10;

    number = 0;

    tasks = (development_task_t**)malloc(size_of_tasks *
                                         sizeof(development_task_t*));

    tasks[0] = create_development_task(number, description, first_priority,
                                       first_date);  // должна стать третьей
    tasks[1] = create_development_task(number, description, second_priority,
                                       second_date);  // должна стать второй
    tasks[2] = create_development_task(number, description, third_priority,
                                       third_date);  // должна стать четвертой
    tasks[3] = create_development_task(number, description, fourth_priority,
                                       fourth_date);  // должна стать первой
  }

  void TearDown() {
    for (size_t i = 0; i < size_of_tasks; ++i) {
      free_development_task(tasks[i]);
    }
    free(tasks);
  }
  int key = NUMBER_OF_DAYS;

  development_task_t** null_tasks;
  size_t size_of_tasks;

  int first_date[3] = {23, 12, 2000};
  int second_date[3] = {22, 12, 2000};
  int third_date[3] = {2, 2, 2001};
  int fourth_date[3] = {2, 2, 2020};

  int first_priority;
  int second_priority;
  int third_priority;
  int fourth_priority;

  char description[4] = {'1', '2', '3', END_OF_STRING};

  int number;

  development_task_t** tasks;

  const size_t size_of_keys = 4;

  int keys[4] = {NUMBER_OF_DAYS, NUMBER_OF_MONTHS, NUMBER_OF_YEARS,
                 MAX_PRIORITY};
};

TEST_F(test_sorts, t1) {
  ASSERT_TRUE(distribution_sort(1, 1, null_tasks, 0) == NULL);
}

/*
 * Тестовые данные
кол-во записей 2
приоритет 1: 9 -> должна стать второй задачей
дата 1:23 12 2000
приоритет 2: 9 -> должна стать первой задачей
дата 2: 22 12 2000
 */
TEST_F(test_sorts, t2) {
  size_of_tasks = 2;
  tasks = distribution_sort(key, key, tasks, size_of_tasks);

  ASSERT_EQ(tasks[0]->production_date[0], second_date[0]);
  ASSERT_EQ(tasks[1]->production_date[0], first_date[0]);
}

TEST_F(test_sorts, t3) {
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
TEST_F(test_sorts, t4) {
  development_task_t** sorted_tasks;
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

  free(sorted_tasks);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}