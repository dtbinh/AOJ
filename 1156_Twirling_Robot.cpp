
#define _USE_MATH_DEFINES
#define INF 100000000

#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>
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
#include <cctype>
#include <utility>

using namespace std;

typedef long long ll;
typedef pair <int,int> P;

static const double EPS = 1e-8;

int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};

class Data{
public:
	int cost;
	int x;
	int y;
	int dir;

	Data(int cost,int x,int y,int dir){
		this->cost = cost;
		this->x = x;
		this->y = y;
		this->dir = dir;
	}
	bool operator>(const Data& d1) const{
		return cost > d1.cost;
	}
};

int stage[31][31];
int costTable[31][31][4];
int W,H;

void dfs(int x,int y,int dir,int* c){
	for(int i=0;i<=3;i++){
		int cost = c[i];
		if(stage[y][x] == i) cost = 0;

		int prev = dir;
		int next = (prev+i)%4;
		int dx = x + tx[next];
		int dy = y + ty[next];


		if(dx < 0 || dx >= W || dy < 0 || dy >= H) continue;
		if(costTable[dy][dx][next] > costTable[y][x][prev] + cost){
			costTable[dy][dx][next] = costTable[y][x][prev] + cost;
			dfs(dx,dy,next,c);
		}
	}
}

int main()
{
	while(~scanf("%d %d",&W,&H)){
		if(W==H && H==0) break;

		memset(costTable,0x3f,sizeof(costTable));

		for(int y=0;y<H;y++){
			for(int x=0;x<W;x++){
				scanf("%d",&stage[y][x]);
			}
		}

		int c[4];
		for(int i=0;i<4;i++){
			scanf("%d",c+i);
		}
		//costTable[0][0][1] = 0;

		priority_queue<Data,vector<Data>,greater<Data> > que;

		que.push(Data(0,0,0,1));

		while(!que.empty()){
			int sum = que.top().cost;
			int x = que.top().x;
			int y = que.top().y;
			int dir = que.top().dir;

			que.pop();
			if(costTable[y][x][dir] != 0x3f3f3f3f) continue;
			
			costTable[y][x][dir] = sum;

			for(int i=0;i<=3;i++){
				int cost = c[i];
				if(stage[y][x] == i) cost = 0;

				int prev = dir;
				int next = (prev+i)%4;
				int dx = x + tx[next];
				int dy = y + ty[next];

				if(dx < 0 || dx >= W || dy < 0 || dy >= H) continue;
				if(costTable[dy][dx][next] == 0x3f3f3f3f){
					//printf("dx:%d dy:%d \n",dx,dy);
					//printf("sum:%d prev:%d next:%d\n",sum,prev,next);
					//costTable[dy][dx][next] = sum;
					que.push(Data(sum+cost,dx,dy,next));
				}
			}

		}

		//dfs(0,0,1,c);

		int minv = numeric_limits<int>::max();
		for(int i=0;i<=3;i++){
			minv = min(minv,costTable[H-1][W-1][i]);
		}

		printf("%d\n",minv);
	}
}

