#include "const_static_test.h"

int TestClass::s = 6;

TestClass::TestClass() :
  c(5) {
  printf("c is %d, s is %d\n", c, s);
}

TestClass::~TestClass() {
}

int main(int argc, char *argv[]) {
  TestClass *test = new TestClass();
}
