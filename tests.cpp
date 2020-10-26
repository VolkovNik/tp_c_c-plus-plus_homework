extern "C" {
  #include "matrix.c"
}

#include "gtest/gtest.h"

class test_sorts : public ::testing::Test {
 protected:
  void SetUp() {
    // инициализация
  }

  void TearDown() {
    // деструкторы
  }
  // объявление переменных
};


int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}