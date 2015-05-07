int china_remainder_theorem(int n, int ai[], int mi[]) {
	int gcdn, x, y, reduce, tmp;
	for(int i=1; i<n; ++i) {
		gcdn=ext_gcd(mi[i-1], mi[i], x, y);
		reduce=ai[i]-ai[i-1];
		if( reduce%gcdn!=0 )
			return -1;
		tmp=mi[i]/gcdn;
		x=(reduce/gcdn*x%tmp+tmp)%tmp;
		ai[i] = ai[i-1] + mi[i-1]*x;
		mi[i] = mi[i-1]*tmp;
	}
	return ai[n-1]%mod;
}

