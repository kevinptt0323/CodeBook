#include <cstdio>
#include <cstring>
template<class T>
T max(const T& a, const T& b) {return a>b?a:b;}
template<class T>
T abs(const T& n) {return n>=T(0)?n:-n;}
class BigNum {
public:
	BigNum(const int& num=0) : len(0), step(10000), sign(1) {
		int num2=num;
		memset(arr, 0, sizeof(arr));
		if( num2<0 ) sign=-1, num2*=-1;
		while( num2 ) arr[len++]=num2%step, num2/=step;
	}
	//BigNum(char* num) {}
	BigNum(const BigNum& b) : len(b.len), step(b.step), sign(b.sign) {
		memset(arr, 0, sizeof(arr));
		for(int i=0; i<len; ++i) arr[i]=b.arr[i];
	}
	BigNum(const char* s) : step(10000) {
		memset(arr, 0, sizeof(arr));
		int i;
		if( s[0]=='-' ) i=1, sign=-1, len=(strlen(s)+3)/4;
		else i=0, sign=1, len=(strlen(s)+2)/4;
		for(; s[i]; ++i) *this=(*this)*10+s[i]-48;
	}
	~BigNum() {}
	BigNum & operator=(const BigNum& b) {
		len=b.len;
		sign=b.sign;
		memset(arr, 0, sizeof(arr));
		for(int i=0; i<len; ++i) arr[i]=b.arr[i];
		return *this;
	}
	BigNum & operator=(const int& num) {
		int num2=num;
		memset(arr, 0, sizeof(arr));
		len=0, sign=1;
		if( num2<0 ) sign=-1, num2*=-1;
		while( num2 ) arr[len++]=num2%step, num2/=step;
		return *this;
	}
	BigNum operator+(const BigNum& b) const {
		if( *this>0 && b<0 ) return *this-(-b);
		if( *this<0 && b>0 ) return -(-*this-b);
		BigNum res=*this;
		int len2=max(res.len, b.len);
		for(int i=0; i<len2; ++i) {
			res.arr[i]+=b.arr[i];
			if( res.arr[i]>=step ) res.arr[i]-=step, res.arr[i+1]++;
		}
		res.len=len2;
		if(res.arr[len2]) ++res.len;
		return res;
	}
	BigNum operator-(const BigNum& b) const {
		if( *this<b ) return -(b-*this);
		if( *this<0 && b<0 ) return -(-*this+b);
		if( *this>0 && b<0 ) return *this+(-b);
		BigNum res=*this;
		int len2=max(res.len, b.len);
		for(int i=0; i<len2; ++i) {
			res.arr[i]-=b.arr[i];
			if( res.arr[i]<0 ) res.arr[i]+=step, res.arr[i+1]--;
		}
		while( len2>0 && res.arr[len2-1]==0 ) --len2;
		res.len=len2;
		return res;
	}
	BigNum operator*(const BigNum& b) const {
		if( *this==0 || b==0 ) return BigNum(0);
		BigNum res;
		for(int i=0; i<len; ++i) {
			for(int j=0; j<b.len; ++j) {
				res.arr[i+j]+=arr[i]*b.arr[j];
				res.arr[i+j+1]+=res.arr[i+j]/step;
				res.arr[i+j]%=step;
			}
		}
		res.len=len+b.len-1;
		while( res.arr[res.len] ) ++res.len;
		res.sign=sign*b.sign;
		return res;
	}
	BigNum operator/(const int& b) const {
		if( b==0 ) return BigNum(0);
		BigNum res;
		long long reduce=0;
		int signb=b>0?1:-1, b2=b*signb;
		for(int i=len-1; i>=0; --i) {
			res.arr[i] = (arr[i]+reduce*step)/b2;
			reduce = (arr[i]+reduce*step)%b2;
		}
		res.len = len;
		while( res.len>0 && res.arr[res.len-1]==0 ) --res.len;
		if( res.len==0 ) res.sign=1;
		else res.sign=sign*signb;
		return res;
	}
	BigNum operator/(const BigNum& b) const {
		BigNum abs_this=abs(*this);
		if( b==0 ) return BigNum(0);
		BigNum st=0, ed, md;
		if( b.arr[0]>0 ) ed=abs_this/b.arr[0];
		else if( b.arr[1]*b.step+b.arr[0]>0 ) ed=abs_this/b.arr[1]*b.step+b.arr[0];
		else ed=abs_this;
		while( st<ed ) {
			md = (st+ed)/2+1;
			if( md*b<=abs_this ) st=md;
			else ed=md-1;
		}
		if( st.len==0 ) st.sign=1;
		else st.sign=sign*b.sign;
		
		return st;
	}
	BigNum operator%(const int& b) const {
		if( b<=0 ) return BigNum(0);
		BigNum res;
		long long reduce=0;
		for(int i=len-1; i>=0; --i)
			reduce = (arr[i]+reduce*step)%b;
		return reduce*sign;
	}
	BigNum operator%(const BigNum& b) const {
		if( b.isInt() ) return *this%int(b.toInt());
		if( b<=BigNum(0) ) return BigNum(0);
		return *this-*this/b*b;
	}
	bool operator<(const BigNum& b) const {
		if( sign!=b.sign ) return sign<b.sign;
		if( len!=b.len ) return len*sign<b.len*b.sign;
		for(int i=len-1; i>=0; --i)
			if( arr[i]!=b.arr[i] ) return arr[i]*sign<b.arr[i]*b.sign;
		return false;
	}
	bool operator==(const BigNum& b) const {
		if( sign!=b.sign ) return false;
		if( len!=b.len ) return false;
		for(int i=len-1; i>=0; --i)
			if( arr[i]!=b.arr[i] ) return false;
		return true;
	}
	bool operator<=(const BigNum& b) const {return *this<b || *this==b;}
	bool operator>(const BigNum& b) const {return b<=*this;}
	bool operator>=(const BigNum& b) const {return b<=*this;}
	bool operator!=(const BigNum& b) const {return !(*this==b);}
	BigNum operator-() const {
		BigNum res = *this;
		if( res.len>0 ) res.sign*=-1;
		return res;
	}
	template<class T> BigNum operator+(const T& b) const {return *this+BigNum(b);}
	template<class T> BigNum operator-(const T& b) const {return *this-BigNum(b);}
	template<class T> bool operator==(const T& b) const {return *this==BigNum(b);}
	void print(const char *str="") const {
		if( len==0 ) printf("0");
		else {
			printf("%d", arr[len-1]*sign);
			for(int i=len-2; i>=0; --i) printf("%04d", arr[i]);
		}
		printf("%s", str);
	}
	bool isInt() const {
		if( len>2 ) return false;
		if( len<2 ) return true;
		long long res=toInt();
		return res<(1ll<<31) && res>=-(1ll<<31);
	}
	long long toInt() const {return sign*(1ll*arr[1]*step+arr[0]);}
private:
	int arr[1000];
	int len;
	int step;
	int sign;
};
int main() {
	BigNum a=1;
	for(int i=1; i<=1000; i++) a=a*i;
	a.print();
	printf("\n");
	return 0;
}
