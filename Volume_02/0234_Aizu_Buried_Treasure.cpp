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
  
static const int tx[] = {+1,+0,-1};
static const int ty[] = {+0,+1,+0};

class State {
public:
  int x,y;
  int volume;
  int cost;

  State(int _x,int _y,int _v,int _c) :
    x(_x),y(_y),volume(_v),cost(_c) {}
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
    int upper_cost;
    int capacity;
    int initial_volume;
    scanf("%d %d %d",&upper_cost,&capacity,&initial_volume);

    int stage[11][11];
    for(int y=0; y < H; y++){
      for(int x=0; x < W; x++){
	scanf("%d",&stage[y][x]);
      }
    }

    priority_queue<State,vector<State>,greater<State> > que;
    que.push(State(initial_volume,0));
    
    while(!que.empty()){
      State s = que.top();
      int x = s.x;
      int y = s.y;

      que.pop();
      for(int i = 0; i < 3; i++){
	int dx = tx[i] + x;
	int dy = ty[i] + y;

	int next_cost = s.cost;
	int next_volume = s.volume - 1;
	if(next_volume <= 0) continue;
	
	if(stage[dy][dx] < 0){
	  next_cost += -stage[dy][dx];
	}
	else{
	  next_volume += stage[dy][dx];
	  if(next_volume > capacity) next_volume = capacity;
	}

	if(next_cost > upper_cost) continue;

	que.push(State(dx,dy,next_volume,next_cost));
      }
    }
  }
}
