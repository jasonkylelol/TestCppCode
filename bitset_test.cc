#include <bitset>
#include <iostream>
// #include <shared_mutex>

int main(int argc, char*argv[]) {
  std::bitset<2> bset;
  bset[0] = true;
  std::cout << "bset[" << bset << "]" << std::endl;

  // std::shared_mutex lock;
  // std::shared_lock<std::shared_mutex> lk(lock);
}

