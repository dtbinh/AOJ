
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
typedef pair<int,int> P;

static const double eps = 1e-8;

int moveTo[][2] = {{-1,0},{1,0},{0,-1},{0,1}};

int stage[100][100];

void paint(int c,int d,int x,int y){
	//c:1~5 d: 0:horizonal 1:vertical
	if(d==0){
		for(int i=x;i<x+4;i++){
			for(int j=y;j<y+2;j++){
				stage[j][i] = c;
			}
		}
	}
	else{
		for(int i=x;i<x+2;i++){
			for(int j=y;j<y+4;j++){
				stage[j][i] = c;
			}
		}
	}
}

bool bfs(int w, int h, int xs, int ys, int xg, int yg){
	int cs = stage[ys][xs];
	int cg = stage[yg][xg];
	if(cs != cg) return false;

	queue<P> que;
	que.push(P(xs,ys));

	while(!que.empty()){
		int sx = que.front().first;
		int sy = que.front().second;
		
		if(sx == xg && sy == yg) return true;
		que.pop();

		stage[sy][sx] = -1;

		for(int i=0;i<4;i++){
			int dx = sx + moveTo[i][0];
			int dy = sy + moveTo[i][1];

			if(dx < 0 || dx >= w || dy < 0 || dy >= h) continue;
			if(stage[dy][dx] != cs || stage[dy][dx] == -1) continue;
			que.push(P(dx,dy));

		}

	}
	return false;
}

int main(){
	int w,h;
	while(~scanf("%d %d",&w,&h)){
		if(w==h && h==0) break;
		memset(stage,-1,sizeof(stage));
		int xs,ys;
		scanf("%d %d",&xs,&ys);

		int xg,yg;
		scanf("%d %d",&xg,&yg);

		int n;
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			int c,d,x,y;
			//c:1~5 d: 0:horizonal 1:vertical
			scanf("%d %d %d %d",&c,&d,&x,&y);
			paint(c,d,x-1,y-1);
		}

		printf("%s\n",bfs(w,h,xs-1,ys-1,xg-1,yg-1) ? "OK" : "NG");
	}
}

