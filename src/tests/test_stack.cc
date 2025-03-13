#include <stack>

#include "../s21_containers.h"
#include "gtest/gtest.h"

TEST(stack, push_pop_top) {
  s21::stack<int> test_1;
  test_1.push(1);
  test_1.push(2);
  test_1.push(3);
  test_1.push(4);
  test_1.push(5);
  EXPECT_EQ(test_1.size(), 5);
  EXPECT_FALSE(test_1.empty());

  EXPECT_EQ(test_1.top(), 5);
  test_1.pop();
  EXPECT_EQ(test_1.top(), 4);
  test_1.pop();
  EXPECT_EQ(test_1.top(), 3);
  test_1.pop();
  EXPECT_EQ(test_1.top(), 2);
  test_1.pop();
  EXPECT_EQ(test_1.top(), 1);
  test_1.pop();
  EXPECT_TRUE(test_1.empty());
}

TEST(stack, size) {
  s21::stack<int> test_1;
  EXPECT_EQ(test_1.size(), 0);
  EXPECT_TRUE(test_1.empty());

  test_1.push(1);
  EXPECT_EQ(test_1.size(), 1);
  EXPECT_FALSE(test_1.empty());

  test_1.push(1);
  EXPECT_EQ(test_1.size(), 2);
  EXPECT_FALSE(test_1.empty());
}

TEST(stackTest, constructor) {
  s21::stack<int> test_1;

  EXPECT_TRUE(test_1.empty());
  EXPECT_EQ(test_1.size(), 0);

  test_1.push(1);
  test_1.push(2);
  test_1.push(3);
  test_1.push(4);
  test_1.push(5);

  EXPECT_EQ(test_1.top(), 5);
  EXPECT_FALSE(test_1.empty());
  EXPECT_EQ(test_1.size(), 5);
  test_1.pop();
  EXPECT_EQ(test_1.size(), 4);
  test_1.pop();
  EXPECT_EQ(test_1.size(), 3);
  EXPECT_EQ(test_1.top(), 3);
  test_1.pop();
  test_1.pop();
  test_1.pop();
  EXPECT_TRUE(test_1.empty());
}

TEST(stackTest, copy_constructor) {
  s21::stack<int> test_1;
  test_1.push(1);
  test_1.push(2);
  test_1.push(3);
  test_1.push(4);
  test_1.push(5);
  s21::stack<int> copy(test_1);
  EXPECT_EQ(copy.top(), test_1.top());
  copy.pop();
  test_1.pop();
  EXPECT_EQ(copy.top(), test_1.top());
  copy.pop();
  test_1.pop();
  EXPECT_EQ(copy.top(), test_1.top());
  copy.pop();
  test_1.pop();
  EXPECT_EQ(copy.top(), test_1.top());
  copy.pop();
  test_1.pop();
  EXPECT_EQ(copy.top(), test_1.top());
  copy.pop();
  test_1.pop();

  EXPECT_TRUE(copy.empty());
  EXPECT_TRUE(test_1.empty());

  int x = 420;
  copy.push(x);
  test_1.push(x);
  copy.push(69);
  test_1.push(69);
  EXPECT_EQ(copy.top(), test_1.top());
}

TEST(stackTest, move_constructor) {
  s21::stack<int> test_1;
  test_1.push(1);
  test_1.push(2);
  test_1.push(3);
  test_1.push(4);
  test_1.push(5);
  s21::stack<int> moved(std::move(test_1));
  EXPECT_EQ(moved.size(), 5);
  EXPECT_EQ(moved.top(), 5);
}

TEST(stackTest, copy_assignment) {
  s21::stack<int> test_1;
  test_1.push(1);
  test_1.push(2);
  test_1.push(3);
  test_1.push(4);
  test_1.push(5);
  s21::stack<int> copy;
  copy = test_1;
  EXPECT_EQ(copy.top(), test_1.top());
  copy.pop();
  test_1.pop();
  EXPECT_EQ(copy.top(), test_1.top());
  copy.pop();
  test_1.pop();
  EXPECT_EQ(copy.top(), test_1.top());
  copy.pop();
  test_1.pop();
  EXPECT_EQ(copy.top(), test_1.top());
  copy.pop();
  test_1.pop();
  EXPECT_EQ(copy.top(), test_1.top());
  copy.pop();
  test_1.pop();

  EXPECT_TRUE(copy.empty());
  EXPECT_TRUE(test_1.empty());

  copy.push(69);
  test_1.push(69);
  EXPECT_EQ(copy.top(), test_1.top());
}

TEST(stackTest, move_assignment) {
  s21::stack<int> test_1;
  test_1.push(1);
  test_1.push(2);
  test_1.push(3);
  test_1.push(4);
  test_1.push(5);
  s21::stack<int> moved;
  moved = std::move(test_1);
  EXPECT_EQ(moved.size(), 5);
  EXPECT_EQ(moved.top(), 5);
}

TEST(stackTest, swap) {
  s21::stack<int> test_1, test_2;
  test_1.push(1);
  test_1.push(2);
  test_1.push(3);
  test_1.push(4);
  test_1.push(5);
  EXPECT_EQ(test_2.size(), 0);
  EXPECT_EQ(test_1.size(), 5);
  EXPECT_FALSE(test_1.empty());
  EXPECT_TRUE(test_2.empty());
  test_1.swap(test_2);
  EXPECT_FALSE(test_2.empty());
  EXPECT_TRUE(test_1.empty());
  EXPECT_EQ(test_1.size(), 0);
  EXPECT_EQ(test_2.size(), 5);
}

TEST(stack, consts) {
  s21::stack<int> x;
  std::stack<int> y;
  int val = 69;
  x.push(val);
  y.push(val);
  x.push(val);
  x.push(val);
  y.push(val);
  y.push(val);
}

TEST(stack, initializer_list) {
  s21::stack<int> test_1{1, 2, 3, 4, 5};
  EXPECT_EQ(test_1.size(), 5);
  EXPECT_FALSE(test_1.empty());

  EXPECT_EQ(test_1.top(), 5);
  test_1.pop();
  EXPECT_EQ(test_1.top(), 4);
  test_1.pop();
  EXPECT_EQ(test_1.top(), 3);
  test_1.pop();
  EXPECT_EQ(test_1.top(), 2);
  test_1.pop();
  EXPECT_EQ(test_1.top(), 1);
  test_1.pop();
  EXPECT_TRUE(test_1.empty());
}
