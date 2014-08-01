/**********************
 * Ural 1519 - 插頭DP *
 **********************/
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;

#define MOD 130003
#define GET_STATE(ST, I) ((ST>>((I)<<1)) & 3)
#define CHANGE_STATE(ST, I, BIT) ( (ST^(ST&(3<<((I)<<1)))) | (BIT<<((I)<<1)) )

#ifdef _WIN32
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

bool board[20][20];
int posQQ[MOD]; // position in state queue
ll dp[2][MOD];
int state[2][MOD], back[2];
/* 3^12 
 * 0 # , 1 ( , 2 )
 */

void hashinit(int flag) {
	memset(dp[flag], 0, sizeof(dp[flag]));
	memset(posQQ, -1, sizeof(posQQ));
	back[flag] = 0;
}

void hashadd(ll state0, ll val, int flag) {
	int hashpos = state0*10007%MOD;
	int delta = 1;
	while( ~posQQ[hashpos] ) {
		if( state[flag][posQQ[hashpos]]==state0) {
			dp[flag][posQQ[hashpos]] += val;
			return;
		}
		hashpos = (hashpos+delta)%MOD;
		delta = (delta<<1)%MOD;
	}
	posQQ[hashpos] = back[flag];
	dp[flag][ back[flag] ] = val;
	state[flag][ back[flag]++ ] = state0; // push into queue
}

ll solve(const int& n, const int& m, const int& endi, const int& endj) {
	memset(dp, 0, sizeof(dp));
	memset(posQQ, -1, sizeof(posQQ));
	back[0] = back[1] = 0;
	hashadd(0, 1, 1);
	int nowstate, s1, s2, nxtstate;
	ll ans = 0;
	for(int i=0, i2=0; i2<n; ++i2) {
		for(int j=0; j<back[!i]; ++j) state[!i][j]<<=2;
		for(int j=0; j<m; ++j, i^=1) {
			hashinit(i);
			//printf("%d %d %d\n", i2, j, back[!i]);
			for(int k=0; k<back[!i]; ++k) {
				nowstate = state[!i][k];
				s1 = GET_STATE(nowstate, j);	// 左插頭
				s2 = GET_STATE(nowstate, j+1);	// 上插頭
				//printf("%2dth : [%d %d] (%d) -- %d\n", k, s1, s2, nowstate, dp[!i][k]);
				if( board[i2][j] ) {
					if( s1==0 && s2==0 ) hashadd(nowstate, dp[!i][k], i);
					continue;
				}
				if( s1==0 && s2==0 ) {
					if( !board[i2+1][j] && !board[i2][j+1] ) {
						nxtstate = nowstate;
						nxtstate = CHANGE_STATE(nxtstate, j, 1);
						nxtstate = CHANGE_STATE(nxtstate, j+1, 2);
						hashadd(nxtstate, dp[!i][k], i);
					}
				}
				else if( s1==0 && s2 ) {
					if( !board[i2+1][j] ) {
						nxtstate = nowstate;
						nxtstate = CHANGE_STATE(nxtstate, j, s2);
						nxtstate = CHANGE_STATE(nxtstate, j+1, 0);
						hashadd(nxtstate, dp[!i][k], i);
					}
					if( !board[i2][j+1] ) hashadd(nowstate, dp[!i][k], i);
				}
				else if( s1 && s2==0 ) {
					if( !board[i2+1][j] ) hashadd(nowstate, dp[!i][k], i);
					if( !board[i2][j+1] ) {
						nxtstate = nowstate;
						nxtstate = CHANGE_STATE(nxtstate, j, 0);
						nxtstate = CHANGE_STATE(nxtstate, j+1, s1);
						hashadd(nxtstate, dp[!i][k], i);
					}
				}
				else if( s1==1 && s2==1 ) {
					int cnt_bracket = 1, tmp;
					nxtstate = nowstate;
					nxtstate = CHANGE_STATE(nxtstate, j, 0);
					nxtstate = CHANGE_STATE(nxtstate, j+1, 0);
					for(int idx = j+2; idx<=m; ++idx) {
						tmp = GET_STATE(nowstate, idx);
						if( tmp==1 ) ++cnt_bracket;
						else if( tmp==2 ) --cnt_bracket;
						if( cnt_bracket==0 ) {
							nxtstate = CHANGE_STATE(nxtstate, idx, 1);
							hashadd(nxtstate, dp[!i][k], i);
							break;
						}
					}
				}
				else if( s1==2 && s2==1 ) {
					nxtstate = nowstate;
					nxtstate = CHANGE_STATE(nxtstate, j, 0);
					nxtstate = CHANGE_STATE(nxtstate, j+1, 0);
					hashadd(nxtstate, dp[!i][k], i);
				}
				else if( s1==2 && s2==2 ) {
					int cnt_bracket = 1, tmp;
					nxtstate = nowstate;
					nxtstate = CHANGE_STATE(nxtstate, j, 0);
					nxtstate = CHANGE_STATE(nxtstate, j+1, 0);
					for(int idx = j-1; idx>=0; --idx) {
						tmp = GET_STATE(nowstate, idx);
						if( tmp==1 ) --cnt_bracket;
						else if( tmp==2 ) ++cnt_bracket;
						if( cnt_bracket==0 ) {
							nxtstate = CHANGE_STATE(nxtstate, idx, 2);
							hashadd(nxtstate, dp[!i][k], i);
							break;
						}
					}
				}
				else if( s1==1 && s2==2 ) {
					if( i2==endi && j==endj ) ans+=dp[!i][k];
				}
			}
		}
	}
	return ans;
}

int main() {
#ifdef KEVINPTT
	//freopen("a.in", "r", stdin);
	//freopen("a.ans", "w", stdout);
#endif
	int n, m, endi, endj;
	char str[20];
	while( ~scanf("%d %d", &n, &m) ) {
		memset(board, true, sizeof(board));
		for(int i=0; i<n; ++i) {
			scanf("%s", str);
			for(int j=0; str[j]; ++j) {
				board[i][j] = str[j]=='*';
				if( !board[i][j] ) endi = i, endj = j;
			}
		}
		printf(LLD "\n", solve(n, m, endi, endj));
	}
	
	return 0;
}

