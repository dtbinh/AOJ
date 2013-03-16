
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

using namespace std;

typedef long long ll;
typedef pair<double,int> P;

static const double eps = 10e-9;

const int tgt[][2] = {{0,1},{1,0},{0,-1},{-1,0}};

void dfs(int stage[101][101],int x,int y,int dir,int w){

	//printf("x:%d y:%d\n",x,y);
	if(stage[y][x]) return;	

	int dx;
	int dy;

	int c=0;
	for(int i=0;i<4;i++){
		dx = x+tgt[i][0];
		dy = y+tgt[i][1];
		if(dx < 0 || dx >= w || dy < 0 || dy >= w) continue;
		if(stage[dy][dx]) c++;
	}

	if(c>=2) return;

	dx = x+tgt[dir][0];
	dy = y+tgt[dir][1];

	int jx = x+tgt[dir][0]*2;
	int jy = y+tgt[dir][1]*2;

	stage[y][x] = 1;

	if(!(jx < 0 || jx >= w || jy < 0 || jy >= w) && stage[jy][jx]){
		dx = x+tgt[(dir+1)%4][0];
		dy = y+tgt[(dir+1)%4][1];
		dfs(stage,dx,dy,(dir+1)%4,w);
	}

	else if(dx < 0 || dx >= w || dy < 0 || dy >= w){
		dx = x+tgt[(dir+1)%4][0];
		dy = y+tgt[(dir+1)%4][1];
		dfs(stage,dx,dy,(dir+1)%4,w);
	}


	else dfs(stage,dx,dy,dir,w);

}

int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		int w;
		scanf("%d",&w);
		int x=0;
		int y=0;

		int stage[101][101];
		memset(stage,0,sizeof(stage));
		int dir = 0;
		int change = 0;

		dfs(stage,0,0,0,w);
		for(int ty = w-1; ty>=0;ty--){
			for(int tx=0; tx<w;tx++){
				cout << (stage[ty][tx] ? '#' : ' ');
			}
			cout << endl;
		}

		if(i<n-1) cout << endl;
	}
}


