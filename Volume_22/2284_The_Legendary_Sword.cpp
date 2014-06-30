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
 
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

class State{
public:
  int x;
  int y;
  int cost;
  int level;
  State(int _x,int _y,int _c,int _l) : x(_x),y(_y),cost(_c),level(_l) {}
  bool operator<(const State& s) const{
    return cost < s.cost;
  }
  bool operator>(const State& s) const{
    return cost > s.cost;
  }
};

int pos2idx(int x,int y,int W){
  return W * y + x;
}

int main(){
  int W,H;
  while(~scanf("%d %d",&W,&H)){
    if(W == 0 && H == 0) break;

    int sx,sy;
    int gx,gy;
    string stage[101][101];
    int levels[101];
    int max_level = 0;
    memset(levels,0,sizeof(levels));

    for(int y=0;y<H;y++){
      for(int x=0;x<W;x++){
	char tmp[101];
	scanf("%s",tmp);
	stage[y][x] = tmp;
	if(stage[y][x] == "S"){
	  sx = x;
	  sy = y;
	}
	else if(stage[y][x] == "G"){
	  gx = x;
	  gy = y;
	}
	else if(stage[y][x] != "."){
	  stringstream ss;
	  ss << stage[y][x];
	  int level = 0;
	  ss >> level;
	  levels[y * W + x] = level;
	  max_level = max(level,max_level);
	}
      }
    }
    
    priority_queue<State,vector<State>,greater<State> > que;

    que.push(State(sx,sy,0,1));
    int dp[105][101];//dp[level][pos]
    memset(dp,0x3f,sizeof(dp));

    dp[1][pos2idx(sx,sy,W)] = 0;

    int res = 0;
    while(!que.empty()){
      State s = que.top();
      que.pop();
      for(int i=0;i<4;i++){
	int dx = s.x + tx[i];
	int dy = s.y + ty[i];
	if(dx < 0 || dx >= W || dy < 0 || dy >= H) continue;
	int idx = pos2idx(dx,dy,W);
	if(levels[idx] > s.level) continue;

	if(levels[idx] == s.level){
	  if(dp[s.level+1][dy * W + dx] <= s.cost + 1) continue;
	  dp[s.level+1][dy * W + dx] = s.cost + 1;
	  que.push(State(dx,dy,s.cost + 1,s.level+1));
	}
	else{
	  if(dp[s.level][dy * W + dx] <= s.cost + 1) continue;
	  dp[s.level][dy * W + dx] = s.cost + 1;
	  que.push(State(dx,dy,s.cost + 1,s.level));
	}
      }
    }
  found:;
    printf("%d\n",dp[max_level+1][gy * W + gx]);
  }
}
