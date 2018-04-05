#include <cstdio>
#include <cstdlib>
#include <memory>
#include <thread>

bool b_exit = false;

void ThreadFunc(void) {
  printf("Thread start!\n");
  for (;;) {
    if (b_exit) {
      printf("About to exit!\n");
      break;
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));
  }
  printf("Thread end!\n");
}

int main(int argc, char *argv[]) {
  auto func = []() {
      ThreadFunc();
  };
  std::shared_ptr<std::thread> t = std::shared_ptr<std::thread>(
    new std::thread(std::bind(func)));
  if (nullptr != t.get()) printf("Shared ptr stored!\n");
  // t->detach();
  if (t->joinable()) printf("Thread is joinable\n");
  std::this_thread::sleep_for(std::chrono::seconds(5));
  b_exit = true;
  std::this_thread::sleep_for(std::chrono::seconds(5));
  if (t->joinable()) {
    printf("Thread is joinable\n");
    t->join();
  }
  t.reset();
  if (nullptr == t.get()) printf("Shared ptr released!\n");
  std::this_thread::sleep_for(std::chrono::seconds(5));
  printf("Main exit!\n");
}
