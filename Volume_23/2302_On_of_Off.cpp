#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
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
 
static const double EPS = 1e-8;

class State {
public:
  int _x;
  int _y;
  int _cost;
  State(int x,int y,int cost) ; _x(x),_y(y),_cost(cost) {}
  bool operator<(const State& s) const{
    return _cost < s._cost;
  }
  bool operator>(const State& s) const{
    return _cost > s._cost;
  }
};

int main(){
  int H,W,task_rooms;
  while(~scanf("%d %d %d",&H,&W,&task_rooms)){
    int consumption_per_unit[51][51];
    int turn_off_cost[51][51];
    int turn_on_cost[51][51];

    char stage[51][51];
    for(int y = 0; y < H; y++){
      char buf[51];
      scanf("%s",buf);
      for(int x = 0; x < W; x++){
	stage[y][x] = buf[x];
      }
    }
    
    for(int y = 0; y < H; y++){
      for(int x = 0; x < W; x++){
	scanf("%d",&consumption_per_unit[y][x]);
      }
    }

    for(int y = 0; y < H; y++){
      for(int x = 0; x < W; x++){
	scanf("%d",&turn_off_cost[y][x]);
      }
    }

    for(int y = 0; y < H; y++){
      for(int x = 0; x < W; x++){
	scanf("%d",&turn_on_cost[y][x]);
      }
    }

    vector<P> points;
    for(int task_i = 0; task_i < task_rooms; task_i++){
      int y,x;
      scanf("%d %d",&y,&x);
      points.push_back(P(x,y));
    }

    for(int task_i = 0; task_i + 1 < task_rooms; task_i++){
      int sx = points[task_i].first;
      int sy = points[task_i].second;

      int gx = points[task_i+1].first;
      int gy = points[task_i+1].second;
      
      priority_queue<State,vector<State>,greater<State> > que;
      que.push(State(sx,sy,0));
      while(!que.empty()){
	State s = que.top();
	
	for(int i=0;i<4;i++){
	  int dx = s.x + tx[i];
	  int dy = s.y + ty[i];
	  if(dx < 0 || dx >= W || dy < 0 || dy >= H) continue;
	     
	     
	}
      }
    }
  }
}
