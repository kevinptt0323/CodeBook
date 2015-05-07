int* isp;
char fcnt[N+5];
int mobius[N+5];
void make_mobius(int n) {
	isp = mobius;
	memset(mobius, true, sizeof(mobius));
	memset(fcnt, 0, sizeof(fcnt));
	for(int i=2; i<=n; ++i) {
		if( isp[i] ) {
			fcnt[i] = 1;
			for(int j=i+i; j<=n; j+=i) {
				isp[j] = false;
				if( fcnt[j]!=-1 ) fcnt[j]++;
			}
			if( i<=10000 )
				for(int ii=i*i, j=ii; j<=n; j+=ii) {
					fcnt[j] = -1;
				}
		}
	}
	mobius[0] = 0;
	mobius[1] = 1;
	for(int i=2; i<=n; ++i) {
		if( fcnt[i]==-1 ) mobius[i] = 0;
		else if( fcnt[i]&1 ) mobius[i] = -1;
		else mobius[i] = 1;
	}
}

