#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdio>
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
 
static const double EPS = 1e-8;

static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};

int H,W;
char stage[20][20];
string ghost;
bool visited[20][20][20][20][10];
int gTime = 0;
int rx,ry;

void dfs(int sx,int sy,int gx,int gy,int time){
  int pattern_i = time % ghost.size();
  if(ghost[pattern_i] == '5'){
    //nothing to do
  }
  else if(ghost[pattern_i] == '8' && gy - 1 >= 0){
    gy--;
  }
  else if(ghost[pattern_i] == '6' && gx + 1 < W){
    gx++;
  }
  else if(ghost[pattern_i] == '4' && gx - 1 >= 0){
    gx--;
  }
  else if(ghost[pattern_i] == '2' && gy + 1 < H){
    gy++;
  }

  if(!visited[sx][sy][gx][gy][pattern_i]){
    visited[sx][sy][gx][gy][pattern_i] = true;
    if(sx == gx && sy == gy && gTime > time){
      gTime = time;
      rx = gx;
      ry = gy;
      return;
    }
    dfs(sx,sy,gx,gy,time+1);
  }
  for(int i = 0; i < 4; i++){
    int dx = tx[i] + sx;
    int dy = ty[i] + sy;
    if(dx < 0 || dx >= W || dy < 0 || dy >= H) continue;
    if(stage[dy][dx] == '#') continue;
    if(visited[dx][dy][gx][gy][pattern_i]) continue;

    visited[dx][dy][gx][gy][pattern_i] = true;
    if(dx == gx && dy == gy && gTime > time){
      gTime = time;
      rx = gx;
      ry = gy;
      return;
    }
    dfs(dx,dy,gx,gy,time+1);
  }
}

int main(){
  while(~scanf("%d %d",&H,&W)){
    if(H == 0 && W == 0) break;

    int sx,sy,gx,gy;
    memset(visited,false,sizeof(visited));
    gTime = INF;

    for(int y = 0; y < H; y++){
      char line[32];
      scanf("%s",line);
      for(int x = 0; x < W; x++){
	stage[y][x] = line[x];
	if(stage[y][x] == 'A'){
	  sx = x;
	  sy = y;
	}
	if(stage[y][x] == 'B'){
	  gx = x;
	  gy = y;
	}
      }
    }
    cin >> ghost;
    rx = -1;
    ry = -1;
    dfs(sx,sy,gx,gy,0);
    
    if(gTime == INF){
      printf("Impossible\n");
    }
    else{
      printf("%d %d %d\n",gTime + 1,ry,rx);
    }
  }
}
