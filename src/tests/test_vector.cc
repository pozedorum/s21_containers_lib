#include <gtest/gtest.h>

#include <vector>

#include "../s21_containers.h"

TEST(VectorConstructorTest, DefaultConstructor) {
  std::vector<int> std_vec;
  s21::Vector<int> custom_vec;
  EXPECT_EQ(std_vec.size(), custom_vec.size());
  EXPECT_EQ(std_vec.capacity(), custom_vec.capacity());
}

TEST(VectorConstructorTest, Constructor) {
  std::vector<int> std_vec(2);
  s21::Vector<int> custom_vec(2);
  EXPECT_EQ(std_vec.size(), custom_vec.size());
  EXPECT_EQ(std_vec.capacity(), custom_vec.capacity());
}

TEST(VectorConstructorTest, ConstructorError) {
  EXPECT_THROW(s21::Vector<int> custom_vec(-5), std::bad_array_new_length);
}

TEST(VectorConstructorTest, CopyConstructor) {
  s21::Vector<int> source2 = {1, 2, 3, 4, 5};
  s21::Vector<int> custom_vec(source2);
  EXPECT_EQ(custom_vec.size(), 5);
  EXPECT_EQ(custom_vec[0], 1);
  EXPECT_EQ(custom_vec[3], 4);
  EXPECT_EQ(custom_vec[4], 5);
}

TEST(VectorConstructorTest, MoveConstructor) {
  s21::Vector<int> source = {1, 2, 3, 4, 5};
  s21::Vector<int> temp(source);
  s21::Vector<int> custom_temp(temp);
  s21::Vector<int> custom_vec(std::move(custom_temp));
  EXPECT_EQ(temp.size(), 5);
  EXPECT_EQ(custom_temp.size(), 0);
  for (size_t i = 0; i < source.size(); ++i) {
    EXPECT_EQ(source[i], custom_vec[i]);
  }
}

TEST(VectorElementAccessTest, At) {
  s21::Vector<int> custom_vec = {1, 2, 3, 4, 5};
  std::vector<int> std_vec = {1, 2, 3, 4, 5};
  const size_t index = 2;
  EXPECT_EQ(custom_vec.at(index), std_vec.at(index));
}

TEST(VectorElementAccessTest, OperatorBracket) {
  s21::Vector<int> custom_vec = {1, 2, 3, 4, 5};
  std::vector<int> std_vec = {1, 2, 3, 4, 5};
  const size_t index = 3;
  EXPECT_EQ(custom_vec[index], std_vec[index]);
}

TEST(VectorElementAccessTest, Operator) {
  s21::Vector<int> custom_vec{1, 2, 3, 4, 5};
  s21::Vector<int> new_vec;
  new_vec = std::move(custom_vec);
  EXPECT_EQ(new_vec[0], 1);
}

TEST(VectorElementAccessTest, Front) {
  s21::Vector<int> custom_vec = {1, 2, 3, 4, 5};
  std::vector<int> std_vec = {1, 2, 3, 4, 5};
  EXPECT_EQ(custom_vec.front(), std_vec.front());
}

TEST(VectorElementAccessTest, Back) {
  s21::Vector<int> custom_vec = {1, 2, 3, 4, 5};
  std::vector<int> std_vec = {1, 2, 3, 4, 5};
  EXPECT_EQ(custom_vec.back(), std_vec.back());
}

TEST(VectorElementAccessTest, Data) {
  s21::Vector<int> custom_vec = {1, 2, 3, 4, 5};
  std::vector<int> std_vec = {1, 2, 3, 4, 5};
  int* custom_data_ptr = custom_vec.data();
  int* std_data_ptr = std_vec.data();
  EXPECT_EQ(*custom_data_ptr, *std_data_ptr);
}

TEST(VectorIteratorTest, Begin) {
  s21::Vector<int> custom_vec = {1, 2, 3, 4, 5};
  std::vector<int> std_vec = {1, 2, 3, 4, 5};
  EXPECT_EQ(*custom_vec.begin(), *std_vec.begin());
}

TEST(VectorIteratorTest, End) {
  s21::Vector<int> custom_vec = {1, 2, 3, 4, 5};
  EXPECT_EQ(*(custom_vec.end()), 5);
}

TEST(VectorCapacityTest, Empty) {
  s21::Vector<int> custom_vec;
  std::vector<int> std_vec;
  EXPECT_EQ(custom_vec.empty(), std_vec.empty());
}

