#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <unistd.h>

std::vector<int32_t> v {
  2, 6, 10, 13, 16, 19
};

void MatchTime(
  int64_t time, int32_t begin, int32_t end, int32_t *index) {
  if (begin >= end) return;
  if (end >= v.size()) return;
  int32_t pivot = (begin + end) / 2;
  int32_t before_time = v.at(pivot);
  int32_t after_time = v.at(pivot+1);
  if (before_time > time && after_time > time) {
    // printf("pivot %d\n", pivot);
    return MatchTime(time, begin, pivot, index);
  } else if (before_time < time && after_time < time) {
    // printf("pivot %d\n", pivot);
    return MatchTime(time, pivot+1, end, index);
  } else {
    *index = ((std::abs(before_time-time) < std::abs(
      after_time-time)) ? pivot : pivot+1);
    // *index = pivot + 1;
    return;
  }
}

void MatchTimeNoRecursion(int64_t time, int32_t begin,
  int32_t end, int32_t *index, bool left_align) {
  if (begin >= end || begin < 0) return;
  if (end >= v.size() || end < 0) return;
  if (time < v.front() || time > v.back()) return;
  int32_t pivot, before_time, after_time;
  do {
    pivot = (begin + end) / 2;
    // printf("pivot %d\n", pivot);
    before_time = v.at(pivot);
    after_time = v.at(pivot+1);
    if (before_time > time && after_time > time)
      end = pivot;
    else if (before_time < time && after_time < time)
      begin = pivot+1;
    else
      break;
  } while(begin < end && end < v.size());
  if (before_time == time) *index = pivot;
  else if (after_time == time) *index = pivot+1;
  else *index = (left_align ? pivot : pivot+1);
  /*
  *index = ((std::abs(before_time-time) < std::abs(
    after_time-time)) ? pivot : pivot+1);
  */
}

void printv(const std::vector<int32_t>& v) {
  printf("v: ");
  for (auto i : v) {
    printf("%d ", i);
  }
  printf("\n");
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("invalid parameter\n");
    return -1;
  }
  int64_t time = std::atoi(argv[1]);
  int a = 0;
  int b = 1;
  int c = (a+b)/2;
  printv(v);

  int index = -1;
  MatchTime(time, 0, v.size()-1, &index);
  if (-1 != index)
    printf("time: %d, index: %d, find_time: %d\n", time, index, v.at(index));
  else
    printf("time: %d, index: %d, find failed!\n", time, index);
  
  printf("======== recursion ==========\n");
  printv(v);
  for (int i = (v.front()-2); i <= (v.back()+2); i++) {
    time = i;
    index = -1;
    MatchTime(time, 0, v.size()-1, &index);
    printf("time: %d, index: %d, find_time: %d\n", time, index,
      (index != -1) ? v.at(index) : -1);
  }

  printf("======== no recursion ==========\n");
  printv(v);
  for (int i = (v.front()-2); i <= (v.back()+2); i++) {
    time = i;
    int right_index = -1;
    int left_index = -1;
    MatchTimeNoRecursion(time, 0, v.size()-1, &right_index, false);
    MatchTimeNoRecursion(time, 0, v.size()-1, &left_index, true);
    printf("time: %d, right_index: %d, right_time: %d, left_index: %d, left_time: %d\n", time,
      right_index, ((right_index != -1) ? v.at(right_index) : -1),
      left_index, ((left_index != -1) ? v.at(left_index) : -1));
  }
}

