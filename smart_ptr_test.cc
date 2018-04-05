#include <memory>
#include <iostream>
#include <queue>
#include <cstdio>

class Dummy {
private:
	char* ptr;
public:
	Dummy() {
		printf("new\n");
		ptr = malloc(1024*1024);
	}
	virtual ~Dummy() {
		printf("del\n");
		free(ptr);
	}
};

int main(int argc, char *argv[]) {
	{
	  std::queue<std::shared_ptr<Dummy>> q;
		std::shared_ptr<Dummy> p1(new Dummy());
		std::shared_ptr<Dummy> p2(new Dummy());
		printf("enqueue\n");
		q.push(p1);
		q.push(p2);

		int64_t i = 0;
		while (i < 1000) {
			i++;
		  std::shared_ptr<Dummy> p(new Dummy());
			q.push(p);
			printf("enqueue\n");
			std::shared_ptr<Dummy> d = q.front();
			q.pop();
			printf("dequeue\n");
		}
	
		while (!q.empty()) {
			printf("access\n");
			std::shared_ptr<Dummy> d = q.front();
			printf("dequeue\n");
			q.pop();
			d.reset();
		}
	}
	printf("exit brace\n");

	std::shared_ptr<Dummy> p3(new Dummy());
	p3.reset();
	printf("manual reset\n");
}

