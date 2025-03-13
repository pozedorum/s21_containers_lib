#include <gtest/gtest.h>

#include <queue>

#include "../s21_containers.h"

template <typename value_type>
bool check_eq(s21::queue<value_type> m_queue,
              std::queue<value_type> orig_queue) {
  bool result = true;
  if (m_queue.size() == orig_queue.size()) {
    while (!m_queue.empty() && !orig_queue.empty()) {
      if (m_queue.front() != orig_queue.front()) {
        result = false;
        break;
      }
      m_queue.pop();
      orig_queue.pop();
    }
  } else {
    result = false;
  }
  return result;
}

TEST(Queue_test, construct_def_empty) {
  s21::queue<int> queue_my;
  EXPECT_THROW(queue_my.back(), std::logic_error);

  s21::queue<int> queue_my1;
  queue_my1.push(1);
  queue_my1.push(2);
  queue_my1.push(3);
  queue_my1.push(4);

  std::queue<int> queue_orig;
  queue_orig.push(1);
  queue_orig.push(2);
  queue_orig.push(3);
  queue_orig.push(4);

  int kek = queue_my1.front();
  int kek_orig = queue_orig.front();
  int kek_back = queue_my1.back();
  int kek_orig_back = queue_orig.back();
  EXPECT_EQ(queue_my1.size(), 4);
  EXPECT_EQ(kek, kek_orig);
  EXPECT_EQ(kek_back, kek_orig_back);
}

TEST(Queue_test, queue) {
  s21::queue<int> queue_my;
  s21::queue<int> queue_my1;
  queue_my.push(1);
  queue_my.push(2);
  queue_my.push(3);
  queue_my1.push(1);
  queue_my1.push(2);
  queue_my1.push(3);
  queue_my.pop();
  queue_my.pop();
  queue_my.front();
  queue_my.back();
  queue_my = queue_my1;
}

TEST(Queue_test, front) {
  s21::queue<int> queue_my;
  EXPECT_THROW(queue_my.front(), std::logic_error);
}

TEST(Queue_test, empty) {
  s21::queue<int> queue_my1;
  std::queue<int> queue_orig;
  EXPECT_EQ(queue_my1.empty(), queue_orig.empty());
}

TEST(Queue_test, swap) {
  s21::queue<int> kek = {1, 2, 3, 5, 6, 7};
  s21::queue<int> kek2 = {55, 22, 53, 8342, 5643, 422};
  kek.swap(kek2);
  EXPECT_EQ(kek.back(), 422);
  EXPECT_EQ(kek.front(), 55);
}

TEST(Queue_test, not_eq_length) {
  s21::queue<int> kek = {1, 2, 3, 5, 6, 7};
  s21::queue<int> kek2 = {55, 22, 53, 8342, 5643, 422, 44, 76, 33};
  kek.swap(kek2);
  EXPECT_EQ(kek.back(), 33);
  EXPECT_EQ(kek.front(), 55);
}

TEST(Queue_test, empty_swap) {
  s21::queue<int> kek;
  s21::queue<int> kek2;
  kek.swap(kek2);
  EXPECT_THROW(kek.back(), std::logic_error);
  EXPECT_THROW(kek.front(), std::logic_error);
}

TEST(Queue_test, CompareQueues) {
  s21::queue<int> my_queue{1, 3, 10, -5, 20};
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(3);
  std_queue.push(10);
  std_queue.push(-5);
  std_queue.push(20);
  EXPECT_TRUE(check_eq(my_queue, std_queue));
  std_queue.push(20);
  EXPECT_FALSE(check_eq(my_queue, std_queue));
}

TEST(Queue_test, pop) {
  s21::queue<int> queue{1, 3, 10, -5, 20, 21};
  std::queue<int> queue_orig;
  queue_orig.push(1);
  queue_orig.push(3);
  queue_orig.push(10);
  queue_orig.push(-5);
  queue_orig.push(20);
  queue_orig.push(21);
  queue.pop();
  queue.pop();
  queue_orig.pop();
  queue_orig.pop();
  EXPECT_TRUE(check_eq(queue, queue_orig));
  EXPECT_EQ(queue.front(), 10);

  s21::queue<int> empty_kek;
  EXPECT_THROW(empty_kek.back(), std::logic_error);
  EXPECT_THROW(empty_kek.pop(), std::logic_error);
  EXPECT_THROW(empty_kek.front(), std::logic_error);
}

TEST(Queue_test, InitializerqueueConstructor_2) {
  std::initializer_list<int> b;
  s21::queue<int> queue{b};
  std::queue<int> queue_orig{b};
  EXPECT_TRUE(check_eq(queue, queue_orig));
}

TEST(Queue_test, MoveConstructor) {
  std::queue<int> queue_orig;
  queue_orig.push(1);
  queue_orig.push(3);
  queue_orig.push(10);
  queue_orig.push(-5);
  queue_orig.push(20);
  queue_orig.push(21);

  s21::queue<int> queue_my;
  queue_my.push(1);
  queue_my.push(3);
  queue_my.push(10);
  queue_my.push(-5);
  queue_my.push(20);
  queue_my.push(21);
  EXPECT_TRUE(check_eq(queue_my, queue_orig));
}
