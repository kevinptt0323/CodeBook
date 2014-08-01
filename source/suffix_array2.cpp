#include <cstdio>
#include <cstring>
#include <algorithm>
#define MSET(x,y) memset(x, y, sizeof(x))
#define LEN 1000
int rank[LEN], sa[LEN];
int height[LEN];
int y[LEN], cnt[LEN], rr[2][LEN];
inline bool same(int *rank, int a, int b, int l) { return rank[a]==rank[b]&&rank[a+l]==rank[b+l]; }
void sa2(char str[], int n, int m) {
	printf("%s!! %d %d\n", str, n, m);
	int *rank1=rr[0], *rank2=rr[1];
	MSET(rr[1], 0);
	int i, p;
	for(i=0; i<m; ++i) cnt[i]=0;
	for(i=0; i<n; ++i) rank2[i]=str[i], cnt[rank2[i]]++;
	for(i=1; i<m; ++i) cnt[i]+=cnt[i-1];
	for(i=n-1; i>=0; --i) sa[--cnt[rank2[i]]]=i;
	for(int j=1; p<n; j<<=1, m=p) {
		// 表示用第二個key(rank2)排序後 從 y[i] 開始的後綴排第i名
		for(p=0, i=n-j; i<n; ++i) y[p++]=i;
		for(i=0; i<n; ++i) if( sa[i]>=j ) y[p++]=sa[i]-j;
		for(i=0; i<m; ++i) cnt[i]=0;
		for(i=0; i<n; ++i) cnt[ rank2[y[i]] ] ++;
		for(i=1; i<m; ++i) cnt[i]+=cnt[i-1];
		for(i=n-1; i>=0; --i) sa[ --cnt[ rank2[y[i]] ] ]=y[i];
		for(p=i=1, rank1[sa[0]]=0; i<n; ++i)
			rank1[sa[i]]=same(rank2, sa[i], sa[i-1], j)?p-1:p++;
		std::swap(rank1, rank2);
	}
	for(int i=0; i<n; ++i) rank[i]=rank2[i];
}
void make_height(char str[]) {
	int len=strlen(str);
	height[0]=0;
	for(int i=0, j=0; i<len; ++i, j=height[rank[i-1]]-1) {
		if( rank[i]==1 ) continue;
		if( j<0 ) j=0;
		while( i+j<len && sa[rank[i]-1]+j<len &&
			str[i+j]==str[sa[rank[i]-1]+j] ) ++j;
		height[rank[i]]=j;
	}
}
int main() {
	char str[LEN];
	scanf("%s", str);
	int len = strlen(str);
	sa2(str, len+1, 256);
	make_height(str);
	for(int i=1; i<=len; ++i) printf("%d %d %s\n", i, height[i], str+sa[i]);
}