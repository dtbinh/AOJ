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
    int gx,gy;
    for(int y = 0; y < H; y++){
      char line[70];
      scanf("%s",line);
      for(int x = 0; x < W; x++){
	stage[y][x] = line[x];
	if(stage[y][x] == 'K'){
	  sx = x;
	  sy = y;
	}
	if(stage[y][x] == 'M'){
	  gx = x;
	  gy = y;
	}
      }
    }

    priority_queue<State,vector<State>,greater<State> > que;
    que.push(State(sx,sy,0,0));
    bool visited[20][70][4] = {};
    int flag = 0;

    while(!que.empty()){
      State s = que.top();
      que.pop();
      if(s.x == gx && s.y == gy){
	flag |= (1<<0);
	int dx = s.x;
	int dy = s.y;
	int dir = (s.dir + 2) % 4;
	while(true){
	  if(stage[dy + ty[dir]][dx + tx[dir]] == '#'){
	    if(s.commands.size() == 0) break;
	    dir = dir + (s.commands.back() == 0 ? 1 : 3);
	    dir %= 4;
	    s.commands.pop_back();
	  }
	  else{
	    dy = dy + ty[dir];
	    dx = dx + tx[dir];
	  }
	  if(dx == sx && dy == sy){
	    flag |= (1<<1);
	    break;
	  }
	}
	continue;     
      }

      for(int i = 0; i < 4; i++){
	int dx = tx[s.dir] + s.x;
	int dy = ty[s.dir] + s.y;
	if(dy >= H || dx >= W || dy < 0 || dx < 0) continue;
	if(stage[dy][dx] == '#'){
	  if(!visited[s.y][s.x][(s.dir + 1) % 4]){
	    vector<int> next = s.commands;
	    next.push_back(1);
	    visited[s.y][s.x][(s.dir + 1) % 4] = true;
	    que.push(State(s.x,s.y,s.cost + 1,(s.dir + 1) % 4,next));
	  }
	  if(!visited[s.y][s.x][(s.dir + 3) % 4]){
	    vector<int> next = s.commands;
	    next.push_back(0);
	    visited[s.y][s.x][(s.dir + 3) % 4] = true;
	    que.push(State(s.x,s.y,s.cost + 1,(s.dir + 3) % 4,next));
	  }
	}
	else if(stage[dy][dx] == '.'
		|| stage[dy][dx] == 'K'
		|| stage[dy][dx] == 'M'){
	  visited[dy][dx][s.dir] = true;
	  que.push(State(dx,dy,s.cost + 1,s.dir,s.commands));
	}
      }
    }

    if(flag == (1<<2) - 1){
      printf("He can accomplish his mission.\n");
    }
    else if(flag == (1<<0)){
      printf("He cannot return to the kitchen.\n");
    }
    else{
      printf("He cannot bring tea to his master.\n");
    }
  }
}
