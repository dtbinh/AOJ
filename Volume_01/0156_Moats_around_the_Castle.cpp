
#define _USE_MATH_DEFINES
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

using namespace std;

typedef long long ll;
typedef pair<int,int> P;

static const double eps = 10e-6;

char stage[100][100];
int costTable[100][100];

void bfs(int w,int h){
	const int t[][2] = {{1,0},{0,1},{-1,0},{0,-1}};
	int sx,sy;
	for(int y=0;y<h;y++){
		for(int x=0;x<w;x++){
			if(stage[y][x] == '&'){
				sx = x;
				sy = y;
				goto found;
			}
		}
	}
found:;

	memset(costTable,0x3,sizeof(costTable));
	queue<P> que;
	que.push(P(sx,sy));

	costTable[sy][sx] = 0;

	while(!que.empty()){
		int x = que.front().first;
		int y = que.front().second;
		que.pop();	

		for(int i=0;i<4;i++){
			int dx = x + t[i][0];
			int dy = y + t[i][1];
			if(dx < 0 || dx >= w || dy < 0 || dy >= h) continue;

			int cost = costTable[y][x] + ((stage[dy][dx] == '#' && stage[y][x] != '#') ? 1 : 0);
			if(costTable[dy][dx] <= cost) continue;

			costTable[dy][dx] = cost;
			que.push(P(dx,dy));
		}
	}
}

int seekExtWall(int w,int h){
	int res = 0x3333;

	for(int x=0;x<w;x++){
		res = min(res,costTable[0][x]);
	}

	for(int x=0;x<w;x++){
		res = min(res,costTable[h-1][x]);
	}

	for(int y=0;y<h;y++){
		res = min(res,costTable[y][0]);
	}

	for(int y=0;y<h;y++){
		res = min(res,costTable[y][w-1]);
	}

	return res;
}

void printCostTable(int w,int h){
	for(int y=0;y<h;y++){
		for(int x=0;x<w;x++){
			cout << costTable[y][x];
		}
		cout << endl;
	}
}

int main(){
	int w,h;
	while(~scanf("%d %d",&w,&h)){
		if(w==0 && h==0) break;
		for(int y=0;y<h;y++){
			char buf[128];
			scanf("%s",buf);
			for(int x=0;x<w;x++){
				stage[y][x] = buf[x];
			}
		}

		bfs(w,h);
		cout << seekExtWall(w,h) << endl;
		//printCostTable(w,h);
	}
}

