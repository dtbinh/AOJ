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
#include <complex>
#include <assert.h>

using namespace std;

typedef long long ll;
typedef pair <int,int> P;

static const double EPS = 1e-12;

int tx[] = {+0,+1,+0,-1};
int ty[] = {-1,+0,+1,+0};

class State {
public:
  int x;
  int y;
  int cost;
  int dir;
  vector<int> commands;
  State(int x,int y,int cost,int dir)
    : x(x),y(y),cost(cost),dir(dir) {}
  State(int x,int y,int cost,int dir,const vector<int>& commands)
    : x(x),y(y),cost(cost),dir(dir),commands(commands) {}
  bool operator<(const State& s) const {
    return cost < s.cost;
  }
  bool operator>(const State& s) const {
    return cost > s.cost;
  }
};

int main(){
  int W,H;
  while(~scanf("%d %d",&W,&H)){
    if(W == 0 && H == 0) break;
    char stage[20][70];
    int sx,sy;
    for(int y = 0; y < H; y++){
      char line[70];
      scanf("%s",line);
      for(int x = 0; x < W; x++){
	stage[y][x] = line[x];
	if(stage[y][x] == 'K'){
	  sx = x;
	  sy = y;
	}
      }
    }

    priority_queue<State,vector<State>,greater<State> > que;
    que.push(State(sx,sy,0,0));
    bool visited[20][70][4] = {};

    while(!que.empty()){
      State s = que.top();
      que.pop();
      for(int i = 0; i < 4; i++){
	int dx = tx[s.dir] + s.x;
	int dy = ty[s.dir] + s.y;
	if(dy >= H || dx >= W || dy < 0 || dx > 0) continue;
	if(stage[dy][dx] == '#'){
	  if(!visited[dy][dx][(s.dir + 1) % 4]){
	    vector<int> next = s.commands;
	    next.push_back(1);
	    visited[dy][dx][(s.dir + 1) % 4] = true;
	    que.push(State(dx,dy,s.cost + 1,(s.dir + 1) % 4,next));
	  }
	  if(!visited[dy][dx][(s.dir + 3) % 4]){
	    vector<int> next = s.commands;
	    next.push_back(0);
	    visited[dy][dx][(s.dir + 3) % 4] = true;
	    que.push(State(dx,dy,s.cost + 1,(s.dir + 3) % 4,next));
	  }
	}
      }
    }
  }
}
