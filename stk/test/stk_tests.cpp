#include "../stk.hpp"
#include <gtest/gtest.h>
#include <typeinfo>

typedef Stk<int> IntStk;
typedef Stk<const char *> StrStk;

TEST(example_tests, dummy_test) {
  EXPECT_TRUE(true);
}

TEST(example_tests, empty_stack) {
  IntStk s{0};
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.is_empty());
}

TEST(example_tests, stack_with_capacity) {
  IntStk s{10};
  EXPECT_EQ(s.max_size(), 10);
  EXPECT_TRUE(s.is_empty());
}

TEST(example_tests, stack_push) {
  IntStk s{10};
  EXPECT_TRUE(s.is_empty());
  s.push(12);
  s.push(34);
  s.push(56);
  EXPECT_EQ(s.size(), 3);
  s.push(78);
  EXPECT_EQ(s.size(), 4);
}

TEST(example_tests, stack_pop) {
  IntStk s{6};
  EXPECT_TRUE(s.is_empty());
  s.push(1234);
  s.push(5678);
  s.push(9101112);
  s.push(13141516);
  s.push(17181920);
  EXPECT_EQ(s.size(), 5);
  int x = s.pop();
  EXPECT_EQ(x, 17181920);
  EXPECT_EQ(s.size(), 4);
}

TEST(example_tests, stack_underflow) {
  IntStk s{3};
  EXPECT_TRUE(s.is_empty());
  s.push(-1234);
  s.push(-5678);
  EXPECT_EQ(s.size(), 2);
  int x = s.pop();
  EXPECT_EQ(x, -5678);
  x = s.pop();
  try {
    x = s.pop();
    FAIL() << "Error: No exception was thrown.";
  } catch(const StackUnderflowException& e) {
    // This doesn't work, because the name returned by typeid().name() has no
    // guarantees of any correspondence to the exception name.
    //EXPECT_STREQ(typeid(e).name(), "StackUnderflowException");
    EXPECT_TRUE(true);
  } catch(...) {
    FAIL() << "Error: The incorrect exception was thrown.";
  }
}

TEST(example_tests, stack_of_const_char) {
  const int len = 8;
  StrStk s{len};
  EXPECT_TRUE(s.is_empty());
  for (int i = 0; i < len; i++) {
    s.push("a string");
  }
  EXPECT_EQ(s.size(), len);
  const char* x = s.pop();
  EXPECT_STREQ(x, "a string");
}

