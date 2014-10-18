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

class State {
public:
  int _sx,_sy,_gx,_gy,_time;
  State(int sx,int sy,int gx,int gy,int time) : 
    _sx(sx),_sy(sy),_gx(gx),_gy(gy),_time(time) {}
  bool operator<(const State &s) const {
    return _time < s._time;
  }
  bool operator>(const State &s) const {
    return _time > s._time;
  }
};

void bfs(int sx,int sy,int gx,int gy){
  State init(sx,sy,gx,gy,0);
  
  priority_queue<State,vector<State>,greater<State> > que;
  que.push(init);

  while(!que.empty()){
    State s = que.top();
    que.pop();

    int pattern_i = s._time % ghost.size();
    if(ghost[pattern_i] == '5'){
      //nothing to do
    }
    else if(ghost[pattern_i] == '8' && s._gy - 1 >= 0){
      s._gy--;
    }
    else if(ghost[pattern_i] == '6' && s._gx + 1 < W){
      s._gx++;
    }
    else if(ghost[pattern_i] == '4' && s._gx - 1 >= 0){
      s._gx--;
    }
    else if(ghost[pattern_i] == '2' && s._gy + 1 < H){
      s._gy++;
    }

    if(!visited[s._sx][s._sy][s._gx][s._gy][pattern_i]){
      visited[s._sx][s._sy][s._gx][s._gy][pattern_i] = true;
      if(s._sx == s._gx && s._sy == s._gy && gTime > s._time){
	gTime = s._time;
	rx = s._gx;
	ry = s._gy;
	return;
      }
      que.push(State(sx,sy,s._gx,s._gy,s._time+1));
    }
    for(int i = 0; i < 4; i++){
      int dx = tx[i] + s._sx;
      int dy = ty[i] + s._sy;
      if(dx < 0 || dx >= W || dy < 0 || dy >= H) continue;
	 if(stage[dy][dx] == '#') continue;
	 if(visited[dx][dy][s._gx][s._gy][pattern_i]) continue;
	 
	 visited[dx][dy][s._gx][s._gy][pattern_i] = true;
	 if(dx == s._gx && dy == s._gy && gTime > s._time){
	   gTime = s._time;
	   rx = s._gx;
	   ry = s._gy;
	   return;
	 }
	 que.push(State(dx,dy,s._gx,s._gy,s._time+1));
    }
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
    bfs(sx,sy,gx,gy);
    
    if(gTime == INF){
      printf("impossible\n");
    }
    else{
      printf("%d %d %d\n",gTime + 1,ry,rx);
    }
  }
}
