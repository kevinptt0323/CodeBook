// default for module version, comments for double version
//double mmap[row][column];
const ll modn = 1000000007;
ll mmap[row][column];
ll inv(ll b)
{
	return (b==1)?1:inv(modn%b)*(modn-modn/b)%modn; 
}
void gauss(ll mat[row][column],int n,int m)
{
	int k=0;
	for(int i=0; i<m; i++)
		for(int j=k; j<n; j++)
			if(mat[j][i]!=0){
				for(int l=i; l<m; l++)
					swap(mat[k][l],mat[j][l]);
				for(j++; j<n; j++){
					if(mat[j][i]==0)
						continue;
					//double scale=mat[j][i]/mat[k][i];
					long long scale=mat[j][i]*inv(mat[k][i])%modn;	//mod version
					for(int p=i+1; p<m; p++)
						//mat[j][p]-=mat[k][p]*scale;
						mat[j][p]=(mat[j][p]-mat[k][p]*scale%modn+modn)%modn;
					mat[j][i]=0;
				}
				k++;
				break;
			}
}
