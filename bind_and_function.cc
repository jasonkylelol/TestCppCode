#include <cstdio>
#include <cstdlib>
#include <functional>

class SumClass {
public:
  int32_t i = 8;

public:
  void SumNum(int32_t a) {
    printf("a[%d] plus inside[%d] is [%d]\n", a, i, a+i);
  }
};

template <typename T>
void TestFunc(T& a) {
}

int main(void) {
  std::function<void(SumClass&, int32_t)> bindfunc = &SumClass::SumNum;
  auto memfunc = std::mem_fn(
    &SumClass::SumNum);
  SumClass sum;
  memfunc(sum, 2);
  bindfunc(sum, 3);
}
