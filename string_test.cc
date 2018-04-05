#include <cstdio>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

inline bool DoubleToString(std::string* str, double d, int32_t digits) {
  if (nullptr == str) return false;
  char buf[32], format[8];
  std::snprintf(format, sizeof(format), "%%.%df", digits);
  std::snprintf(buf, sizeof(buf), format, d);
  *str = buf;
}

inline bool GrubSymbolPostfix(
  const std::string& symbol, const std::string& original) {
  /*
  std::string original = "GBPUSD";
  std::string symbol = "GBPUSD..";
  */
  std::string postfix;
  std::string::size_type n = symbol.rfind(original);
  if (std::string::npos == n) {
    std::cout << "can not find original[" << original
      << "] in symbol[" << symbol << "]" << std::endl;
    return false;
  }
  try {
    postfix = symbol.substr(
      (n + original.size()),
      (symbol.size() - (n + original.size())));
    std::cout << "symbol[" << symbol << "] original[" << original
      << "] postfix[" << postfix << "]" << std::endl;
    return true;
  } catch (const std::out_of_range& e) {
    std::cout << "catch an exception[" << e.what()
      << "] symbol[" << symbol << "] original[" << original << "]" << std::endl;
  }
  return false;
}

class DingStream {
public:
  static DingStream& Ding() {
    static DingStream ding;
    return ding;
  }

  friend std::ostream& operator<<(std::ostream& os,
    const DingStream& ding) {
    std::stringstream oss;
    oss << os.rdbuf();
    std::cout << "[" << oss.str() << ":" << os.tellp() << "]";
    return os;
  }
};

int main(int argc, char *argv[])
{
  std::vector<std::string> v;
  std::string s("22798491,,22781699,%^&,22809124");
  std::istringstream f;
  f.str(s);
  std::string t;
  while (std::getline(f, t, ',')) v.push_back(t);
  
  for (auto &c : v) {
    try {
      int i = std::stoi(c);
      std::cout << "integer:" << i << std::endl;
    } catch (const std::invalid_argument &e) {
      std::cout << "conversion [" << c << "] catch an exception: " << e.what()
        << std::endl;
    }
  }

  std::string str;
  double d = 114.07152631578947;
  DoubleToString(&str, d, 4);
  printf("\n%f : %s\n", d, str.c_str());

  GrubSymbolPostfix("GBPUSD..", "GBPUSD");
  GrubSymbolPostfix("GBPUSD.", "GBPUSD");
  GrubSymbolPostfix("GBPUSD-hkd", "GBPUSD");
  GrubSymbolPostfix("GBPUSDE", "GBPUSD");

  str = "xxx Invalid S/L or T/P xxx";
  if (std::string::npos != str.find("Invalid S/L or T/P")) {
    printf("find\n");
  } else {
    printf("not find\n");
  }

  std::cout << "HeHeHeHeHe" << DingStream::Ding() << "HaHaHaHaHa" << std::endl;
}
