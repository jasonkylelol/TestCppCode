#include <cstdio>
#include <cstdlib>
#include <cmath>

int main(int argc, char* argv[]) {
  double d = 0.0;
  double factor = 0.00001;
  if (factor - (std::abs(d)) > 0.00001) {
    printf("get! d[%.5f] factor[%.5f]\n", d, factor);
  } else {
    printf("not get! d[%.5f] factor[%.5f]\n", d, factor);
  }

  factor = 0.0001;
  if (factor - (std::abs(d)) > 0.00001) {
    printf("get! d[%.5f] factor[%.5f]\n", d, factor);
  } else {
    printf("not get! d[%.5f] factor[%.5f]\n", d, factor);
  }

  double needed_margin = (static_cast<int32_t>(((0.2 *
    500 - 101.36) +
    99.999999)) / 100) * 100.0;
  int32_t v = (static_cast<int32_t>(((0.2 * 500 - 101.36) +
    99.999999)) / 100);
  printf("needed_margin[%f] v[%d]\n", needed_margin, v);

  double f = std::abs(0.0001);
  printf("f[%f]\n", f);
  f = std::abs(-0.0001);
  printf("f[%f]\n", f);
}
