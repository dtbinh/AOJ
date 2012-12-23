
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
typedef pair <int,P> PP;

static const double EPS = 1e-8;

int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};

int cost[30][30][30][30];
int visited[30][30];
int W,H;

int main()
{
	while(~scanf("%d %d",&W,&H)){
		if(W==H && H==0) break;
		memset(cost,0,sizeof(cost));
		memset(visited,0x3f,sizeof(visited));

		for(int y=0;y<2*H-1;y++){
			if(y%2==0){
				for(int x=0;x<W-1;x++){
					int n;
					scanf("%d",&n);
					cost[y/2][x][y/2][x+1] = n;
					cost[y/2][x+1][y/2][x] = n;
				}
			}
			else{
				for(int x=0;x<W;x++){
					int n;
					scanf("%d",&n);
					cost[y/2][x][y/2+1][x] = n;
					cost[y/2+1][x][y/2][x] = n;
				}
			}
		}

		priority_queue<PP,vector<PP>,greater<PP> > que;
		que.push(PP(0,P(0,0)));

		visited[0][0] = 0;
		while(!que.empty()){
			int d = que.top().first;
			int x = que.top().second.first;
			int y = que.top().second.second;
			que.pop();

			for(int i=0;i<4;i++){
				int dx = x + tx[i];
				int dy = y + ty[i];
				if(dx < 0 || dx >= W || dy < 0 || dy >= H) continue;
				if(cost[y][x][dy][dx]==1) continue;
				if(visited[dy][dx] <= d+1) continue;

				visited[dy][dx] = d+1;
				que.push(PP(d+1,P(dx,dy)));
			}
		}

		printf("%d\n",visited[H-1][W-1] == 0x3f3f3f3f ? 0 : visited[H-1][W-1] + 1);
	}
}

