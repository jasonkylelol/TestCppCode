#include <random>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>

int64_t RandInt(int64_t begin, int64_t end) {
	if (begin > end) return -1;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int64_t> dis(begin, end);
	return dis(gen);
}

double RandReal(double begin, double end) {
	if (end - begin < 0.00001) return -1.0;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(begin,
	  std::nextafter(end, std::numeric_limits<double>::max()));
	return dis(gen);
}

int main(int argc, char *argv[]) {
	std::ostringstream o1, o2, o3, o4, o5, o6;
	for (int i = 0; i < 10; i++) {
	  o1 << RandInt(1, 10) << " ";
    o2 << RandInt(-3, 6) << " ";
		o3 << RandInt(-13, -2) << " ";
		o4 << RandReal(0.0, 1.0) << " ";
		o5 << RandReal(-0.5, 0.5) << " ";
		o6 << RandReal(-1.0, -0.1) << " ";
	}
	std::cout << "INT:\n" << o1.str() << "\n"
		<< o2.str() << "\n"
		<< o3.str() << "\n";
  std::cout << "REAL:\n" << o4.str() << "\n"
		<< o5.str() << "\n"
		<< o6.str() << "\n";
}

