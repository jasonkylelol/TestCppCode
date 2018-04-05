#ifndef CONST_STATIC_TEST_H
#define CONST_STATIC_TEST_H

#include <cstdio>
#include <cstdlib>

class TestClass {
public:
  TestClass();
  ~TestClass();
private:
  const int c;
  static int s;
};

#endif
