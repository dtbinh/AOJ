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
  int forward_x;
  int forward_y;
  int forward_dir;
  int backward_x;
  int backward_y;
  int backward_dir;
  State(int fx,int fy,int fd,int bx,int by,int bd)
    : forward_x(fx),forward_y(fy),forward_dir(fd),
      backward_x(bx),backward_y(by),backward_dir(bd) {}
};

bool visited[17][65][4][17][65][4];
char stage[20][70];

bool two_doll_bfs(int sx,int sy,int sdir,int gx,int gy,int gdir){
  queue<State> que;
  memset(visited,false,sizeof(visited));

  for(int bdir = 0; bdir < 4; bdir++){
    que.push(State(sx,sy,sdir,sx,sy,bdir));
  }
  
  while(!que.empty()){
    State s = que.front();
    que.pop();
    
    int tmp_forward_dx = s.forward_x;
    int tmp_forward_dy = s.forward_y;
    while(stage[tmp_forward_dy][tmp_forward_dx] != '#'){
      tmp_forward_dx += tx[s.forward_dir];
      tmp_forward_dy += ty[s.forward_dir];
    }
    tmp_forward_dx -= tx[s.forward_dir];
    tmp_forward_dy -= ty[s.forward_dir];
    
    int forward_dx = tmp_forward_dx;
    int forward_dy = tmp_forward_dy;
    
    int backward_dx = s.backward_x;
    int backward_dy = s.backward_y;
    
    while(stage[backward_dy][backward_dx] != '#'){

      if(visited[forward_dy][forward_dx][s.forward_dir][backward_dy][backward_dx][s.backward_dir]){
	backward_dx += tx[(s.backward_dir + 2) % 4];
	backward_dy += ty[(s.backward_dir + 2) % 4];
	continue;
      }

      const int lr[] = {3,1}; // {left,right}
      for(int i = 0; i < 2; i++){
	if(stage[ty[(s.backward_dir + lr[i]) % 4] + backward_dy][tx[(s.backward_dir + lr[i]) % 4] + backward_dx] != '#') continue;
	visited[forward_dy][forward_dx][s.forward_dir][backward_dy][backward_dx][s.backward_dir] = true;
	que.push(State(forward_dx,forward_dy,(s.forward_dir + lr[i]) % 4,
		       backward_dx,backward_dy,(s.backward_dir + lr[i]) % 4));
      }
      backward_dx += tx[(s.backward_dir + 2) % 4];
      backward_dy += ty[(s.backward_dir + 2) % 4];
    }
  }
  
  bool flag = false;
  for(int i = 0; i < 4; i++){
    if(visited[gy][gx][i][gy][gx][gdir]){
      flag = true;
      break;
    }
  }
  
  return flag;
}

bool one_doll_bfs(int sx,int sy,int sdir,int gx,int gy,int gdir){
  queue<State> que;
  memset(visited,false,sizeof(visited));

  const int backward_dx = sx;
  const int backward_dy = sy;
  const int backward_dir = 0;

  que.push(State(sx,sy,sdir,backward_dx,backward_dy,backward_dir));
  
  while(!que.empty()){
    State s = que.front();
    que.pop();
    
    int tmp_forward_dx = s.forward_x;
    int tmp_forward_dy = s.forward_y;

    while(stage[tmp_forward_dy][tmp_forward_dx] != '#'){
      tmp_forward_dx += tx[s.forward_dir];
      tmp_forward_dy += ty[s.forward_dir];
    }
    tmp_forward_dx -= tx[s.forward_dir];
    tmp_forward_dy -= ty[s.forward_dir];
    
    int forward_dx = tmp_forward_dx;
    int forward_dy = tmp_forward_dy;
    
    if(visited[forward_dy][forward_dx][s.forward_dir][backward_dy][backward_dx][backward_dir]) continue;
    visited[forward_dy][forward_dx][s.forward_dir][backward_dy][backward_dx][backward_dir] = true;

    const int lr[] = {3,1}; // {left,right}
    for(int i = 0; i < 2; i++){
      que.push(State(forward_dx,forward_dy,(s.forward_dir + lr[i]) % 4,
		     backward_dx,backward_dy,backward_dir));
    }
  }
  
  bool flag = false;
  for(int i = 0; i < 4; i++){
    if(visited[gy][gx][i][backward_dy][backward_dx][backward_dir]){
      flag = true;
      break;
    }
  }
  
  return flag;
}


int main(){
  int W,H;
  while(~scanf("%d %d",&W,&H)){
    if(W == 0 && H == 0) break;
    memset(stage,'#',sizeof(stage));

    int sx,sy,sdir;
    int gx,gy,gdir;

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

    for(int i = 0; i < 4; i++){
      if(stage[(sy + ty[i]) % 4][(sx + tx[i]) % 4] == '.'){
	sdir = i;
      }
      if(stage[(gy + ty[i]) % 4][(gx + tx[i]) % 4] == '.'){
	gdir = i;
      }
    }


    if(one_doll_bfs(sx,sy,sdir,gx,gy,gdir)){
      if(two_doll_bfs(sx,sy,sdir,gx,gy,gdir)){
    	printf("He can accomplish his mission.\n");
      }
      else{
    	printf("He cannot return to the kitchen.\n");
      }
    }
    else{
      printf("He cannot bring tea to his master.\n");
    }
  }
}
