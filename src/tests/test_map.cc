
#include <gtest/gtest.h>

#include <map>

#include "../s21_containers.h"

// STANDART CONSTRUCTOR
TEST(map_constructor, case1) {
  s21::map<int, int> s21_map_int;
  s21::map<double, double> s21_map_double;
  s21::map<std::string, std::string> s21_map_string;

  EXPECT_EQ(s21_map_int.size(), 0U);
  EXPECT_EQ(s21_map_double.size(), 0U);
  EXPECT_EQ(s21_map_string.size(), 0U);
}

TEST(map_constructor, case2) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};

  s21::map<int, double> s21_map = {pair1, pair2, pair3};

  EXPECT_EQ(s21_map.size(), 3U);
}

TEST(map_constructor, case3) {
  std::pair<double, std::string> pair1{1.4, "hello"};
  std::pair<double, std::string> pair2{2.77, "hi"};
  std::pair<double, std::string> pair3{3.9, "hola"};

  s21::map<double, std::string> s21_map = {pair1, pair2, pair3};

  EXPECT_EQ(s21_map.size(), 3U);
}

TEST(map_constructor, case4) {
  std::pair<std::string, int> pair1{"hello", 1};
  std::pair<std::string, int> pair2{"hi", 2};
  std::pair<std::string, int> pair3{"hola", 3};

  s21::map<std::string, int> s21_map = {pair1, pair2, pair3};

  EXPECT_EQ(s21_map.size(), 3U);
}

TEST(map_constructor, case5) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<double, std::string> pair2{2.77, "hi"};
  std::pair<std::string, int> pair3{"hola", 3};

  s21::map<int, double> s21_map_int{pair1};
  s21::map<double, std::string> s21_map_double{pair2};
  s21::map<std::string, int> s21_map_string{pair3};

  EXPECT_EQ(s21_map_int.size(), 1U);
  EXPECT_EQ(s21_map_double.size(), 1U);
  EXPECT_EQ(s21_map_string.size(), 1U);

  s21::Tree<int, double> s21_tree_int(pair1.first, pair1.second);
  s21::Tree<double, std::string> s21_tree_double(pair2.first, pair2.second);
  s21::Tree<std::string, int> s21_tree_string(pair3.first, pair3.second);

  EXPECT_EQ(s21_tree_int.size(), 1U);
  EXPECT_EQ(s21_tree_double.size(), 1U);
  EXPECT_EQ(s21_tree_string.size(), 1U);
}

// CONSTRUCTOR COPY

TEST(map_constructor, case6) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};

  s21::map<int, double> s21_map_ref = {pair1, pair2, pair3};
  s21::map<int, double> s21_map_res(s21_map_ref);

  EXPECT_EQ(s21_map_res.size(), s21_map_ref.size());
}

TEST(map_constructor, case7) {
  std::pair<double, std::string> pair1{1.4, "hello"};
  std::pair<double, std::string> pair2{2.77, "hi"};
  std::pair<double, std::string> pair3{3.9, "hola"};

  s21::map<double, std::string> s21_map_ref = {pair1, pair2, pair3};
  s21::map<double, std::string> s21_map_res(s21_map_ref);

  EXPECT_EQ(s21_map_res.size(), s21_map_ref.size());
}

TEST(map_constructor, case8) {
  std::pair<std::string, int> pair1{"hello", 1};
  std::pair<std::string, int> pair2{"hi", 2};
  std::pair<std::string, int> pair3{"hola", 3};

  s21::map<std::string, int> s21_map_ref = {pair1, pair2, pair3};
  s21::map<std::string, int> s21_map_res(s21_map_ref);

  EXPECT_EQ(s21_map_res.size(), s21_map_ref.size());
}

// CONSTRUCTOR MOVE

TEST(map_constructor, case9) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};

  s21::map<int, double> s21_map_ref = {pair1, pair2, pair3};
  s21::map<int, double> s21_map_res = std::move(s21_map_ref);

  EXPECT_EQ(s21_map_ref.size(), 0U);
  EXPECT_EQ(s21_map_res.size(), 3U);
}

