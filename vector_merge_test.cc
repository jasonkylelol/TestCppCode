#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <map>
#include <sstream>

class Data {
public:
	Data() {}
	virtual ~Data() {}
	Data(std::string tag, int64_t value) {
		m_tag = tag;
		m_value = value;
	}

	Data& operator=(const Data& d) {
	  m_tag = d.m_tag;
		m_value = d.m_value;
		return *this;
	}

public:
	std::string m_tag;
	int64_t m_value;
};

bool MergeSubOrders(
		std::vector<std::shared_ptr<Data>> *sub_orders) {
	std::map<std::string, std::shared_ptr<Data>> dummy_map;
	auto it = sub_orders->begin();
	for (; it != sub_orders->end();) {
		std::shared_ptr<Data>& order = *it;
		auto it_s = dummy_map.find(order->m_tag);
		if (it_s != dummy_map.end()) {
			std::shared_ptr<Data>& dummy_order = it_s->second;
			dummy_order->m_value = (dummy_order->m_value + order->m_value);
			it = sub_orders->erase(it);
		} else {
			dummy_map.insert(std::make_pair(order->m_tag, order));
			it++;
		}
	}
	return true;
}

void PrintV(const std::vector<std::shared_ptr<Data>>& v) {
	std::ostringstream oss;
	for (auto const &d : v) {
		oss << "[" << d->m_tag << ":" << d->m_value << "] ";
	}
  std::cout << oss.str() << std::endl;
}

int main(int argc, char *argv[]) {
	std::vector<std::shared_ptr<Data>> data_v {
		std::shared_ptr<Data>(new Data("aaa", 3)),
		std::shared_ptr<Data>(new Data("aaa", 3)),
		std::shared_ptr<Data>(new Data("bbb", 3)),
		std::shared_ptr<Data>(new Data("aaa", 3)),
		std::shared_ptr<Data>(new Data("bbb", 3)),
		std::shared_ptr<Data>(new Data("aaa", 3))
	};
	PrintV(data_v);
	MergeSubOrders(&data_v);
	PrintV(data_v);
 
  return 0;	
}
