#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <memory.h>

bool IsAvailableTradeTime(time_t t) {
  struct tm tm_buf;
  //time_t t = time(NULL);
  if (nullptr == gmtime_r(&t, &tm_buf)) {
    std::cout << __func__ << " gmtime_s error, t[" << t << "]" << std::endl;
    return true;
  }
  int wday = tm_buf.tm_wday;
  int hour = tm_buf.tm_hour;
  if ((5 == wday && 23 <= hour) ||
    (6 == wday) ||
    (0 == wday && 20 > hour)) {
    return false;
  }
  return true;
}

short GetMonthMaxDay(short month, int year) {
	if(month == 0 || month == 2 ||
	  month == 4 || month == 6 ||
		month == 7 || month == 9 ||
		month == 11)
		return 31;
	else if(month == 3 || month == 5 ||
		month == 8 || month == 10)
		return 30;
	else {
		if(year % 4 == 0) {
			if(year % 100 == 0) {
				if(year % 400 == 0)
					return 29;
		    else
				  return 28;
			}
			return 29;
		}
		return 28;
	}
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "usage: " << argv[0]
      << " seconds" << std::endl;
    exit(1);
  }

  time_t t = time(nullptr);
  struct tm tm_buf;
  char t_buf[64];
  gmtime_r(&t, &tm_buf);
  snprintf(t_buf, sizeof(t_buf), "%04d-%02d-%02d %02d:%02d:%02d",
    1900 + tm_buf.tm_year, 1 + tm_buf.tm_mon, tm_buf.tm_mday,
    tm_buf.tm_hour, tm_buf.tm_min, tm_buf.tm_sec);
  std::cout << "current[" << std::string(t_buf) << "] isAvailable["
    << IsAvailableTradeTime(t) << "]" << std::endl;

  /*
  bzero(t_buf, sizeof(t_buf));
  bzero(&tm_buf, sizeof(tm_buf));
  memcpy(t_buf, argv[1], strlen(argv[1]));
  sscanf(t_buf, "%04d-%02d-%02d %02d:%02d:%02d",
    &tm_buf.tm_year, &tm_buf.tm_mon, &tm_buf.tm_mday,
    &tm_buf.tm_hour, &tm_buf.tm_min, &tm_buf.tm_sec);
  if (tm_buf.tm_mon < 0 || tm_buf.tm_mon > 11 ||
    tm_buf.tm_mday < 1 || tm_buf.tm_mday > 31 ||
    tm_buf.tm_hour < 0 || tm_buf.tm_hour > 23 ||
    tm_buf.tm_min < 0 || tm_buf.tm_min > 59) {
    std::cout << "invalid time string[" << t_buf << "]" << std::endl;
    exit(1);
  } else {
    tm_buf.tm_year -= 1900;
    tm_buf.tm_mon -= 1;
  }
  t = mktime(&tm_buf);
  
  std::cout << "input[" << std::string(t_buf) << "] isAvailable["
    << IsAvailableTradeTime(t) << "] ";
  snprintf(t_buf, sizeof(t_buf), "%04d-%02d-%02d %02d:%02d:%02d",
    1900 + tm_buf.tm_year, 1 + tm_buf.tm_mon, tm_buf.tm_mday,
    tm_buf.tm_hour, tm_buf.tm_min, tm_buf.tm_sec);
  std::cout << "after transform[" << std::string(t_buf) << "]" << std::endl;
	*/

  int64_t sec = atoi(argv[1]);
	std::tm tm;
	if (nullptr == gmtime_r((const long *)&sec, &tm)) {
		std::cout << "gmtime_r failed!\n";
		exit(1);
	}
	std::cout << "tm is " << std::asctime(&tm) << "\n";
	std::cout << "mktime is " << std::mktime(&tm) << "\n";
}


