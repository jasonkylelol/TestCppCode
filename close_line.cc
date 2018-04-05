#include <cstdio>
#include <algorithm>
#include <string>

int main(int argc, char *argv[]) {
  if (argc != 5) {
    printf("usage: equity copy_order_profit remain_margin copy_capital\n");
    return 0;
  }

  double equity = std::stod(std::string(argv[1]));
  double copy_order_profit = std::stod(std::string(argv[2]));
  double remain_margin = std::stod(std::string(argv[3]));
  double copy_capital = std::stod(std::string(argv[4]));

  double close_line_gap = remain_margin / (equity + copy_capital + copy_order_profit) * equity * 0.9;
  printf("close_line_gap %f\n", close_line_gap);
}