TEST(map_constructor, case10) {
  std::pair<double, std::string> pair1{1.4, "hello"};
  std::pair<double, std::string> pair2{2.77, "hi"};
  std::pair<double, std::string> pair3{3.9, "hola"};

  s21::map<double, std::string> s21_map_ref = {pair1, pair2, pair3};
  s21::map<double, std::string> s21_map_res = std::move(s21_map_ref);

  EXPECT_EQ(s21_map_ref.size(), 0U);
  EXPECT_EQ(s21_map_res.size(), 3U);
}

TEST(map_constructor, case11) {
  std::pair<std::string, int> pair1{"hello", 1};
  std::pair<std::string, int> pair2{"hi", 2};
  std::pair<std::string, int> pair3{"hola", 3};

  s21::map<std::string, int> s21_map_ref = {pair1, pair2, pair3};
  s21::map<std::string, int> s21_map_res = std::move(s21_map_ref);

  EXPECT_EQ(s21_map_ref.size(), 0U);
  EXPECT_EQ(s21_map_res.size(), 3U);
}

// // OPERATOR =

TEST(map_constructor, case12) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};

  s21::map<int, double> s21_map_ref = {pair1, pair2, pair3};
  s21::map<int, double> s21_map_res;
  s21_map_res = std::move(s21_map_ref);

  EXPECT_EQ(s21_map_ref.size(), 0U);
  EXPECT_EQ(s21_map_res.size(), 3U);
}

TEST(map_constructor, case13) {
  std::pair<double, std::string> pair1{1.4, "hello"};
  std::pair<double, std::string> pair2{2.77, "hi"};
  std::pair<double, std::string> pair3{3.9, "hola"};

  s21::map<double, std::string> s21_map_ref = {pair1, pair2, pair3};

  s21::map<double, std::string> s21_map_res;
  s21_map_res = std::move(s21_map_ref);

  EXPECT_EQ(s21_map_ref.size(), 0U);
  EXPECT_EQ(s21_map_res.size(), 3U);
}

TEST(map_constructor, case14) {
  std::pair<std::string, int> pair1{"hello", 1};
  std::pair<std::string, int> pair2{"hi", 2};
  std::pair<std::string, int> pair3{"hola", 3};

  s21::map<std::string, int> s21_map_ref = {pair1, pair2, pair3};

  s21::map<std::string, int> s21_map_res;
  s21_map_res = std::move(s21_map_ref);

  EXPECT_EQ(s21_map_ref.size(), 0U);
  EXPECT_EQ(s21_map_res.size(), 3U);
}

TEST(map_constructor, case15) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};

  s21::map<int, double> s21_map_ref_int{pair1, pair2, pair3};
  s21::map<int, double> s21_map_res_int{s21_map_ref_int};

  std::pair<double, std::string> pair4{1.4, "hello"};
  std::pair<double, std::string> pair5{2.77, "hi"};
  std::pair<double, std::string> pair6{3.9, "hola"};

  s21::map<double, std::string> s21_map_ref_double{pair4, pair5, pair6};
  s21::map<double, std::string> s21_map_res_double{s21_map_ref_double};

  std::pair<std::string, int> pair7{"hello", 1};
  std::pair<std::string, int> pair8{"hi", 2};
  std::pair<std::string, int> pair9{"hola", 3};

  s21::map<std::string, int> s21_map_ref_string{pair7, pair8, pair9};
  s21::map<std::string, int> s21_map_res_string{s21_map_ref_string};

  auto it_res_int = s21_map_res_int.begin();
  for (auto it_ref_int = s21_map_ref_int.begin();
       it_ref_int != s21_map_ref_int.end(); ++it_ref_int) {
    EXPECT_EQ(it_res_int->value_, it_ref_int->value_);
    ++it_res_int;
  }

  auto it_res_double = s21_map_res_double.begin();
  for (auto it_ref_double = s21_map_ref_double.begin();
       it_ref_double != s21_map_ref_double.end(); ++it_ref_double) {
    EXPECT_EQ(it_res_double->value_, it_ref_double->value_);
    ++it_res_double;
  }

  auto it_res_string = s21_map_res_string.begin();
  for (auto it_ref_string = s21_map_ref_string.begin();
       it_ref_string != s21_map_ref_string.end(); ++it_ref_string) {
    EXPECT_EQ(it_res_string->value_, it_ref_string->value_);
    ++it_res_string;
  }
}

// INSERT

