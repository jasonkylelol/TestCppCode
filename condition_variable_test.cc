#include <stdio.h>
#include <unistd.h>

#include <cstdio>
#include <iostream>
#include <thread>
#include <condition_variable>
#include <vector>
#include <queue>
#include <string>

std::mutex mtx;
std::condition_variable cond;
std::queue<std::string> que;
bool b_stop = false;

void Wait(int index) {
  while (!b_stop) {
    {
      std::unique_lock<std::mutex> lk(mtx);
      if (cond.wait_for(lk, std::chrono::seconds(1), [&] {return b_stop || !que.empty();})) {
        std::cout << "Thread[" << index << "] wait b_stop[" << b_stop
          << "] que size[" << que.size() << "]" << std::endl;
      } else {
        // std::cout << "Thread[" << index << "] timeout" << std::endl;
      }
    }

    {
      std::lock_guard<std::mutex> lk(mtx);
      if (!que.empty()) {
        auto val = que.front();
        que.pop();
        std::cout << "Thread[" << index << "] fetch one [" << val << "]" << std::endl;
      }
    }
    // sleep(5);
  }
  std::cout << "Thread[" << index << "] exited" << std::endl;
}

void NotifyOne(std::string val) {
  printf("NotifyOne val[%s]\n", val.c_str());
  {
    std::lock_guard<std::mutex> lk(mtx);
    que.push(val);
  }
  cond.notify_one();
}

void NotifyAll(bool stop) {
  printf("NotifyAll stop[%s]\n", (stop?"true":"false"));
  {
    std::lock_guard<std::mutex> lk(mtx);
    b_stop = stop;
  }
  cond.notify_all();
}

int main(int argc, char *argv[]) {
  std::vector<std::thread> th_v;
  for (int i = 0; i < 4; i++) {
    th_v.push_back(std::thread(Wait, i));
  }

  sleep(2);
  NotifyOne("aaaaaa");
  sleep(5);
  NotifyOne("bbbbbb");
  sleep(5);
  NotifyOne("cccccc");
  sleep(5);
  NotifyAll(true);

  for (auto& th : th_v) {
    th.join();
  }
}
