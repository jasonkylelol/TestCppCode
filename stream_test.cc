#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <unistd.h>

class DingStream {
 public:
  DingStream& operator<<(const char* str) {
    printf("%s", str);
    return *this;
  }

  DingStream& operator<<(const std::string& str) {
    printf("%s", str.c_str());
    return *this;
  }

  DingStream& operator<<(const int i) {
    printf("%d", i);
    return *this;
  }
};

class MyMsg {
 public:
  friend DingStream& operator<<(DingStream& os, const MyMsg& msg) {
    os << msg.m_msg << msg.m_int;
    return os;
  }
 private:
  std::string m_msg = "hehehe";
  int m_int = 66;
};

const DingStream Ding;

class HeHe {
public:
  HeHe() {
		std::cout << "new" << std::endl;
  }
  virtual ~HeHe() {
		std::cout << "delete" << std::endl;
  }
};

int main(int argc, char *argv[]) {
  int uid = 23456789;
  std::string nick_name = "dog";
  MyMsg msg;
  Ding << "i want to ding u! uid[" << uid
    << "] msg[" << msg << "] name[" << nick_name << "]\n";

  std::ostringstream oss;
  oss << "one\t" << "1\t";
  printf("%s\n", oss.str().c_str());

  // HeHe hehe;
  // sleep(2);

	std::cout << "=============" << std::endl;
	{
		std::cout << "before" << std::endl;
		HeHe a;
		std::cout << "after" << std::endl;
	}
  std::cout << "=============" << std::endl;
	{
		std::cout << "before" << std::endl;
		HeHe();
		std::cout << "after" << std::endl;
	}
}

