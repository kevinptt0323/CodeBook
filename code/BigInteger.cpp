#include <cstdio>
#include <cstring>
#include <iostream>
#include <iomanip>
using namespace std;
template<class T>
T abs(const T& n) {return n>=T(0)?n:-n;}
class BigInteger {
public:
	BigInteger(const int& num=0) : len(0), sign(1) {
		int num2=num;
		memset(arr, 0, sizeof(arr));
		if( num2<0 ) sign=-1, num2*=-1;
		while( num2 ) arr[len++]=num2%step, num2/=step;
	}
	BigInteger(const char* num0) : len(0), sign(1) {
		*this = num0;
	}
	BigInteger(const BigInteger& b) : len(b.len), sign(b.sign) {
		memset(arr, 0, sizeof(arr));
		for(int i=0; i<len; ++i) arr[i]=b.arr[i];
	}
	~BigInteger() {}
	BigInteger & operator = (const BigInteger& b) {
		len=b.len;
		sign=b.sign;
		memset(arr, 0, sizeof(arr));
		for(int i=0; i<len; ++i) arr[i]=b.arr[i];
		return *this;
	}
	BigInteger & operator = (const int& num) {
		int num2=num;
		memset(arr, 0, sizeof(arr));
		len=0, sign=1;
		if( num2<0 ) sign=-1, num2*=-1;
		while( num2 ) arr[len++]=num2%step, num2/=step;
		return *this;
	}
	BigInteger & operator = (const char* num0) {
		char num[strlen(num0)];
		int offset = 0;
		len = 0;
		sign = 1;
		if( num0[0] == '-' ) sign = -1, ++offset;
		else if( num0[0] == '+' ) ++offset;
		while( num0[offset]=='0' ) ++offset;
		strcpy(num, num0+offset);
		int tmp = strlen(num);
		for(int i=tmp-digit; i>=0; i-=digit) {
			arr[len] = 0;
			for(int j=0; j<digit; ++j) arr[len] = arr[len]*10 + num[i+j]-'0';
			++len;
		}
		arr[len] = 0;
		for(int j=0; j<tmp%digit; ++j) arr[len] = arr[len]*10 + num[j]-'0';
		if( tmp%digit ) ++len;
		return *this;
	}
	BigInteger operator + (const BigInteger& b) const {
		if( *this>0 && b<0 ) return *this-(-b);
		if( *this<0 && b>0 ) return -(-*this-b);
		BigInteger res=*this;
		int len2=max(res.len, b.len);
		for(int i=0; i<len2; ++i) {
			res.arr[i]+=b.arr[i];
			if( res.arr[i]>=step ) res.arr[i]-=step, res.arr[i+1]++;
		}
		res.len=len2;
		if(res.arr[len2]) ++res.len;
		return res;
	}
	BigInteger operator - (const BigInteger& b) const {
		if( *this<b ) return -(b-*this);
		if( *this<0 && b<0 ) return -(-*this+b);
		if( *this>0 && b<0 ) return *this+(-b);
		BigInteger res=*this;
		int len2=max(res.len, b.len);
		for(int i=0; i<len2; ++i) {
			res.arr[i]-=b.arr[i];
			if( res.arr[i]<0 ) res.arr[i]+=step, res.arr[i+1]--;
		}
		while( len2>0 && res.arr[len2-1]==0 ) --len2;
		res.len=len2;
		return res;
	}
	BigInteger operator * (const BigInteger& b) const {
		if( *this==0 || b==0 ) return BigInteger(0);
		BigInteger res;
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
	BigInteger operator / (const int& b) const {
		if( b==0 ) return 0;
		BigInteger res;
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
	BigInteger operator / (const BigInteger& b) const {
		BigInteger abs_this=abs(*this);
		if( b==0 ) return 0;
		BigInteger st=0, ed, md;
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
	BigInteger operator % (const int& b) const {
		if( b<=0 ) return 0;
		BigInteger res;
		long long reduce=0;
		for(int i=len-1; i>=0; --i)
			reduce = (arr[i]+reduce*step)%b;
		return reduce*sign;
	}
	BigInteger operator % (const BigInteger& b) const {
		if( b.isInt() ) return *this%int(b.toInt());
		if( b<=0 ) return 0;
		return *this-*this/b*b;
	}
	bool operator <  (const BigInteger& b) const {
		if( sign!=b.sign ) return sign<b.sign;
		if( len!=b.len ) return len*sign<b.len*b.sign;
		for(int i=len-1; i>=0; --i)
			if( arr[i]!=b.arr[i] ) return arr[i]*sign<b.arr[i]*b.sign;
		return false;
	}
	bool operator == (const BigInteger& b) const {
		if( sign!=b.sign ) return false;
		if( len!=b.len ) return false;
		for(int i=len-1; i>=0; --i)
			if( arr[i]!=b.arr[i] ) return false;
		return true;
	}
	bool operator <= (const BigInteger& b) const { return *this<b || *this==b; }
	bool operator >  (const BigInteger& b) const { return b<*this; }
	bool operator >= (const BigInteger& b) const { return b<=*this; }
	bool operator != (const BigInteger& b) const { return !(*this==b); }
	BigInteger operator-() const {
		BigInteger res = *this;
		if( res.len>0 ) res.sign*=-1;
		return res;
	}
	template<class T> BigInteger operator +  (const T& b) const {return *this+BigInteger(b);}
	template<class T> BigInteger operator -  (const T& b) const {return *this-BigInteger(b);}
	template<class T> bool   operator == (const T& b) const {return *this==BigInteger(b);}
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
	friend ostream& operator << ( ostream& out, const BigInteger &rhs ) {
		if( rhs.len==0 ) out << '0';
		else {
			out << rhs.arr[rhs.len-1]*rhs.sign;
			for(int i=rhs.len-2; i>=0; --i) out << setfill('0') << setw(BigInteger::digit) << rhs.arr[i];
		}
		return out;
	}
	long long toInt() const {return sign*(1ll*arr[1]*step+arr[0]);}
private:
	static const int length = 100;
	static const int digit = 4, step = 10000;
	int arr[length];
	int len, sign;
};
istream& operator >> ( istream& in, BigInteger &rhs ) {
	char s[1000];
	in >> s;
	rhs = s;
	return in;
}

