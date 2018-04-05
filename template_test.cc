#include <iostream>
#include <string>
#include <queue>
#include <memory>
#include <functional>
#include <unistd.h>

class SqlMetaBase {
public:
  SqlMetaBase() {
		std::cout << "Base new" << std::endl;
	}
	virtual ~SqlMetaBase() {
		std::cout << "Base del" << std::endl;
	}

	virtual void Exec() = 0;
}; // class SqlMetaBase

template <typename F, typename P>
class SqlMeta : public SqlMetaBase {
	public:
	  F m_func;
		P m_param;
	public:
		SqlMeta() {
			std::cout << "Derived new" << std::endl;
		}
		virtual ~SqlMeta() {
			std::cout << "Derived del" << std::endl;
		}
		SqlMeta(const F& f, const P& p) {
			m_func = f;
			m_param = p;
		}
	  SqlMeta(const SqlMeta& m) {
		  m_func = m.m_func;
      m_param = m.m_param;
    }
    SqlMeta& operator=(const SqlMeta& m) {
      m_func = m.m_func;
      m_param = m.m_param;
      return *this;
	  }
	  virtual void Exec() override {
			std::cout << "Derived ";
			m_func(m_param);
		}
}; // class SqlMeta

int main(int argc, char *argv) {
	auto func = [&] (std::string s) {
		std::cout << "string[" << s << "]" << std::endl;
	};
	std::string s = "hehehe";
	func(s);
	
  // SqlMeta<std::function<void(std::string)>, std::string> m(func, s);
	// m.Exec();

  std::queue<std::shared_ptr<SqlMetaBase>> queue1;
	std::shared_ptr<SqlMetaBase> p1(new SqlMeta<std::function<void(std::string)>,
	  std::string>(func, std::string("hahaha")));
  std::shared_ptr<SqlMetaBase> p2(new SqlMeta<std::function<void(std::string)>,
	  std::string>(func, std::string("hehehe")));
	std::shared_ptr<SqlMetaBase> p3(new SqlMeta<std::function<void(std::string)>,
		std::string>(func, std::string("xixixi")));
	queue1.push(p1);
	queue1.push(p2);
	queue1.push(p3);

	while (!queue1.empty()) {
		std::shared_ptr<SqlMetaBase> n;
		{
	    n	= queue1.front();
		  queue1.pop();
		}

		n->Exec();
	}

  return 0;
}


