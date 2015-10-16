#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;

typedef long long ll;

int ODD[1<<20], EVEN[1<<20], ODD_B[1<<20], EVEN_B[1<<20];

int mul_order(int n) {
	n--;
	int high_bit = n&(-n);
	for(n-=high_bit; n; n-=high_bit)
		high_bit = n&(-n);
	return high_bit<<2;
}

// return a^x mod p
int mod_pow(int a, int x, int p) {
	if(x==0) return 1;
	ll ret = mod_pow(a,x>>1,p);
	ret*=ret;
	ret%=p;
	return (x&1)?(ret*a)%p:ret;
}

// only works for prime p
int mod_inverse(int x, int p) { return mod_pow(x,p-2,p); }

// n is a power of 2 and answer is at most upper_bound
// 2013265921=1+2^27*3*5 is a prime
inline int suitable_prime(int n, int upper_bound) { return 2013265921; }

// not general version
int primitive_root(int p) {
	int ret;
	srand(714091); // THOR
//	srand(time(NULL));
	for(ret=rand()%p;;ret=rand()%p) {
		if(mod_pow(ret,(p-1)/2,p)!=1 && 
			mod_pow(ret,(p-1)/3,p)!=1 &&
			mod_pow(ret,(p-1)/5,p)!=1)
			return ret;
	}
}

// nth principle root of unity (mod p)
int principal_root(int n, int p) {
	int g=primitive_root(p);
	return mod_pow(g,(p-1)/n,p);
}

void cooley_tukey(int *a, int *b, int n, ll r, ll p) {
	if(n>1) {
		int half_n=n>>1;
		int *odd=ODD+half_n, *even=EVEN+half_n;
		int *odd_b=ODD_B+half_n, *even_b=EVEN_B+half_n;
		for(int i=0; i<n; i+=2) {
			even[i>>1]=a[i];
			odd[i>>1]=a[1|i];
		}
		cooley_tukey(even,even_b,n>>1,r*r%p,p);
		cooley_tukey(odd,odd_b,n>>1,r*r%p,p);
		ll iter=1, p2=p*p;
		for(int i=0; i<half_n; i++) {
			ll odd_part=iter*odd_b[i];
			b[i]=(even_b[i]+odd_part)%p;
			b[half_n|i]=(even_b[i]+p2-odd_part)%p;
			iter*=r;
			iter%=p;
		}
	}
	else b[0]=a[0];
}

void print(int *a, int n) {
	for(int i=0; i<n; i++)
		printf("%d%c",a[i],i==n-1?'\n':' ');
}

// c=a*b where c is initially empty
void multiply(int *a, int *b, int *c, 
	int n, ll inv_n, ll r, ll inv_r, ll p) {
	int *f, *g, *h;
	f=new int[n];
	g=new int[n];
	h=new int[n];
	cooley_tukey(a,f,n,r,p);
	cooley_tukey(b,g,n,r,p);
	for(int i=0; i<n; i++) h[i]=(ll)f[i]*g[i]%p;
	cooley_tukey(h,c,n,inv_r,p);
	for(int i=0; i<n; i++) c[i]=c[i]*inv_n%p;
	delete[] f;
	delete[] g;
	delete[] h;
}

int main() {
	int n, N;
	scanf("%d",&n);
	N=mul_order(n);
	printf("N=%d\n",N);
	int *a, *b, *c;
	a=new int[N];
	b=new int[N];
	c=new int[N];
	for(int i = 0; i < n; i++) scanf("%d",&a[i]);
	for(int i = 0; i < n; i++) scanf("%d",&b[i]);
	for(int i = n; i< N; i++)  a[i]=b[i]=0;
	int p=suitable_prime(N,10007);
	ll r=principal_root(N,p);
	ll inv_r=mod_inverse(r,p);
	ll inv_n=mod_inverse(N,p);
	multiply(a,b,c,N,inv_n,r,inv_r,p);
	int last=N-1;
	while(last>=0 && c[last]==0) last--;
	for(int i = 0; i<=last; i++)
		printf("%d%c",c[i],last==i?'\n':' ');
	return 0;
}
