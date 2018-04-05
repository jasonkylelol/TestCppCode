#include <iostream>

int main(int argc, char *argv[])
{
  bool b_test = false;
  // the ? : operator's priority is lower than << , so ? : is behind of cout print event.
  std::cout << "without parenthesis: " << b_test ? "true" : "false";
  std::cout << std::endl;
  // use parenthesis to wrap ? : to get the correct output.
  std::cout << "with parenthesis: " << (b_test ? "true" : "false") << std::endl;
}
