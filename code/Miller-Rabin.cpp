ll mul(ll a, ll b, ll n) { // a*b%n
	ll r = 0; a %= n, b %= n;
	while(b){
		if(b&1) r = (a+r>=n? a+r-n: a+r);
		a = (a+a>=n? a+a-n: a+a);
		b >>= 1;
	}
	return r;
}
ll powmod(ll a, ll d, ll n) { // a^d%n
	if(d==0) return 1ll;
	if(d==1) return a%n;
	return mul(powmod(mul(a, a, n), d>>1, n), d%2?a:1, n);
}
bool miller_rabin(ll a, ll n) {
	if (__gcd(a,n) == n ) return true;
	if (__gcd(a,n) != 1 ) return false;
	ll d = n-1, r = 0, res;
	while(d%2==0) { ++r; d>>=1; }
	res = powmod(a, d, n);
	if( res==1 || res==n-1 ) return true;
	while(r--) {
		res = mul(res, res, n);
		if(res==n-1) return true;
	}
	return false;
}
bool isprime(ll n) {
	ll as[7]={2, 325, 9375, 28178, 450775, 9780504, 1795265022}; //  2, 7, 61
	for(int i=0; i<7; i++)
		if( miller_rabin(n, as[i])==false )
			return false;
	return true;
}

