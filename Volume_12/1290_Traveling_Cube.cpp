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
 
int tx[] = {0,1,0,-1};//URDL
int ty[] = {-1,0,1,0};
 
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
    surface[SOUTH] = CYAN;
    surface[BOTTOM] = GREEN;
    surface[NORTH] = MAGENTA;
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
      int next[6];
      memcpy(next,surface,sizeof(int)*6);
      next[SOUTH] = surface[BOTTOM];
      next[BOTTOM] = surface[NORTH];
      next[NORTH] = surface[TOP];
      next[TOP] = surface[SOUTH];
      memcpy(surface,next,sizeof(int)*6);
    }
  }
  void yaw(int num){
    //WEST,SOUTH,EAST,NORTH
    for(int i=0;i<num;i++){
      int next[6];
      memcpy(next,surface,sizeof(int)*6);
      next[WEST] = surface[SOUTH];
      next[SOUTH] = surface[EAST];
      next[EAST] = surface[NORTH];
      next[NORTH] = surface[WEST];
      memcpy(surface,next,sizeof(int)*6);
    }
  }
  void roll(int num){
    //TOP,WEST,BOTTOM,EAST
    for(int i=0;i<num;i++){
      int next[6];
      memcpy(next,surface,sizeof(int)*6);
      next[TOP] = surface[WEST];
      next[WEST] = surface[BOTTOM];
      next[BOTTOM] = surface[EAST];
      next[EAST] = surface[TOP];
      memcpy(surface,next,sizeof(int)*6);
    }
  }
  char get_bottom() const{
    const char dict[] = {'r','c','g','m','b','y'};
    return dict[surface[BOTTOM]];
  }
};

char stage[31][31];
bool visited[31][31];
char order[8];
int H,W;

int dfs(Cube& cube,int sx,int sy,int step,int cost){
  if(step == 6){
    return cost;
  }

  int res = INF;
  for(int i = 0; i < 4; i++){
    int dx = tx[i] + sx;
    int dy = ty[i] + sy;
    if(dx >= W || dy >= H || dx < 0 || dy < 0) continue;
    if(stage[dy][dx] == 'k') continue;
    if(visited[dy][dx]) continue;

    Cube prev = cube;
    if(i == 0){
      cube.pitch(1);
    }
    else if(i == 1){
      cube.roll(1);
    }
    else if(i == 2){
      cube.pitch(3);
    }
    else if(i == 3){
      cube.roll(3);
    }

    if(stage[dy][dx] == 'w'){
      visited[dy][dx] = true;
      res = min(dfs(cube,dx,dy,step,cost + 1),res);
      visited[dy][dx] = false;
      cube = prev;
    }
    else if(cube.get_bottom() == stage[dy][dx]){
      visited[dy][dx] = true;
      res = min(dfs(cube,dx,dy,step + 1,cost + 1),res);
      visited[dy][dx] = false;
      cube = prev;
    }
  }
  return res;
}

int main(){

  while(~scanf("%d %d",&W,&H)){
    if(W == 0 && H == 0) break;
    memset(visited,false,sizeof(visited));
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
    visited[sy][sx] = true;
    scanf("%s",order);
    Cube cube;
    cout << dfs(cube,sx,sy,0,0) << endl;
  }
}