TEST(VectorCapacityTest, Size) {
  s21::Vector<int> custom_vec = {1, 2, 3, 4, 5};
  std::vector<int> std_vec = {1, 2, 3, 4, 5};
  EXPECT_EQ(custom_vec.size(), std_vec.size());
}

TEST(VectorCapacityTest, MaxSize) {
  s21::Vector<int> custom_vec;
  std::vector<int> std_vec;
  EXPECT_EQ(custom_vec.max_size(), std_vec.max_size());
}

TEST(VectorCapacityTest, Reserve) {
  s21::Vector<int> custom_vec;
  std::vector<int> std_vec;
  const size_t new_capacity = 10;
  custom_vec.reserve(new_capacity);
  std_vec.reserve(new_capacity);
  EXPECT_EQ(custom_vec.capacity(), std_vec.capacity());
}

TEST(VectorCapacityTest, Capacity) {
  s21::Vector<int> custom_vec = {1, 2, 3, 4, 5};
  std::vector<int> std_vec = {1, 2, 3, 4, 5};
  EXPECT_EQ(custom_vec.capacity(), std_vec.capacity());
}

TEST(VectorCapacityTest, ShrinkToFit) {
  s21::Vector<int> custom_vec = {1, 2, 3, 4, 5};
  std::vector<int> std_vec = {1, 2, 3, 4, 5};
  custom_vec.shrink_to_fit();
  std_vec.shrink_to_fit();
  EXPECT_EQ(custom_vec.capacity(), std_vec.capacity());
}

TEST(VectorCapacityTest, ShrinkToFit2) {
  s21::Vector<int> custom_vec = {1, 2, 3, 4, 5};
  custom_vec.pop_back();
  std::vector<int> std_vec = {1, 2, 3, 4, 5};
  std_vec.pop_back();
  custom_vec.shrink_to_fit();
  std_vec.shrink_to_fit();
  EXPECT_EQ(custom_vec.capacity(), std_vec.capacity());
}

TEST(VectorModifiersTest, Clear) {
  s21::Vector<int> custom_vec = {1, 2, 3, 4, 5};
  std::vector<int> std_vec = {1, 2, 3, 4, 5};
  custom_vec.clear();
  std_vec.clear();
  EXPECT_EQ(custom_vec.size(), std_vec.size());
}

TEST(VectorModifiersTest, Insert) {
  s21::Vector<int> custom_vec = {1, 2, 3, 4, 5};
  std::vector<int> std_vec = {1, 2, 3, 4, 5};
  const int value = 10;
  auto custom_it = custom_vec.insert(custom_vec.begin() + 2, value);
  auto std_it = std_vec.insert(std_vec.begin() + 2, value);
  EXPECT_EQ(*custom_it, *std_it);
}

TEST(VectorModifiersTest, Erase) {
  s21::Vector<int> custom_vec = {1, 2, 3, 4, 5};
  std::vector<int> std_vec = {1, 2, 3, 4, 5};
  custom_vec.erase(custom_vec.begin() + 2);
  std_vec.erase(std_vec.begin() + 2);
  for (int index = 0; index < *custom_vec.end(); index++)
    EXPECT_EQ(custom_vec[index], std_vec[index]);
}

TEST(VectorModifiersTest, Erase2) {
  s21::Vector<int> custom_vec = {1, 2, 3, 4, 5};
  custom_vec.erase(custom_vec.end());
  EXPECT_EQ(custom_vec.back(), 4);
}

TEST(VectorModifiersTest, PushBack) {
  s21::Vector<int> custom_vec = {1, 2, 3, 4, 5};
  std::vector<int> std_vec = {1, 2, 3, 4, 5};
  const int value = 10;
  custom_vec.push_back(value);
  std_vec.push_back(value);
  EXPECT_EQ(custom_vec.back(), std_vec.back());
}

TEST(VectorModifiersTest, PopBack) {
  s21::Vector<int> custom_vec = {1, 2, 3, 4, 5};
  std::vector<int> std_vec = {1, 2, 3, 4, 5};
  custom_vec.pop_back();
  std_vec.pop_back();
  EXPECT_EQ(custom_vec.size(), std_vec.size());
}

TEST(VectorModifiersTest, Swap) {
  s21::Vector<int> custom_vec1 = {1, 2, 3};
  s21::Vector<int> custom_vec2 = {4, 5};
  std::vector<int> std_vec1 = {1, 2, 3};
  std::vector<int> std_vec2 = {4, 5};
  custom_vec1.swap(custom_vec2);
  std_vec1.swap(std_vec2);
  EXPECT_EQ(custom_vec1.size(), std_vec1.size());
  EXPECT_EQ(custom_vec2.size(), std_vec2.size());
}
