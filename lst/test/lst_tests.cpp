#include "../lst.hpp"
#include <gtest/gtest.h>
#include <typeinfo>
#include <iostream>

typedef Lst<int> IntLst;
typedef Lst<float> FloatLst;
typedef Lst<const char *> StrLst;

TEST(lst_tests, empty_list) {
  IntLst l{};
  EXPECT_EQ(l.count(), 0);
  EXPECT_TRUE(l.is_empty());
}

TEST(lst_tests, insert_head) {
  IntLst l{};
  l.insert_head(123);
  l.insert_head(456);
  EXPECT_EQ(l.count(), 2);
  EXPECT_FALSE(l.is_empty());
}

TEST(lst_tests, to_string) {
  IntLst l{};
  l.insert_head(54321);
  l.insert_head(98765);
  EXPECT_EQ(l.count(), 2);
  EXPECT_FALSE(l.is_empty());
  EXPECT_STREQ(l.to_string().c_str(), "[lst{2}: 98765 54321]");
}

TEST(lst_tests, clear) {
  IntLst l{};
  l.insert_head(-400);
  l.insert_head(500);
  l.insert_head(-200);
  EXPECT_EQ(l.count(), 3);
  EXPECT_FALSE(l.is_empty());
  l.clear();
  EXPECT_EQ(l.count(), 0);
  EXPECT_TRUE(l.is_empty());
}

TEST(lst_tests, insert_after) {
  IntLst l{};
  l.insert_head(79);
  l.insert_head(89);
  l.insert_head(65);
  l.insert_head(92);
  l.insert_head(15);
  l.insert_head(14);
  l.insert_head(3);
  auto pos = l.find(65);
  l.insert_after(pos, 35);
  EXPECT_EQ(l.count(), 8);
  EXPECT_FALSE(l.is_empty());
}

TEST(lst_tests, remove_head) {
  FloatLst l{};
  l.insert_head(10.1);
  l.insert_head(-2.02);
  auto pos = l.find(10.1);
  l.insert_after(pos, 303.0);
  EXPECT_EQ(l.count(), 3);
  l.remove_head();
  EXPECT_EQ(l.count(), 2);
  // TODO: We can't do this and can't use EXPECT_FLOAT_EQ for floating point
  // comparisons unless we crack open the string
  //EXPECT_STREQ(l.to_string().c_str(), "[lst{0}: 10.1 303.0]");
  l.remove_head();
  EXPECT_EQ(l.count(), 1);
  l.remove_head();
  EXPECT_EQ(l.count(), 0);
  EXPECT_STREQ(l.to_string().c_str(), "[lst{0}:]");
  EXPECT_TRUE(l.is_empty());
}

TEST(lst_tests, list_of_const_char) {
  StrLst l{};
  l.insert_head("one");
  l.insert_head("two");
  l.insert_head("three");
  l.insert_head("four");
  EXPECT_EQ(l.count(), 4);
  EXPECT_FALSE(l.is_empty());
  auto pos = l.find("three");
  EXPECT_NE(pos, nullptr);
  EXPECT_STREQ(l.item_at(pos), "three");
  EXPECT_STREQ(l.to_string().c_str(), "[lst{4}: four three two one]");
}

TEST(lst_tests, insert_tail) {
  IntLst l{};
  l.insert_head(92);
  l.insert_head(15);
  l.insert_head(14);
  l.insert_head(3);
  EXPECT_EQ(l.count(), 4);
  l.insert_tail(65);
  EXPECT_EQ(l.count(), 5);
  EXPECT_FALSE(l.is_empty());
  EXPECT_STREQ(l.to_string().c_str(), "[lst{5}: 3 14 15 92 65]");
}

TEST(lst_tests, remove_tail) {
  IntLst l{};
  l.insert_head(1001);
  l.insert_head(101);
  l.insert_head(-201);
  auto pos = l.find(-201);
  l.insert_after(pos, 3030);
  EXPECT_EQ(l.count(), 4);
  l.remove_tail();
  EXPECT_EQ(l.count(), 3);
  EXPECT_STREQ(l.to_string().c_str(), "[lst{3}: -201 3030 101]");
  l.remove_tail();
  EXPECT_EQ(l.count(), 2);
  EXPECT_STREQ(l.to_string().c_str(), "[lst{2}: -201 3030]");
  l.remove_tail();
  EXPECT_EQ(l.count(), 1);
  EXPECT_STREQ(l.to_string().c_str(), "[lst{1}: -201]");
  l.remove_tail();
  EXPECT_EQ(l.count(), 0);
  EXPECT_STREQ(l.to_string().c_str(), "[lst{0}:]");
  EXPECT_TRUE(l.is_empty());
}

