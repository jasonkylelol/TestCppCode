#include <iostream>
#include <string>
#include <streambuf>
#include <memory.h>

class StreamBuf : public std::streambuf {
 public:
  StreamBuf(char *buf, int len) {
    setp(buf, buf + len - 2);
    m_buff_len = len;
  }
  // This effectively ignores overflow.
  virtual int_type overflow(int_type ch) {
    return ch;
  }

  int sync() {
    printf("sync count:%d buff:%s \n", pcount(), pbase());
    memset(pbase(), 0, m_buff_len);
    setp(pbase(), pbase() + m_buff_len - 2);
  }

  size_t pcount() const { return pptr() - pbase(); }
  char* pbase() const { return std::streambuf::pbase(); }

 private:
  int m_buff_len;
};

class Stream : public std::ostream {
 public:
  Stream() : std::ostream(NULL) {
    m_buff = new char[1024];
    m_buff_len = 1024;
    m_streambuf = new StreamBuf(m_buff, m_buff_len);
    rdbuf(m_streambuf);
  }
  virtual ~Stream() {
    if (m_buff) {
      delete[] m_buff;
    }
    delete m_streambuf;
  }

 private:
  StreamBuf* m_streambuf;
  char* m_buff;
  int m_buff_len;
};

int main () {
  Stream s;
  s << "AAAA" << std::endl;
  return 0;
}
