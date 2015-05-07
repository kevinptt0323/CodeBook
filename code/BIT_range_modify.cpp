inline int lowbit(int x) { return x&-x; }
template<class T>
class fenwick {
public:
	fenwick(int __size=SIZE) {
		size = __size+10;
		a = new T[size], b=new T[size];
		memset(a, 0, sizeof(T)*size);
		memset(b, 0, sizeof(T)*size);
	}
	~fenwick() { delete[] a, delete[] b;}
	inline void add(int l, int r, long long n) {
		__add(a, r, r*n), __add(a, l-1, (l-1)*-n);
		__add(b, r, n), __add(b, l-1, -n);
	}
	inline long long sum(int l, int r) { return __sum(r)-__sum(l-1); }
private:
	int size;
	T *a, *b;
	inline void __add(T *arr, int x, T n) { for(; x&&n&&x<size; x+=lowbit(x)) arr[x]+=n; }
	inline T __sum(T x) { return __sum(a, x)+(__sum(b, size)-__sum(b, x))*x; }
	inline T __sum(T *arr, int x) {
		T res=0;
		for(; x; x-=lowbit(x)) res+=arr[x];
		return res;
	}
};

