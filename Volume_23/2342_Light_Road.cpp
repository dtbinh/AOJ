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
  
static const int tx[] = {+0,+1,+0,-1};
static const int ty[] = {-1,+0,+1,+0};

class State{
public:
  int x;
  int y;
  int prev_dir;
  int P_reflect_count; //2->1, 1->2, 0->3, 3->0
  int Q_reflect_count;
  map<int,bool> P_mirror;//2->3, 3->2, 1->0, 0->1
  map<int,bool> Q_mirror;//2->3, 3->2, 1->0, 0->1
  State() : x(0),y(0),P_reflect_count(0),Q_reflect_count(0),prev_dir(-1) {}
  State(int _x,int _y,int _p,int _q,int _d,
	map<int,bool>& _P_mirror,map<int,bool>& _Q_mirror) : x(_x),y(_y),P_reflect_count(_p),Q_reflect_count(_q),prev_dir(_d) {
    P_mirror = _P_mirror;
    Q_mirror = _Q_mirror;
  }

  State(int _x,int _y,int _p,int _q,int _d) : x(_x),y(_y),P_reflect_count(_p),Q_reflect_count(_q),prev_dir(_d) { }
  bool operator<(const State& s) const{
    return ((P_reflect_count + Q_reflect_count)
	    < (s.P_reflect_count + s.Q_reflect_count));
  }
  bool operator>(const State& s) const{
    return ((P_reflect_count + Q_reflect_count)
	    > (s.P_reflect_count + s.Q_reflect_count));
  }
};

bool check(int x,int y,int gx,int gy,int dir,
	   map<int,bool>& P_mirror,map<int,bool>& Q_mirror,
	   char stage[100][100],int W,int H){
  if(x == gx && y == gy) return true;

  bool res = false;
  int dx = x + tx[dir];
  int dy = y + ty[dir];
  if(dx < 0 || dy < 0 || dx >= W || dy >= H) return false;
  if(stage[dy][dx] == '#') return false;

  map<int,bool>::iterator it;
  int next_dir = dir;
  if((it = P_mirror.find(dy*W+dx)) != P_mirror.end()){
    if(dir == 0) next_dir = 3;
    if(dir == 1) next_dir = 2;
    if(dir == 2) next_dir = 1;
    if(dir == 3) next_dir = 0;
  }

  if((it = Q_mirror.find(dy*W+dx)) != Q_mirror.end()){
    if(dir == 0) next_dir = 1;
    if(dir == 1) next_dir = 0;
    if(dir == 2) next_dir = 3;
    if(dir == 3) next_dir = 2;
  }

  res |= check(dx,dy,gx,gy,next_dir,P_mirror,Q_mirror,stage,W,H);
     
  return res;
}

int main(){
  int H,W,A;
  while(~scanf("%d %d %d",&H,&W,&A)){
    char stage[100][100];

    int sx,sy;
    int gx,gy;
    for(int y=0;y<H;y++){
      char line[101];
      scanf("%s",line);
      for(int x=0;x<W;x++){
	stage[y][x] = line[x];
	if(line[x] == 'S'){
	  sx = x;
	  sy = y;
	}
	if(line[x] == 'G'){
	  gx = x;
	  gy = y;
	}
      }
    }

    priority_queue<State,vector<State>,greater<State> > que;
    que.push(State(sx,sy,0,0,4));

    //P 2->1, 1->2, 0->3, 3->0
    //Q 2->3, 3->2, 1->0, 0->1
    int P_bit1=0; P_bit1 |= (1<<1); P_bit1 |= (1<<2);
    int P_bit2=0; P_bit2 |= (1<<0); P_bit2 |= (1<<3);
    int Q_bit1=0; Q_bit1 |= (1<<2); Q_bit1 |= (1<<3);
    int Q_bit2=0; Q_bit2 |= (1<<0); Q_bit2 |= (1<<1);

    bool dp[100][100][10];
    memset(dp,false,sizeof(dp));
    
    int use_mirrors = INF;
    while(!que.empty()){
      State s = que.top();
      que.pop();

      if(dp[s.x][s.y][s.prev_dir]) continue;
      dp[s.x][s.y][s.prev_dir] = true;

      // printf("x:%d y:%d prev:%d\n",s.x,s.y,s.prev_dir);
      if(s.x == gx && s.y == gy){
	if(s.P_reflect_count > A || s.Q_reflect_count > A) continue;
	if(!check(s.x,s.y,sx,sy,(s.prev_dir+2) % 4,
		  s.P_mirror,s.Q_mirror,stage,W,H)) continue;

	use_mirrors = s.P_reflect_count + s.Q_reflect_count;
	break;
      }

      for(int i=0;i<4;i++){
	if(s.prev_dir == 4 && i != 2) continue;
	int dx = s.x + tx[i];
	int dy = s.y + ty[i];

	if(dx < 0 || dy < 0 || dx >= W || dy >= H) continue;
	if(stage[dy][dx] == '#') continue;

	if(stage[s.y][s.x] == 'S'){
	  if(s.prev_dir != 4 && s.prev_dir != i){
	    continue;
	  }
	}

	//P 2->1, 1->2, 0->3, 3->0
	//Q 2->3, 3->2, 1->0, 0->1
	int dir_history = 0;
	dir_history |= (1<<i);
	if(s.prev_dir != -1){
	  dir_history |= (1<<s.prev_dir);
	}
	int next_P = s.P_reflect_count;
	int next_Q = s.Q_reflect_count;

	map<int,bool> P_mirror = s.P_mirror;
	map<int,bool> Q_mirror = s.Q_mirror;

	if(P_bit1 == dir_history
	   || P_bit2 == dir_history){
	  next_P++;
	  P_mirror[dy*W+dx] = true;
	}
	if(Q_bit1 == dir_history
	   || Q_bit2 == dir_history){
	  next_Q++;
	  Q_mirror[dy*W+dx] = true;
	}
	if(next_P > A || next_Q > A) continue;
	if(s.prev_dir == (i + 2) % 4) continue;
	que.push(State(dx,dy,next_P,next_Q,i,P_mirror,Q_mirror));
      }
    }
    printf("%d\n",use_mirrors >= INF ? -1 : use_mirrors);
  }
}