TEST(map_insert, case1) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{9, 1.4};
  std::pair<int, double> pair3{9, 1.4};
  std::pair<int, double> pair4{23, 2.77};
  std::pair<int, double> pair5{98, 3.9};

  s21::map<int, double> s21_map;

  std::pair<s21::map<int, double>::iterator, bool> insert1 =
      s21_map.insert(pair1);
  EXPECT_EQ(insert1.first->key_, 9);
  EXPECT_EQ(insert1.second, 1);

  std::pair<s21::map<int, double>::iterator, bool> insert2 =
      s21_map.insert(pair2);
  std::pair<s21::map<int, double>::iterator, bool> insert3 =
      s21_map.insert(pair3);
  EXPECT_EQ(insert2.second, 0);
  EXPECT_EQ(insert3.second, 0);

  std::pair<s21::map<int, double>::iterator, bool> insert4 =
      s21_map.insert(pair4);
  EXPECT_EQ(insert4.first->key_, 23);
  EXPECT_EQ(insert4.second, 1);

  std::pair<s21::map<int, double>::iterator, bool> insert5 =
      s21_map.insert(pair5);
  EXPECT_EQ(insert5.first->key_, 98);
  EXPECT_EQ(insert5.second, 1);

  EXPECT_EQ(s21_map.size(), 3U);
}

TEST(map_insert, case2) {
  std::pair<double, std::string> pair1{1.4, "hello"};
  std::pair<double, std::string> pair2{2.77, "hi"};
  std::pair<double, std::string> pair3{3.9, "hola"};
  std::pair<double, std::string> pair4{2.77, "hi"};
  std::pair<double, std::string> pair5{3.9, "hola"};

  s21::map<double, std::string> s21_map;

  std::pair<s21::map<double, std::string>::iterator, bool> insert1 =
      s21_map.insert(pair1);
  EXPECT_EQ(insert1.first->key_, 1.4);
  EXPECT_EQ(insert1.second, 1);

  std::pair<s21::map<double, std::string>::iterator, bool> insert2 =
      s21_map.insert(pair2);
  EXPECT_EQ(insert2.first->key_, 2.77);
  EXPECT_EQ(insert2.second, 1);

  std::pair<s21::map<double, std::string>::iterator, bool> insert3 =
      s21_map.insert(pair3);
  EXPECT_EQ(insert3.first->key_, 3.9);
  EXPECT_EQ(insert3.second, 1);

  std::pair<s21::map<double, std::string>::iterator, bool> insert4 =
      s21_map.insert(pair4);
  std::pair<s21::map<double, std::string>::iterator, bool> insert5 =
      s21_map.insert(pair5);
  EXPECT_EQ(insert4.second, 0);
  EXPECT_EQ(insert5.second, 0);

  EXPECT_EQ(s21_map.size(), 3U);
}

TEST(map_insert, case3) {
  std::pair<std::string, int> pair1{"hello", 1};
  std::pair<std::string, int> pair2{"hi", 2};
  std::pair<std::string, int> pair3{"hi", 2};
  std::pair<std::string, int> pair4{"hola", 3};
  std::pair<std::string, int> pair5{"hello", 1};

  s21::map<std::string, int> s21_map;

  std::pair<s21::map<std::string, int>::iterator, bool> insert1 =
      s21_map.insert(pair1);
  EXPECT_EQ(insert1.first->key_, "hello");
  EXPECT_EQ(insert1.second, 1);

  std::pair<s21::map<std::string, int>::iterator, bool> insert2 =
      s21_map.insert(pair2);
  EXPECT_EQ(insert2.first->key_, "hi");
  EXPECT_EQ(insert2.second, 1);

  std::pair<s21::map<std::string, int>::iterator, bool> insert3 =
      s21_map.insert(pair3);
  EXPECT_EQ(insert3.second, 0);

  std::pair<s21::map<std::string, int>::iterator, bool> insert4 =
      s21_map.insert(pair4);
  EXPECT_EQ(insert4.first->key_, "hola");
  EXPECT_EQ(insert4.second, 1);

  std::pair<s21::map<std::string, int>::iterator, bool> insert5 =
      s21_map.insert(pair5);
  EXPECT_EQ(insert5.second, 0);

  EXPECT_EQ(s21_map.size(), 3U);
}

