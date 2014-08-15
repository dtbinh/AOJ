#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f

#include <iostream>
#include <cstdio>
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
  
static const int tx[] = {+1,+0,-1};
static const int ty[] = {+0,+1,+0};

class State {
public:
  int x,y;
  int volume;
  int cost;
  int visited[11];
  State(int _x,int _y,int _v,int _c,int _vis[11]) :
    x(_x),y(_y),volume(_v),cost(_c) {
    memcpy(visited,_vis,sizeof(int)*11);
    visited[_y] |= (1 << _x);
  }
  State(int _x,int _y,int _v,int _c) :
    x(_x),y(_y),volume(_v),cost(_c) {}

  State& init(){
    memset(visited,0,sizeof(visited));
    return *this;
  }

  State& add(int _x,int _y){
    visited[_y] |= (1 << _x);
    return *this;
  }

  bool operator<(const State& s) const {
    return cost < s.cost;
  }
  bool operator>(const State& s) const {
    return cost > s.cost;
  }
};

int dp[1<<11][11][11];

int main(){
  int W,H;
  while(~scanf("%d %d",&W,&H)){
    if(W == 0 && H == 0) break;

    int upper_cost;
    int capacity;
    int initial_volume;
    scanf("%d %d %d",&upper_cost,&capacity,&initial_volume);

    int stage[11][11];
    for(int y=0; y < H; y++){
      for(int x=0; x < W; x++){
	scanf("%d",&stage[y][x]);
      }
    }

    priority_queue<State,vector<State>,greater<State> > que;

    memset(dp,0x3f,sizeof(dp));
    for(int sx = 0; sx < W; sx++){
      State root(sx,-1,initial_volume,0);
      root.init();
      que.push(root);
      
      while(!que.empty()){
	State s = que.top();
	que.pop();
	
	int x = s.x;
	int y = s.y;
	for(int i = 0; i < 3; i++){
	  if(y == -1 && i != 1) continue;
	  int dx = tx[i] + x;
	  int dy = ty[i] + y;
	  if(dx < 0 || dx >= W
	     || dy < 0 || dy >= H) continue;
	  
	  int next_cost = s.cost;
	  int next_volume = s.volume - 1;
	  
	  if(next_volume <= 0) continue;
	  
	  if(stage[dy][dx] < 0){
	    next_cost += -stage[dy][dx];
	  }
	  else{
	    if(s.visited[dy] & (1<<dx)) continue;
	    next_volume += stage[dy][dx];
	    if(next_volume > capacity) next_volume = capacity;
	  }
	  
	  if(next_cost > upper_cost) continue;
	  
	  int next_visited = (s.visited[dy] | (1<<dx));
	  if(dp[next_visited][dx][dy] <= next_cost) continue;
	  dp[next_visited][dx][dy] = next_cost;
	  que.push(State(dx,dy,next_volume,next_cost,s.visited));
	}
      }
    }

    int res = INF;
    for(int S = 0; S <= (1 << 10) - 1; S++){
      for(int x = 0; x < W; x++){
	if(res > dp[S][x][H-1]){
	  res = dp[S][x][H-1];

	}
      }
    }

    if(res == INF){
      printf("NA\n");
    }
    else{
      printf("%d\n",res);
    }
  }
}
