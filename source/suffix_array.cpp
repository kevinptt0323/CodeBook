#include <cstdio>
#include <cstring>
#include <algorithm>
#define MSET(x,y) memset(x, y, sizeof(x))
#define LEN 1000
#define MP(x,y) make_pair(x,y)
using namespace std;
int RANK[LEN];
int SA[LEN];
int height[LEN];
pair< pair<int,int>,int > buf[LEN];
int flag;
int cc[2][LEN], rr[2][LEN+LEN];
void sort(pair< pair<int,int>,int > arr[], int n) {
	int *cnt = height;
	MSET(height, 0);
	int maxn=0;
	for(int i=0; i<n; ++i) {
		cnt[arr[i].first.second]++;
		if( maxn<arr[i].first.second ) maxn=arr[i].first.second;
	}
	for(int i=1; i<=maxn; ++i) cnt[i]+=cnt[i-1];
	for(int i=0; i<n; ++i) arr2[cnt[arr[i].first.second-1]++]=arr[i];
	MSET(height, 0);
	maxn=0;
	for(int i=0; i<n; ++i) {
		cnt[arr2[i].first.first]++;
		if( maxn<arr[i].first.first ) maxn=arr[i].first.first;
	}
	for(int i=1; i<maxn; ++i) cnt[i]+=cnt[i-1];
	for(int i=0; i<n; ++i) arr[cnt[arr2[i].first.first-1]++]=arr2[i];
}
void sa(char str[]) {
	int len=strlen(str);
	int *precnt=cc[0], *cnt=cc[1];
	int (*rank)=rr[0], (*newrank)=rr[1];
		// [1, maxrank]
	MSET(cc, 0); // count
	MSET(rr, 0);
	for(int i=0; str[i]; ++i) rank[i]=str[i]>='a'&&str[i]<='z'?str[i]-'a'+1:str[i]-'A'+27;
	for(int i=0; i<=26; ++i) precnt[i]=0;
	int i=0;
	do {
		for(int j=0; j<len; ++j) cnt[j]=0;
		flag=0;
		for(int j=0; j<len; ++j)
			buf[flag++]=MP(MP(rank[j], rank[j+i]), j);
		//std::sort(buf, buf+flag);
		sort(buf, flag);
		int nowrank=1;
		newrank[buf[0].second]=nowrank;
		for(int j=1; j<flag; ++j) {
			if( buf[j].first!=buf[j-1].first )
				++nowrank;
			newrank[buf[j].second]=nowrank;
		}
		swap(rank, newrank), swap(precnt, cnt);
		i<<=1;
		if( i==0 ) i=1;
	} while( i<len );
	for(int i=0; i<len; ++i)
		SA[rank[i]]=i, RANK[i]=rank[i];
}
void make_height(char str[]) {
	int len=strlen(str);
	height[0]=0;
	for(int i=0, j=0; i<len; ++i, j=height[RANK[i-1]]-1) {
		if( RANK[i]==1 ) continue;
		if( j<0 ) j=0;
		while( i+j<len && SA[RANK[i]-1]+j<len &&
			str[i+j]==str[SA[RANK[i]-1]+j] ) ++j;
		height[RANK[i]]=j;
	}
}
int main() {
	char str[LEN];
	scanf("%s", str);
	int len = strlen(str);
	sa(str);
	make_height(str);
	for(int i=1; i<=len; ++i) printf("%d %d %s\n", SA[i], height[i], str+SA[i]);
}