#include <cstdio>
#include <cstring>
#include <ctime>
#include <cmath>
#define N 10000000
using namespace std;
bool isp[N+10]; // may not be correct after calcuate
int prime[N+10];

int findPrime0(const int &n) {
	int flag=0, sqr;
	bool prime2;
	prime[flag++] = 2, prime[flag++] = 3;
	for(int i=5, tmp=0; i<=n; i+=(tmp+2), tmp=(tmp+2)%4) {
		prime2 = true;
		sqr = sqrt(i);
		for(int j=0; prime[j]<=sqr; ++j)
			if( i%prime[j]==0 ) { prime2=false; break; }
		if( prime2 ) prime[flag++] = i;
	}
	return flag;
}

int findPrime1(const int &n) {
	int flag=0;
	memset(isp, true, sizeof(isp));
	prime[flag++] = 2;
	for(int i=3; i<=n; i+=2) {
		if( isp[i] ) {
			prime[flag++] = i;
			if( 1ll*i*i<=n )
				for(int j=i*i; j<=n; j+=i+i) isp[j] = false;
		}
	}
	return flag;
}
int findPrime2(const int &n) {
	int flag=0;
	memset(isp, true, sizeof(isp));
	prime[flag++] = 2, prime[flag++] = 3;
	for(int j=3*3; j<=n; j+=6) isp[j] = false;
	for(int i=5, tmp=0; i<=n; i+=(tmp+2), tmp=(tmp+2)&3) {
		if( isp[i] ) {
			prime[flag++] = i;
			if( 1ll*i*i<=n )
				for(int j=i*i; j<=n; j+=i+i) isp[j] = false;
		}
	}
	return flag;
}
int findPrime3(const int &n) {
	int flag=0;
	memset(isp, true, sizeof(isp));
	prime[flag++] = 2;
	for(int i=3; i<=n; i+=2){
		if( isp[i] ) prime[flag++]=i;
		for(int j=0; j<flag&&i*prime[j]<=n; j++){
			isp[i*prime[j]]=false;
			if( i%prime[j]==0 ) break;
		}
	}
	return flag;
}
int findPrime4(const int &n) {
	int flag=0;
	memset(isp, true, sizeof(isp));
	prime[flag++] = 2, prime[flag++] = 3;
	for(int i=5, tmp=0; i<=n; i+=(tmp+2), tmp=(tmp+2)&3) {
		if( isp[i] ) prime[flag++]=i;
		for(int j=0; j<flag&&i*prime[j]<=n; j++){
			isp[i*prime[j]]=false;
			if( i%prime[j]==0 ) break;
		}
	}
	return flag;
}
double test(int (*func)(const int&)) {
	clock_t st, ed;
	st = clock();
	for(int i=0; i<20; ++i) func(N);
	ed = clock();
	return double(ed-st)/CLOCKS_PER_SEC;
}

int main() {
	printf("amount = %d\n", findPrime0(N));
	printf("amount = %d\n", findPrime1(N));
	printf("amount = %d\n", findPrime2(N));
	printf("amount = %d\n", findPrime3(N));
	printf("amount = %d\n", findPrime4(N));
	//printf("0 : %lf ms\n", test(findPrime0));
	printf("1 : %lf ms\n", test(findPrime1));
	printf("2 : %lf ms\n", test(findPrime2));
	printf("3 : %lf ms\n", test(findPrime3));
	printf("4 : %lf ms\n", test(findPrime4));
	
	return 0;
}