TEST(map_insert, case4) {
  std::pair<int, double> pair1{9, 1.4};

  s21::map<int, double> s21_map;

  std::pair<s21::map<int, double>::iterator, bool> insert1 =
      s21_map.insert(pair1);
  EXPECT_EQ(insert1.first->key_, 9);
  EXPECT_EQ(insert1.second, 1);

  std::pair<s21::map<int, double>::iterator, bool> insert2 =
      s21_map.insert(pair1);
  std::pair<s21::map<int, double>::iterator, bool> insert3 =
      s21_map.insert(pair1);
  EXPECT_EQ(insert2.second, 0);
  EXPECT_EQ(insert3.second, 0);

  EXPECT_EQ(s21_map.size(), 1U);
}

TEST(map_insert, case5) {
  std::pair<double, std::string> pair1{1.4, "hello"};

  s21::map<double, std::string> s21_map = {pair1};

  std::pair<s21::map<double, std::string>::iterator, bool> insert1 =
      s21_map.insert(pair1);
  EXPECT_EQ(insert1.second, 0);

  EXPECT_EQ(s21_map.size(), 1U);
}

TEST(map_insert, case6) {
  std::pair<std::string, int> pair1{"hello", 1};
  std::pair<std::string, int> pair2{"hi", 2};

  s21::map<std::string, int> s21_map = {pair1};

  std::pair<s21::map<std::string, int>::iterator, bool> insert1 =
      s21_map.insert(pair2);
  EXPECT_EQ(insert1.first->key_, "hi");
  EXPECT_EQ(insert1.second, 1);

  EXPECT_EQ(s21_map.size(), 2U);
}

// // ITERATOR BEGIN

TEST(map_begin, case1) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{15, 1.456};
  std::pair<int, double> pair3{7, 151.4};
  std::pair<int, double> pair4{23, 2.77};
  std::pair<int, double> pair5{2, 3.9};

  s21::map<int, double> s21_map = {pair1, pair2, pair3, pair4, pair5};

  auto min_value = s21_map.begin();

  EXPECT_EQ(min_value->key_, 2);
}

TEST(map_begin, case2) {
  std::pair<double, std::string> pair1{11.4, "hello"};
  std::pair<double, std::string> pair2{2.770001, "hee"};
  std::pair<double, std::string> pair3{3.901, "hola"};
  std::pair<double, std::string> pair4{2.77, "hi"};
  std::pair<double, std::string> pair5{3.9, "hee-hee"};

  s21::map<double, std::string> s21_map = {pair1, pair2, pair3, pair4, pair5};

  auto min_value = s21_map.begin();

  EXPECT_EQ(min_value->key_, 2.77);
}

TEST(map_begin, case3) {
  std::pair<std::string, int> pair1{"hello", 1};
  std::pair<std::string, int> pair2{"hi", 2};
  std::pair<std::string, int> pair3{"hi-hi", 2};
  std::pair<std::string, int> pair4{"hola", 3};
  std::pair<std::string, int> pair5{"hello, there", 1};

  s21::map<std::string, int> s21_map = {pair1, pair2, pair3, pair4, pair5};

  auto min_value = s21_map.begin();

  EXPECT_EQ(min_value->key_, "hello");
}

// TEST(map_begin, case4) {
//   s21::map<int, double> s21_map;

//   EXPECT_THROW(s21_map.begin(), std::out_of_range);
// }

TEST(map_begin, case5) {
  std::pair<double, std::string> pair1{1.4, "hello"};

  s21::map<double, std::string> s21_map = {pair1, pair1};

  auto min_value = s21_map.begin();

  EXPECT_EQ(min_value->key_, 1.4);
  EXPECT_EQ(min_value->value_, "hello");
}

TEST(map_begin, case6) {
  std::pair<std::string, int> pair1{"hello", 1};
  std::pair<std::string, int> pair2{"hello", 2};
  std::pair<std::string, int> pair3{"hello", 45};

  s21::map<std::string, int> s21_map = {pair1, pair2, pair3};

  auto min_value = s21_map.begin();

  EXPECT_EQ(min_value->key_, "hello");
  EXPECT_EQ(min_value->value_, 1);
}

// // ITERATOR END

