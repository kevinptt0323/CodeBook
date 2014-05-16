#include <cstdio>
class LFT {
public:
	LFT(int num) {
		insert(num);
	}
	~LFT() {
		destroy();
	}
	void insert(int num) {
		
	}
	void merge(LFT *b) {
		
	}
	void destroy() {
		
	}
private:
	int num, shortest;
	LFT *lt, *rt;
};
int main() {
	LFT a(10);
	LFT b(7122);
	a.merge(&b);
}
