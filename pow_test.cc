#include <cmath>
#include <cstdlib>
#include <cstdio>

int main() {
  double admin_diff = 2;
  int admin_digits=0;
  double admin_spread = (admin_diff * pow(
      10.0, static_cast<double>(-admin_digits))) / 2.0;

  printf("admin_spread[%f]\n", admin_spread);
}
