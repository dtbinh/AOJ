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

int main(){
  int W,H;
  while(~scanf("%d %d",&W,&H)){
    if(W == 0 && H == 0) break;
    char stage[20][70];
    int sx,sy,sdir;
    int gx,gy;
    memset(visited,false,sizeof(visited));
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
	break;
      }
    }

    queue<State> que;
    que.push(State(sx,sy,sdir,sx,sy,(sdir + 2) % 4));

    while(!que.empty()){
      State s = que.front();
      que.pop();

      printf("f1:%d %d %d\n",s.forward_x,s.forward_y,s.forward_dir);
      printf("b1:%d %d %d\n",s.backward_x,s.backward_y,s.backward_dir);

      int tmp_forward_dx = s.forward_x;
      int tmp_forward_dy = s.forward_y;
      while(true){
	tmp_forward_dx += tx[s.forward_dir];
	tmp_forward_dy += ty[s.forward_dir];
	if(stage[tmp_forward_dy][tmp_forward_dx] == '#'){
	  break;
	}
      }
      tmp_forward_dx -= tx[s.forward_dir];
      tmp_forward_dy -= ty[s.forward_dir];

      int tmp_backward_dx = s.backward_x;
      int tmp_backward_dy = s.backward_y;
      while(true){
	tmp_backward_dx += tx[(s.backward_dir + 2) % 4];
	tmp_backward_dy += ty[(s.backward_dir + 2) % 4];
	if(stage[tmp_backward_dy][tmp_backward_dx] == '#'){
	  break;
	}
      }
      tmp_backward_dx -= tx[(s.backward_dir + 2) % 4];
      tmp_backward_dy -= ty[(s.backward_dir + 2) % 4];

      printf("f2:%d %d %d\n",tmp_forward_dx,tmp_forward_dy,s.forward_dir);
      printf("b2:%d %d %d\n",tmp_backward_dx,tmp_backward_dy,s.backward_dir);

      if(tmp_forward_dx == gx && tmp_forward_dy == gy
	 && tmp_backward_dx == gx && tmp_backward_dy == gy){
	cout << "YES" << endl;
	break;
      }

      const int lr[] = {3,1}; // {left,right}
      for(int i = 0; i < 2; i++){
	int forward_dx = tx[(s.forward_dir + lr[i]) % 4] + tmp_forward_dx;
	int forward_dy = ty[(s.forward_dir + lr[i]) % 4] + tmp_forward_dy;

	int backward_dx = tx[((s.backward_dir + lr[i]) % 4 + 2) % 4] + tmp_backward_dx;
	int backward_dy = ty[((s.backward_dir + lr[i]) % 4 + 2) % 4] + tmp_backward_dy;

	if(forward_dy >= H || forward_dx >= W || forward_dy < 0 || forward_dx < 0) continue;
	if(backward_dy >= H || backward_dx >= W || backward_dy < 0 || backward_dx < 0) continue;
	
	if(stage[forward_dy][forward_dx] == '#') continue;
	if(stage[backward_dy][backward_dx] == '#') continue;
	if(visited[forward_dy][forward_dx][(s.forward_dir + lr[i]) % 4][backward_dy][backward_dx][(s.backward_dir + lr[i]) % 4]) continue;

	visited[forward_dy][forward_dx][(s.forward_dir + lr[i]) % 4][backward_dy][backward_dx][(s.backward_dir + lr[i]) % 4] = true;

	que.push(State(forward_dx,forward_dy,(s.forward_dir + lr[i]) % 4,
		       backward_dx,backward_dy,(s.backward_dir + lr[i]) % 4));
      }
    }

    // if(flag == (1<<2) - 1){
    //   printf("He can accomplish his mission.\n");
    // }
    // else if(flag == (1<<0)){
    //   printf("He cannot return to the kitchen.\n");
    // }
    // else{
    //   printf("He cannot bring tea to his master.\n");
    // }
    cout << endl;
  }
}
