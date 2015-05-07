int myrank[LEN], sa[LEN];
int height[LEN];
int y[LEN], cnt[LEN], rr[2][LEN];
inline bool same(int *_myrank, int a, int b, int l) { return _myrank[a]==_myrank[b]&&_myrank[a+l]==_myrank[b+l]; }
void make_height(char str[]) {
	int len=strlen(str);
	MSET(height, 0);
	for(int i=0, j=0; i<len; ++i, j=height[myrank[i-1]]-1) {
		if( myrank[i]==1 ) continue;
		if( j<0 ) j=0;
		while( i+j<len && sa[myrank[i]-1]+j<len &&
			str[i+j]==str[sa[myrank[i]-1]+j] ) ++j;
		height[myrank[i]]=j;
	}
}
void sa2(char str[], int n, int MAX = 256) {
	printf("%s!! %d %d\n", str, n, MAX);
	int *rank1=rr[0], *rank2=rr[1];
	int *myrank1=rr[0], *myrank2=rr[1]; // rolling array
	int *y = myrank; // share memory
	MSET(rr[1], 0);
	MSET(cnt, 0);
	int i, p=0;
	for(i=0; i<n; ++i) myrank2[i]=str[i], cnt[myrank2[i]]++;
	for(i=1; i<MAX; ++i) cnt[i]+=cnt[i-1];
	for(i=n-1; i>=0; --i) sa[--cnt[myrank2[i]]]=i;
	for(int j=1; p<n; j<<=1, MAX=p) {
		// 表示用第二個key(myrank2)排序後 從 y[i] 開始的後綴排第i名
		for(p=0, i=n-j; i<n; ++i) y[p++]=i;
		for(i=0; i<n; ++i) if( sa[i]>=j ) y[p++]=sa[i]-j;
		for(i=0; i<MAX; ++i) cnt[i]=0;
		for(i=0; i<n; ++i) cnt[ myrank2[y[i]] ] ++;
		for(i=1; i<MAX; ++i) cnt[i]+=cnt[i-1];
		for(i=n-1; i>=0; --i) sa[ --cnt[ myrank2[y[i]] ] ]=y[i];
		for(p=i=1, myrank1[sa[0]]=0; i<n; ++i)
			myrank1[sa[i]]=same(myrank2, sa[i], sa[i-1], j)?p-1:p++;
		std::swap(myrank1, myrank2);
	}
	for(int i=0; i<n; ++i) myrank[i]=myrank2[i];
	make_height(str);
}
int main() {
	char str[LEN];
	scanf("%s", str);
	int len = strlen(str);
	sa2(str, len+1);
	for(int i=1; i<=len; ++i) printf("%d %d %s\n", i, height[i], str+sa[i]);
}