TEST(map_end, case1) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{15, 1.456};
  std::pair<int, double> pair3{7, 151.4};
  std::pair<int, double> pair4{23, 2.77};
  std::pair<int, double> pair5{2, 3.9};

  s21::map<int, double> s21_map = {pair1, pair2, pair3, pair4, pair5};

  auto max_value = s21_map.end();

  EXPECT_EQ(max_value->key_, 23);
}

TEST(map_end, case2) {
  std::pair<double, std::string> pair1{11.4, "hello"};
  std::pair<double, std::string> pair2{2.770001, "hee"};
  std::pair<double, std::string> pair3{3.901, "hola"};
  std::pair<double, std::string> pair4{11.400000001, "hi"};
  std::pair<double, std::string> pair5{3.9, "hee-hee"};

  s21::map<double, std::string> s21_map = {pair1, pair2, pair3, pair4, pair5};

  auto max_value = s21_map.end();

  EXPECT_EQ(max_value->key_, 11.400000001);
}

TEST(map_end, case3) {
  std::pair<std::string, int> pair1{"hello", 1};
  std::pair<std::string, int> pair2{"hi", 2};
  std::pair<std::string, int> pair3{"hola-hola", 2};
  std::pair<std::string, int> pair4{"hola", 3};
  std::pair<std::string, int> pair5{"hello, there", 1};

  s21::map<std::string, int> s21_map = {pair1, pair2, pair3, pair4, pair5};

  auto max_value = s21_map.end();

  EXPECT_EQ(max_value->key_, "hola-hola");
}

// TEST(map_end, case4) {
//   s21::map<int, double> s21_map;

//   EXPECT_THROW(s21_map.end(), std::out_of_range);
// }

TEST(map_end, case5) {
  std::pair<double, std::string> pair1{1.4, "hello"};

  s21::map<double, std::string> s21_map = {pair1, pair1};

  auto max_value = s21_map.end();

  EXPECT_EQ(max_value->key_, 1.4);
  EXPECT_EQ(max_value->value_, "hello");
}

TEST(map_end, case6) {
  std::pair<std::string, int> pair1{"hello", 1};
  std::pair<std::string, int> pair2{"hello", 2};
  std::pair<std::string, int> pair3{"hello", 45};

  s21::map<std::string, int> s21_map = {pair1, pair2, pair3};

  auto max_value = s21_map.end();

  EXPECT_EQ(max_value->key_, "hello");
  EXPECT_EQ(max_value->value_, 1);
}

// // BALANCE TEST

TEST(map_balance, case1) {
  std::pair<int, int> pair1{10, 10};
  std::pair<int, int> pair2{5, 5};
  std::pair<int, int> pair3{20, 20};
  std::pair<int, int> pair4{30, 30};
  std::pair<int, int> pair5{1543, 1543};

  s21::map<int, int> s21_map = {pair1, pair2, pair3, pair4, pair5};

  EXPECT_EQ(s21_map.end()->key_, 1543);
  EXPECT_EQ(s21_map.begin()->key_, 5);
  EXPECT_EQ(s21_map.size(), 5U);
}

TEST(map_balance, case2) {
  std::pair<int, int> pair1{30, 30};
  std::pair<int, int> pair2{5, 5};
  std::pair<int, int> pair3{43, 43};
  std::pair<int, int> pair4{1, 1};
  std::pair<int, int> pair5{20, 20};
  std::pair<int, int> pair6{40, 60};
  std::pair<int, int> pair7{60, 60};
  std::pair<int, int> pair8{35, 35};
  std::pair<int, int> pair9{32, 32};

  s21::map<int, int> s21_map = {pair1, pair2, pair3, pair4, pair5,
                                pair6, pair7, pair8, pair9};

  EXPECT_EQ(s21_map.end()->key_, 60);
  EXPECT_EQ(s21_map.begin()->key_, 1);
  EXPECT_EQ(s21_map.size(), 9U);
}

// // ERASE TEST

