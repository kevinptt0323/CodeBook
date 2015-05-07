const int MAXN = 100000;
int phi[MAXN], prime[MAXN], pn=0;
memset(phi, 0, sizeof(phi));
for(int i=2; i<MAXN; ++i) {
	if( phi[i]==0 ) prime[pn++]=i, phi[i]=i-1;
	for(int j=0; j<pn; ++j) {
		if( i*prime[j]>=MAXN ) break;
		if( i%prime[j]==0 ) {
			phi[i*prime[j]] = phi[i] * prime[j];
			break;
		}
		phi[i*prime[j]] = phi[i] * phi[prime[j]];
	}
}

