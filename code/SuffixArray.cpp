const int LEN = 1000;
int rk[LEN], sa[LEN];
int height[LEN];
int cnt[LEN], rr[2][LEN];
inline bool same(int *_rk, int a, int b, int l) { return _rk[a]==_rk[b]&&_rk[a+l]==_rk[b+l]; }
void make_height(char str[]) {
	int len=strlen(str);
	memset(height, 0, sizeof(height));
	for(int i=0, j=0; i<len; ++i, j=height[rk[i-1]]-1) {
		if (rk[i]==1) continue;
		if (j<0) j=0;
		while (i+j<len && sa[rk[i]-1]+j<len &&
				str[i+j]==str[sa[rk[i]-1]+j]) ++j;
		height[rk[i]]=j;
	}
}
void suffix_array(char str[], int n, int MAXRK = 256) {
	int *rk1=rr[0], *rk2=rr[1]; // rolling array
	int *y = rk; // share memory
	memset(rr[1], 0, sizeof(rr[1]));
	memset(cnt, 0, sizeof(cnt));
	int i, p;
	for(i=0; i<n; ++i) rk2[i]=str[i], cnt[rk2[i]]++;
	for(i=1; i<MAXRK; ++i) cnt[i]+=cnt[i-1];
	for(i=n-1; i>=0; --i) sa[--cnt[rk2[i]]]=i;
	for(int j=1; p<n; j<<=1, MAXRK=p) {
		// 表示用第二個key(rk2)排序後 從 y[i] 開始的後綴排第i名
		for(p=0, i=n-j; i<n; ++i) y[p++]=i;
		for(i=0; i<n; ++i) if (sa[i]>=j) y[p++]=sa[i]-j;
		memset(cnt, 0, sizeof(cnt));
		for(i=0; i<n; ++i) cnt[ rk2[y[i]] ] ++;
		for(i=1; i<MAXRK; ++i) cnt[i]+=cnt[i-1];
		for(i=n-1; i>=0; --i) sa[ --cnt[ rk2[y[i]] ] ]=y[i];
		for(p=i=1, rk1[sa[0]]=0; i<n; ++i)
			rk1[sa[i]] = same(rk2, sa[i], sa[i-1], j) ? p-1 : p++;
		swap(rk1, rk2);
	}
	copy(rk, rk+n, rk2);
	make_height(str);
}
int main() {
	char str[LEN];
	scanf("%s", str);
	int len = strlen(str);
	suffix_array(str, len+1);
	for(int i=1; i<=len; ++i) printf("%d %d %s\n", i, height[i], str+sa[i]);
}