TEST(map_erase, case1) {
  std::pair<int, int> pair1{10, 10};
  std::pair<int, int> pair2{5, 5};
  std::pair<int, int> pair3{15, 15};
  std::pair<int, int> pair4{4, 4};
  std::pair<int, int> pair5{18, 18};
  std::pair<int, int> pair6{13, 13};
  std::pair<int, int> pair7{16, 16};
  s21::map<int, int> s21_map = {pair1, pair2, pair3, pair4,
                                pair5, pair6, pair7};
  auto it = s21_map.begin();
  ++it;
  ++it;
  ++it;
  ++it;
  s21_map.erase(it);
  EXPECT_EQ(s21_map.begin()->key_, 4);
  EXPECT_EQ(s21_map.end()->key_, 18);
  EXPECT_EQ(s21_map.size(), 6U);
}

TEST(map_erase, case2) {
  std::pair<int, int> pair1{30, 30};
  std::pair<int, int> pair2{1543, 1543};
  s21::map<int, int> s21_map = {pair1, pair2};
  auto it = s21_map.begin();
  ++it;
  s21_map.erase(it);
  auto it2 = s21_map.begin();
  s21_map.erase(it2);
  EXPECT_EQ(s21_map.size(), 0U);
}
TEST(map_erase, case3) {
  std::pair<std::string, int> pair1{"hello", 1};
  std::pair<std::string, int> pair2{"hi", 2};
  std::pair<std::string, int> pair3{"hola-hola", 2};
  std::pair<std::string, int> pair4{"hola", 3};
  std::pair<std::string, int> pair5{"hello, there", 1};
  s21::map<std::string, int> s21_map = {pair1, pair2, pair3, pair4, pair5};
  auto it = s21_map.end();
  s21_map.erase(it);
  EXPECT_EQ(s21_map.end()->key_, "hola");
  EXPECT_EQ(s21_map.size(), 4U);
  auto it2 = s21_map.end();
  s21_map.erase(it2);
  EXPECT_EQ(s21_map.end()->key_, "hi");
  EXPECT_EQ(s21_map.size(), 3U);
  s21_map.insert(pair3);
  s21_map.insert(pair4);
  auto it3 = s21_map.end();
  s21_map.erase(it3);
  EXPECT_EQ(s21_map.end()->key_, "hola");
  EXPECT_EQ(s21_map.size(), 4U);
}
// // EMPTY TEST

TEST(map_empty, case1) {
  std::pair<double, int> pair1{22.2, 1};
  std::pair<double, int> pair2{44.48, 1};
  std::pair<double, int> pair3{12.4457, 2};
  std::pair<double, int> pair4{1.44, 3};

  s21::map<double, int> s21_map = {pair1, pair2, pair3, pair4};

  EXPECT_EQ(s21_map.empty(), 0);
}

TEST(map_empty, case2) {
  s21::map<double, int> s21_map;

  EXPECT_EQ(s21_map.empty(), 1);
}

// // TEST SWAP

TEST(map_swap, case1) {
  std::pair<double, int> pair1{22.2, 1};
  std::pair<double, int> pair2{44.48, 1};
  std::pair<double, int> pair3{12.4457, 2};
  std::pair<double, int> pair4{1.44, 3};
  std::pair<double, int> pair5{22.2, 15};

  s21::map<double, int> s21_map_ref = {pair1, pair2};
  s21::map<double, int> s21_map_res = {pair3, pair4, pair5};

  s21_map_ref.swap(s21_map_res);

  EXPECT_EQ(s21_map_ref.size(), 3U);
  EXPECT_EQ(s21_map_ref.begin()->key_, 1.44);

  EXPECT_EQ(s21_map_res.size(), 2U);
  EXPECT_EQ(s21_map_res.begin()->key_, 22.2);
}

TEST(map_swap, case2) {
  std::pair<double, int> pair1{22.2, 1};
  std::pair<double, int> pair2{44.48, 1};

  s21::map<double, int> s21_map_ref = {pair1, pair2};
  s21::map<double, int> s21_map_res;

  s21_map_ref.swap(s21_map_res);

  EXPECT_EQ(s21_map_ref.size(), 0U);

  EXPECT_EQ(s21_map_res.size(), 2U);
  EXPECT_EQ(s21_map_res.begin()->key_, 22.2);
}

TEST(map_swap, case3) {
  std::pair<double, int> pair1{12.4457, 2};
  std::pair<double, int> pair2{1.44, 3};
  std::pair<double, int> pair3{22.2, 15};

  s21::map<double, int> s21_map_ref;
  s21::map<double, int> s21_map_res = {pair1, pair2, pair3};

  s21_map_ref.swap(s21_map_res);

  EXPECT_EQ(s21_map_ref.size(), 3U);
  EXPECT_EQ(s21_map_ref.begin()->key_, 1.44);

  EXPECT_EQ(s21_map_res.size(), 0U);
}

