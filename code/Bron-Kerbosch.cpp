typedef long long ll;
int n;
vector<ll> v, ne;
// ne[u] is the neighbours of u
// v is the result, P = (1<<n) - 1
void BronKerbosch(ll R, ll P, ll X){
	if ((P == 0LL) && (X == 0LL)) {v.push_back(R);return ;}
	int u = 0;
	for (; u < n; u ++) if ( (P|X) & (1LL << u) ) break;
	for (int i = 0; i < n; i ++)
		if ( (P&~ne[u]) & (1LL << i) ){
			BronKerbosch(R | (1LL << i), P & ne[i], X & ne[i]);
			P -= (1LL << i); X |= (1LL << i);
		}
}
