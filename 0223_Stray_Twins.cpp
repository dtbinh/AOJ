
#define _USE_MATH_DEFINES
#define INF 10000000
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <queue>
#include <stack>
#include <limits>
#include <map>
#include <string>
#include <cstring>
#include <set>
#include <deque>
#include <bitset>
#include <list>

using namespace std;

typedef long long ll;
typedef pair <int,int> P;
typedef pair <P,P> PP;
typedef pair <int,PP> PPP;

static const double eps = 1e-8;

static const int moveTo[][2] = {{1,0},{0,-1},{-1,0},{0,1}};
static const int moveToRev[][2] = {{-1,0},{0,1},{1,0},{0,-1}};

int stage[50][50];
int costTable[50][50][50][50];

int bfs(int tx,int ty,int kx,int ky,int w,int h){
	priority_queue<PPP,vector<PPP>,greater<PPP> > que;
	que.push(PPP(0,PP(P(tx,ty),P(kx,ky))));	
	memset(costTable,0x3,sizeof(costTable));

	int res = INF;
	costTable[tx][ty][kx][ky] = 0;
	while(!que.empty()){
		int cost = que.top().first;
		if(res <= cost || cost >= 100){
			return res;
		}

		int tx = que.top().second.first.first;
		int ty = que.top().second.first.second;
		int kx = que.top().second.second.first;
		int ky = que.top().second.second.second;

		if(tx==kx && ty == ky) res = min(res,cost);

		que.pop();

		for(int i=0;i<4;i++){
			int tdx = tx + moveTo[i][0];
			int tdy = ty + moveTo[i][1];

			if((tdx < 0 || tdx >= w || tdy < 0 || tdy >=h) || stage[tdy][tdx]) {
				tdx = tx;
				tdy = ty;
			}

			int kdx = kx + moveToRev[i][0];
			int kdy = ky + moveToRev[i][1];

			if((kdx < 0 || kdx >= w || kdy < 0 || kdy >=h) || stage[kdy][kdx]) {
				kdx = kx;
				kdy = ky;
			}
			if(costTable[tdx][tdy][kdx][kdy] <= cost + 1) continue;
			costTable[tdx][tdy][kdx][kdy] = cost + 1;
			que.push(PPP(cost+1,PP(P(tdx,tdy),P(kdx,kdy))));
		}
	}

	return res;
}

int main(){

	int w,h;
	while(~scanf("%d %d",&w,&h)){
		if(w == h && h==0) break;
		int tx,ty;
		scanf("%d %d",&tx,&ty);
		int kx,ky;
		scanf("%d %d",&kx,&ky);
		for(int y=0;y<h;y++){
			for(int x=0;x<w;x++){
				scanf("%d",&stage[y][x]);
			}
		}

		int res = bfs(tx-1,ty-1,kx-1,ky-1,w,h);
		if(res >= 100) printf("NA\n");
		else printf("%d\n",res);
	}
}

