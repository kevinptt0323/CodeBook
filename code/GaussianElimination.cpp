// default for module version, comments for double version
// double mmap[row][column];
const ll modn = 1000000007;
ll mmap[row][column];
ll inv(ll b) {
	return (b==1)?1:inv(modn%b)*(modn-modn/b)%modn; 
}
void gauss(int n,int m) {
	int k=0;
	for(int i=0; i<m; i++)
		for(int j=k; j<n; j++)
			if(mmap[j][i]!=0) {
				for(int l=i; l<m; l++)
					swap(mmap[k][l],mmap[j][l]);
				for(j++; j<n; j++){
					if(mmap[j][i]==0)
						continue;
					//double scale=mmap[j][i]/mmap[k][i];
					ll scale=mmap[j][i]*inv(mmap[k][i])%modn;
					for(int p=i+1; p<n; p++)
						//mmap[j][p]-=mmap[k][p]*scale;
						mmap[j][p]=(mmap[j][p]-mmap[k][p]*scale%modn+modn)%modn;
					mmap[j][i]=0;
				}
				k++;
				break;
			}
}

