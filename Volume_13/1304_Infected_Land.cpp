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
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;
 
const static int tx[] = {0,1,1,1,0,-1,-1,-1};
const static int ty[] = {-1,-1,0,1,1,1,0,-1};

class State{
public:
  int x;
  int y;
  int stage;
  int move_count;
  State(int _x,int _y,int _s, int _m) : x(_x),y(_y),stage(_s),move_count(_m){}
  State() : x(0),y(0),stage(0),move_count(0){}

  bool operator<(const State& s) const{
    return move_count < s.move_count;
  }
  bool operator>(const State& s) const{
    return move_count > s.move_count;
  }
};

int update(int stage,int vx,int vy,int N){
  int next = stage;
  for(int y=0;y<N;y++){
    for(int x=0;x<N;x++){
      if(x == vx && y == vy) continue;
      int count = 0;
      for(int i=0;i<8;i++){
	int dx = x + tx[i];
	int dy = y + ty[i];
	if(dx < 0 || dy < 0
	   || dx >= N || dy >=N) continue;
	if(stage & (1 << (dy*N+dx))) count++;
	if(dx == vx && dy == vy) count++;
      }
      if((stage & (1<<(y*N+x)))
	 && (count == 3 || count == 2)){
	next |= (1<<(y*N+x));
      }
      else if(!(stage & (1<<(y*N+x)))
	      && count == 3){
	next |= (1<<(y*N+x));
      }
      else{
	next &= ~(1<<(y*N+x));
      }
    }
  }
  return next;
}

void print_stage(int stage,int N){
  for(int y=0;y<N;y++){
    for(int x=0;x<N;x++){
      printf("%c",(stage & (1<<(y*N+x)) ? '#' : '.'));
    }
    printf("\n");
  }
  printf("\n");
}

int main(){
  int N;
  while(~scanf("%d",&N)){
    if(N==0) break;

    int stage = 0;
    int sx,sy;
    for(int y=0;y<N;y++){
      char buf[128];
      scanf("%s",buf);
      for(int x=0;x<N;x++){
	if(buf[x] == '@'){
	  sx = x;
	  sy = y;
	}
	if(buf[x] == '#'){
	  stage |= (1 << (y*N+x));
	}
      }
    }
    priority_queue<State,vector<State>,greater<State> > que;
    //x,y,visited,stage,move_count
    que.push(State(sx,sy,stage,0));
    
    map<int,int> move_count[25];
    move_count[sy*N+sx][stage] = 0;
    int res = -1;
    if(stage == 0){
      res = 0;
      goto found;
    }

    while(!que.empty()){
      State s = que.top();
      que.pop();
      for(int i=0;i<8;i++){
	int dx = s.x + tx[i];
	int dy = s.y + ty[i];
	if(dx < 0 || dy < 0
	   || dx >= N || dy >=N) continue;
	if(s.stage & (1<<(dy*N+dx))) continue;

	// print_stage(s.stage,N);
	int next_stage = update(s.stage,dx,dy,N);

	map<int,int>::iterator it = move_count[dy*N+dx].find(next_stage);
	if(it != move_count[dy*N+dx].end()) continue;
	
	move_count[dy*N+dx][next_stage] = s.move_count + 1;
	if(next_stage == 0){
	  res = s.move_count + 1;
	  goto found;
	}

	que.push(State(dx,dy,next_stage,s.move_count+1));
      }
    }
  found:;
    printf("%d\n",res);
  }
}
