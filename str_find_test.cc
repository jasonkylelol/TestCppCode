#include <cstdio>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  std::string str = "o:15078838991313042~$2029.32~";
  //std::string str = "~$o:15078838991313042~$2029.32~";
  if (str.find("o:") == 0) {
  //if (str.find("~$") != std::string::npos) {
    printf("get\n");
  } else {
    printf("not get\n");
  }
  std::vector<int> v;
  auto it = v.begin();
  for (;it != v.end();it++) {
    printf("aaaaa\n");
  }
  if (it == v.end()) {
    printf("empty, begin=end\n");
  }

  std::string find_last_str = "XAUUSD, USDJPY, USDGBP,";
  printf("original: %s\n", find_last_str.c_str());
  find_last_str.erase(find_last_str.find_last_of(','));
  printf("result: %s\n", find_last_str.c_str());
}
