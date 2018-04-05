#include <cstdio>
#include <string>

int main(int argc, char *argv[]) {
  // core dump at this place
  // double d = std::stod("");
  // printf("d is %f\n", d);

  try {
    int i = std::stoi("7");
    printf("i is %d\n", i);
    double d = std::stod("");
    printf("d is %f\n", d);
  } catch (const std::exception &e) {
    printf("catch an exception: %s\n", e.what());
  }
}

