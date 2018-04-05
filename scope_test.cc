#include <iostream>
#include <vector>
#include <cstdio>

class ScopeTest {
public:
  ScopeTest() {printf("Scope start here!\n");}
  ~ScopeTest() {printf("Scope end here!\n");}
private:
  ScopeTest(const ScopeTest &) = delete;
  ScopeTest & operator = (const ScopeTest &) = delete;
private:
  const int k = 5;
};

int main(int argc, char *argv[])
{
  const char *strs[] = {"aaaaaaaa", "bbb", "ccccccccccccccccc"};
  std::vector<std::string> v(strs, strs+sizeof(strs)/sizeof(char*));
  for(std::string s : v){
    printf("%s\n", s.c_str());
  }

  printf("start1\n");
  {
    printf("start2\n");
    {
      ScopeTest test;
    }
    printf("end2\n");
  }
  printf("end1\n");
}
