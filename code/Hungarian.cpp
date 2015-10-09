#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define N 550             //max number of vertices in one part
#define INF 100000000    //just infinity

int cost[N][N];          //cost matrix
int n, max_match;        //n workers and n jobs
int lx[N], ly[N];        //labels of X and Y parts
int xy[N];               //xy[x] - vertex that is matched with x,
int yx[N];               //yx[y] - vertex that is matched with y
bool S[N], T[N];         //sets S and T in algorithm
int slack[N];            //as in the algorithm description
int slackx[N];           //slackx[y] such a vertex, that l(slackx[y]) + l(y) - w(slackx[y],y) = slack[y]
int pre[N];              //array for memorizing alternating paths


void init_labels() {
	memset(lx, 0, sizeof(lx));
	memset(ly, 0, sizeof(ly));
	for (int x = 0; x < n; x++)
		for (int y = 0; y < n; y++)
			lx[x] = max(lx[x], cost[x][y]);
}
void update_labels() {
	int x, y, delta = INF;             //init delta as infinity
	for (y = 0; y < n; y++)            //calculate delta using slack
		if (!T[y])
			delta = min(delta, slack[y]);
	for (x = 0; x < n; x++)            //update X labels
		if (S[x]) lx[x] -= delta;
	for (y = 0; y < n; y++)            //update Y labels
		if (T[y]) ly[y] += delta;
	for (y = 0; y < n; y++)            //update slack array
		if (!T[y])
			slack[y] -= delta;
}

void add_to_tree(int x, int prex) {
	S[x] = true;
	pre[x] = prex;
	for (int y = 0; y < n; y++)
		if (lx[x] + ly[y] - cost[x][y] < slack[y]){
			slack[y] = lx[x] + ly[y] - cost[x][y];
			slackx[y] = x;
		}
}

void augment() {
	if (max_match == n) return;
	int x, y, root;
	int q[N], wr = 0, rd = 0;

	memset(S, false, sizeof(S));
	memset(T, false, sizeof(T));
	memset(pre, -1, sizeof(pre));
	for (x = 0; x < n; x++)
		if (xy[x] == -1){
			q[wr++] = root = x;
			pre[x] = -2;
			S[x] = true;
			break;
		}

	for (y = 0; y < n; y++){
		slack[y] = lx[root] + ly[y] - cost[root][y];
		slackx[y] = root;
	}

	while (true){
		while (rd < wr){
			x = q[rd++];
			for (y = 0; y < n; y++)
				if (cost[x][y] == lx[x] + ly[y] &&  !T[y]){
					if (yx[y] == -1) break;
					T[y] = true;
					q[wr++] = yx[y];                                    //add vertex yx[y], which is matched with y, to the queue
					add_to_tree(yx[y], x);                              //add edges (x,y) and (y,yx[y]) to the tree
				}
			if (y < n) break;                                           //augmenting path found!
		}
		if (y < n) break;                                               //augmenting path found!
		update_labels();                                                //augmenting path not found, so improve labeling
		wr = rd = 0;                
		for (y = 0; y < n; y++)        
			if (!T[y] && slack[y] == 0){
				if (yx[y] == -1){                                       //exposed vertex in Y found - augmenting path exists!
					x = slackx[y];
					break;
				}
				else{
					T[y] = true;                                        //else just add y to T,
					if (!S[yx[y]]){    
						q[wr++] = yx[y];                                //add vertex yx[y], which is matched with y, to the queue
						add_to_tree(yx[y], slackx[y]);                  //and add edges (x,y) and (y, yx[y]) to the tree
					}
				}
			}
		if (y < n) break;                                               //augmenting path found!
	}
	if (y < n){                                                         //we found augmenting path!
		max_match++;                                                    //increment matching
		//in this cycle we inverse edges along augmenting path
		for (int cx = x, cy = y, ty; cx != -2; cx = pre[cx], cy = ty){
			ty = xy[cx];
			yx[cy] = cx;
			xy[cx] = cy;
		}
		augment();                                                      //recall function, go to step 1 of the algorithm
	}
}
int hungarian(){
	int ret = 0;                      //weight of the optimal matching
	max_match = 0;                    //number of vertices in current matching
	memset(xy, -1, sizeof(xy));
	memset(yx, -1, sizeof(yx));
	init_labels();                    //step 0
	augment();                        //steps 1-3
	for (int x = 0; x < n; x++)       //forming answer there
		ret += cost[x][xy[x]];
	return ret;
}
int main(){
	while ( scanf("%d",&n) == 1 ){
		for ( int i = 0 ; i < n ;i++ )
			for ( int j = 0 ; j < n ; j++ )
				scanf("%d",&cost[i][j]);
		int ret = hungarian();
		for ( int i = 0 ; i < n ;i++ )
			printf("%d%c",lx[i],i==n-1?'\n':' ');
		for ( int i = 0 ; i < n ; i++ )
			printf("%d%c",ly[i],i==n-1?'\n':' ');
		printf("%d\n",ret);
	}
	return 0;
}
