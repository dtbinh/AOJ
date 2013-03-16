
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

using namespace std;

typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P> PP;
typedef pair<P,P> P2;

static const double eps = 1e-8;

const int tx[4] = {-1,0,1,0};
const int ty[4] = {0,1,0,-1};

char stage[1001][1001];
int gCost[1001][1001];

int main(){
	int W,H,N;
	while(~scanf("%d %d %d",&H,&W,&N)){
		for(int y=0;y<H;y++){
			char buf[1024];
			scanf("%s",buf);
			for(int x=0;x<W;x++){
				stage[y][x] = buf[x];
			}
		}

		vector<P> pos;
		for(int i=0;i<=N;i++){				
			for(int y=0;y<H;y++){
				for(int x=0;x<W;x++){
					if(i==0){
						if(stage[y][x] == 'S'){
							pos.push_back(P(x,y));
							goto next;
						}
					}
					else{
						if(stage[y][x] == '0' + i){
							pos.push_back(P(x,y));
							goto next;
						}
					}
				}
			}
next:;
		}

		priority_queue<P2,vector<P2>,greater<P2> > que; 
		for(int i=0;i+1<pos.size();i++){
			que.push(P2(P(pos[i].first,pos[i].second),P(pos[i+1].first,pos[i+1].second)));
		}

		int res = 0;
		while(!que.empty()){
			int sx = que.top().first.first;
			int sy = que.top().first.second;
			int gx = que.top().second.first;
			int gy = que.top().second.second;

			que.pop();

			queue<PP> que2;
			que2.push(PP(0,P(sx,sy)));

			memset(gCost,0x3,sizeof(gCost));
			gCost[sy][sx] = 0;
			while(!que2.empty()){
				int cost = que2.front().first;
				int x = que2.front().second.first;
				int y = que2.front().second.second;

				que2.pop();
				
				for(int i=0;i<4;i++){
					int dx = x + tx[i];
					int dy = y + ty[i];
					if(dx == gx && dy == gy) {
						res += cost + 1;
						while(!que2.empty()) que2.pop();
						break;
					}
					if(dx < 0 || dx >= W || dy < 0 || dy >= H) continue;
					if(stage[dy][dx] == 'X') continue;
					if(gCost[dy][dx] <= cost + 1) continue;
					gCost[dy][dx] = cost + 1;
					que2.push(PP(cost+1,P(dx,dy)));
				}
			}
		}

		printf("%d\n",res);
	}
}