// // TEST CONTAINS

TEST(map_contains, case1) {
  std::pair<double, int> pair1{22.2, 1};
  std::pair<double, int> pair2{44.48, 1};

  s21::map<double, int> s21_map_ref = {pair1, pair2};
  s21::map<double, int> s21_map_res;

  s21_map_ref.swap(s21_map_res);

  EXPECT_EQ(s21_map_ref.size(), 0U);
  EXPECT_EQ(s21_map_ref.contains(22.2), false);
  EXPECT_EQ(s21_map_ref.contains(44.48), false);

  EXPECT_EQ(s21_map_res.size(), 2U);
  EXPECT_EQ(s21_map_res.contains(22.2), true);
  EXPECT_EQ(s21_map_res.contains(44.48), true);
}

TEST(map_contains, case2) {
  std::pair<double, int> pair1{12.4457, 2};
  std::pair<double, int> pair2{1.44, 3};
  std::pair<double, int> pair3{22.2, 15};

  s21::map<double, int> s21_map_ref;
  s21::map<double, int> s21_map_res = {pair1, pair2, pair3};

  s21_map_ref.swap(s21_map_res);

  EXPECT_EQ(s21_map_ref.size(), 3U);
  EXPECT_EQ(s21_map_ref.contains(12.4457), true);
  EXPECT_EQ(s21_map_ref.contains(1.44), true);
  EXPECT_EQ(s21_map_ref.contains(22.2), true);

  EXPECT_EQ(s21_map_res.size(), 0U);
  EXPECT_EQ(s21_map_res.contains(12.4457), false);
  EXPECT_EQ(s21_map_res.contains(1.44), false);
  EXPECT_EQ(s21_map_res.contains(22.2), false);
}

TEST(map_contains, case3) {
  s21::map<double, int> s21_map;

  EXPECT_EQ(s21_map.size(), 0U);
  EXPECT_EQ(s21_map.contains(12.4457), false);
}

// // TEST AT

TEST(map_at, case1) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};
  std::pair<int, double> pair11{78, 3.9};
  std::pair<int, double> pair22{88, 3.9};
  std::pair<int, double> pair33{108, 3.9};

  s21::map<int, double> s21_map_int{pair1,  pair2,  pair3,
                                    pair11, pair22, pair33};
  EXPECT_EQ(s21_map_int.at(9), 1.4);
  EXPECT_EQ(s21_map_int.at(23), 2.77);
  EXPECT_EQ(s21_map_int.at(98), 3.9);
  EXPECT_EQ(s21_map_int.at(78), 3.9);
  EXPECT_EQ(s21_map_int.at(88), 3.9);
  EXPECT_EQ(s21_map_int.at(108), 3.9);

  std::pair<double, std::string> pair4{1.4, "hello"};
  std::pair<double, std::string> pair5{2.77, "hi"};
  std::pair<double, std::string> pair6{3.9, "hola"};

  s21::map<double, std::string> s21_map_double{pair4, pair5, pair6};
  EXPECT_EQ(s21_map_double.at(1.4), "hello");
  EXPECT_EQ(s21_map_double.at(2.77), "hi");
  EXPECT_EQ(s21_map_double.at(3.9), "hola");

  std::pair<std::string, int> pair7{"hello", 1};
  std::pair<std::string, int> pair8{"hi", 2};
  std::pair<std::string, int> pair9{"hola", 3};

  s21::map<std::string, int> s21_map_string{pair7, pair8, pair9};
  EXPECT_EQ(s21_map_string.at("hello"), 1);
  EXPECT_EQ(s21_map_string.at("hi"), 2);
  EXPECT_EQ(s21_map_string.at("hola"), 3);
}

// // TEST OPERATOR []

