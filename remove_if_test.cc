#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

int main(int agrc, char *argv[]) {
  std::vector<std::string> sv = {"bbb", "ccc", "aaa", "ddd"};
  for (auto s : sv) {
    printf("%s ", s.c_str());
  }
  printf("\n");
  auto func1 = [&] (const std::string& s) {
    printf("%s\n", s.c_str());
    return s < "ccc";
  };
  auto it = std::remove_if(sv.begin(), sv.end(),
    func1);
  sv.erase(it, sv.end());
  for (auto s : sv) {
    printf("%s ", s.c_str());
  }
  printf("\n");
}
