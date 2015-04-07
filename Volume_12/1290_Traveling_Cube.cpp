#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <cstdio>
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
#include <iterator>
#include <complex>
#include <assert.h>
 
using namespace std;
 
typedef long long ll;
typedef pair <double,double> P;
typedef pair <int,P > PP;
 
int tx[] = {+0,+1,+0,-1};//URDL
int ty[] = {-1,+0,+1,+0};
 
static const double EPS = 1e-8;

enum Dir {
  TOP,
  BOTTOM,
  NORTH,
  SOUTH,
  EAST,
  WEST,
};

enum Color {
  RED,
  CYAN,
  GREEN,
  MAGENTA,
  BLUE,
  YELLOW,
};

class Cube {
public:
  Color surface[6];
  Cube(){
    surface[TOP] = RED;
    surface[BOTTOM] = CYAN;
    surface[NORTH] = GREEN;
    surface[SOUTH] = MAGENTA;
    surface[EAST] = BLUE;
    surface[WEST] = YELLOW;
  }

  Cube(const Cube& c){
    surface[TOP] = c.surface[TOP];
    surface[SOUTH] = c.surface[SOUTH];
    surface[BOTTOM] = c.surface[BOTTOM];
    surface[NORTH] = c.surface[NORTH];
    surface[EAST] = c.surface[EAST];
    surface[WEST] = c.surface[WEST];
  }
  
  void pitch(int num){
    //SOUTH,BOTTOM,NORTH,TOP
    for(int i=0;i<num;i++){
      Color next[6];
      memcpy(next,surface,sizeof(Color)*6);
      next[SOUTH] = surface[BOTTOM];
      next[TOP] = surface[SOUTH];
      next[NORTH] = surface[TOP];
      next[BOTTOM] = surface[NORTH];
      memcpy(surface,next,sizeof(Color)*6);
    }
  }
  void yaw(int num){
    //WEST,SOUTH,EAST,NORTH
    for(int i=0;i<num;i++){
      Color next[6];
      memcpy(next,surface,sizeof(Color)*6);
      next[WEST] = surface[SOUTH];
      next[SOUTH] = surface[EAST];
      next[EAST] = surface[NORTH];
      next[NORTH] = surface[WEST];
      memcpy(surface,next,sizeof(Color)*6);
    }
  }
  void roll(int num){
    //TOP,WEST,BOTTOM,EAST
    for(int i=0;i<num;i++){
      Color next[6];
      memcpy(next,surface,sizeof(Color)*6);
      next[TOP] = surface[WEST];
      next[WEST] = surface[BOTTOM];
      next[BOTTOM] = surface[EAST];
      next[EAST] = surface[TOP];
      memcpy(surface,next,sizeof(Color)*6);
    }
  }
  int get_hash() const{
    return 7 * 7 * (surface[TOP] + 1) + 7 * (surface[NORTH] + 1) + (surface[EAST] + 1);
  }
  char get_top() const{
    const char dict[] = {'r','c','g','m','b','y'};
    return dict[surface[TOP]];
  }
};

char stage[31][31];
char order[8];
int H,W;
int visited[31][31][7*7*7][6];

void disp(){
  for(int y = 0; y < H; y++){
    for(int x = 0; x < W; x++){
      printf("%d",visited[y][x][0][0] == INF ? 0 : 1);
    }
    printf("\n");
  }
  printf("\n");
}

class State {
public:
  Cube cube;
  int x;
  int y;
  int cost;
  int step;
  State(const Cube& cube,int x,int y,int cost,int step)
    : cube(cube),x(x),y(y),cost(cost),step(step) {}
  bool operator<(const State& s) const {
    return cost < s.cost;
  }
  bool operator>(const State& s) const {
    return cost > s.cost;
  }
};

bool invalid(int step,char square){
  for(int i = 0; i < step; i++){
    if(order[i] == square){
      return true;
    }
  }
  return false;
}

int bfs(int sx,int sy){
  priority_queue<State,vector<State>,greater<State> > que;
  Cube init;

  que.push(State(init,sx,sy,0,0));
  visited[sy][sx][init.get_hash()][0] = 0;

  while(!que.empty()){
    State s = que.top();
    que.pop();
    if(s.step == 6){
      return s.cost;
    }
    Cube prev = s.cube;
    for(int i = 0; i < 4; i++){
      int dx = tx[i] + s.x;
      int dy = ty[i] + s.y;
      if(dx >= W || dy >= H || dx < 0 || dy < 0) continue;
      if(stage[dy][dx] == 'k') continue;
	
      if(i == 0){
	s.cube.pitch(1);
      }
      else if(i == 1){
	s.cube.roll(1);
      }
      else if(i == 2){
	s.cube.pitch(3);
      }
      else if(i == 3){
	s.cube.roll(3);
      }
      
      if(stage[dy][dx] == 'w'){
	if(visited[dy][dx][s.cube.get_hash()][s.step] <= s.cost + 1){
	  s.cube = prev;
	  continue;
	}
	visited[dy][dx][s.cube.get_hash()][s.step] = s.cost + 1;
	que.push(State(s.cube,dx,dy,s.cost + 1, s.step));
      }
      else if(s.cube.get_top() == stage[dy][dx]){
	if(order[s.step] == stage[dy][dx]){
	  if(visited[dy][dx][s.cube.get_hash()][s.step] <= s.cost + 1){
	    s.cube = prev;
	    continue;
	  }
	  if(invalid(s.step,stage[dy][dx])){
	    s.cube = prev;
	    continue;
	  }
	  visited[dy][dx][s.cube.get_hash()][s.step] = s.cost + 1;
	  que.push(State(s.cube,dx,dy,s.cost + 1, s.step + 1));
	}
      }
      s.cube = prev;
    }
  }
  return INF;
}


int main(){

  while(~scanf("%d %d",&W,&H)){
    if(W == 0 && H == 0) break;
    memset(visited,0x3f,sizeof(visited));
    int sx,sy;
    for(int y = 0; y < H; y++){
      scanf("%s",stage[y]);
      for(int x = 0; x < W; x++){
	if(stage[y][x] == '#'){
	  sy = y;
	  sx = x;
	}
      }
    }

    scanf("%s",order);
    int res = bfs(sx,sy);
    if(res >= INF){
      printf("unreachable\n");
    }
    else{
      printf("%d\n",res);
    }
  }
}