TEST(map_brackets, case1) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};
  std::pair<int, double> pair11{78, 3.9};
  std::pair<int, double> pair22{88, 3.9};
  std::pair<int, double> pair33{108, 3.9};

  s21::map<int, double> s21_map_int{pair1,  pair2,  pair3,
                                    pair11, pair22, pair33};
  EXPECT_EQ(s21_map_int[9], 1.4);
  EXPECT_EQ(s21_map_int[23], 2.77);
  EXPECT_EQ(s21_map_int[98], 3.9);
  EXPECT_EQ(s21_map_int[78], 3.9);
  EXPECT_EQ(s21_map_int[88], 3.9);
  EXPECT_EQ(s21_map_int[108], 3.9);

  std::pair<double, std::string> pair4{1.4, "hello"};
  std::pair<double, std::string> pair5{2.77, "hi"};
  std::pair<double, std::string> pair6{3.9, "hola"};

  s21::map<double, std::string> s21_map_double{pair4, pair5, pair6};
  EXPECT_EQ(s21_map_double[1.4], "hello");
  EXPECT_EQ(s21_map_double[2.77], "hi");
  EXPECT_EQ(s21_map_double[3.9], "hola");

  std::pair<std::string, int> pair7{"hello", 1};
  std::pair<std::string, int> pair8{"hi", 2};
  std::pair<std::string, int> pair9{"hola", 3};

  s21::map<std::string, int> s21_map_string{pair7, pair8, pair9};
  EXPECT_EQ(s21_map_string["hello"], 1);
  EXPECT_EQ(s21_map_string["hi"], 2);
  EXPECT_EQ(s21_map_string["hola"], 3);
}

TEST(map_brackets, case2) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{8, 3.9};

  s21::map<int, double> s21_map_int = {pair1, pair2, pair3};
  s21_map_int[78] = 78.0;
  s21_map_int[88] = 88.0;
  s21_map_int[108] = 108.0;

  EXPECT_EQ(s21_map_int[9], 1.4);
  EXPECT_EQ(s21_map_int[23], 2.77);
  EXPECT_EQ(s21_map_int[8], 3.9);
  EXPECT_EQ(s21_map_int[78], 78.0);
  EXPECT_EQ(s21_map_int[88], 88.0);
  EXPECT_EQ(s21_map_int[108], 108.0);

  std::pair<double, std::string> pair4{1.4, "hello"};
  std::pair<double, std::string> pair5{2.77, "hi"};
  std::pair<double, std::string> pair6{3.9, "hola"};

  s21::map<double, std::string> s21_map_double{pair4, pair5};
  s21_map_double[3.9] = "hola";

  EXPECT_EQ(s21_map_double[1.4], "hello");
  EXPECT_EQ(s21_map_double[2.77], "hi");
  EXPECT_EQ(s21_map_double[3.9], "hola");

  std::pair<std::string, int> pair7{"hello", 1};
  std::pair<std::string, int> pair8{"hi", 2};
  std::pair<std::string, int> pair9{"hola", 3};

  s21::map<std::string, int> s21_map_string{pair7};
  s21_map_string["hi"] = 2;
  s21_map_string["hola"] = 3;

  EXPECT_EQ(s21_map_string["hello"], 1);
  EXPECT_EQ(s21_map_string["hi"], 2);
  EXPECT_EQ(s21_map_string["hola"], 3);
}

// // TEST MERGE

TEST(map_merge, case1) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};

  s21::map<int, double> s21_map_int_ref{pair1, pair2, pair3};
  s21::map<int, double> s21_map_int_res;

  s21_map_int_res.merge(s21_map_int_ref);

  EXPECT_EQ(s21_map_int_res.size(), 3U);
}

TEST(map_merge, case2) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};

  s21::map<int, double> s21_map_int_ref;
  s21::map<int, double> s21_map_int_res{pair1, pair2, pair3};

  s21_map_int_res.merge(s21_map_int_ref);

  EXPECT_EQ(s21_map_int_res.size(), 3U);
}

TEST(map_merge, case3) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};
  std::pair<int, double> pair4{1, 22.2};
  std::pair<int, double> pair5{8, 44.48};
  std::pair<int, double> pair6{32, 12.4457};

  s21::map<int, double> s21_map_int_ref = {pair1, pair2, pair3, pair4};
  s21::map<int, double> s21_map_int_res = {pair5, pair6};

  s21_map_int_res.merge(s21_map_int_ref);

  EXPECT_EQ(s21_map_int_res.size(), 6U);
}
