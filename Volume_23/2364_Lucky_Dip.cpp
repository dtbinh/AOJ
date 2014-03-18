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
 
const static int tx[] = {+0,+1,+0,-1};
const static int ty[] = {-1,+0,+1,+0};
 
static const double EPS = 1e-12;

int W,H;
char stage[1001][1001];
bool visited[1001][1001];

class State{
public:
  int x;
  int y;
  int cost;
  int heuristic_cost;
  State(int _x,int _y,int _c,int _hc) : x(_x),y(_y),cost(_c),heuristic_cost(_hc){}

  bool operator <(const State& s) const{
    return cost+heuristic_cost < s.cost + s.heuristic_cost;
  }
  bool operator >(const State& s) const{
    return cost+heuristic_cost > s.cost + s.heuristic_cost;
  }
};

int heuristic(int sx,int sy,int gx,int gy){
  return abs(gx-sx) + abs(gy-sy);
}

void bfs(int gx,int gy){
  priority_queue<State,vector<State>,greater<State> > que;
  que.push(State(0,0,0,heuristic(0,0,gx,gy)));
  
  while(!que.empty()){
    State s = que.top();
    que.pop();
    int sx = s.x;
    int sy = s.y;
    if(visited[sy][sx]) continue;

    visited[sy][sx] = true;
    if(stage[sy][sx] == 't') break;
    for(int i=0;i<4;i++){
      int dx = sx + tx[i];
      int dy = sy + ty[i];
      if(dx < 0 || dy < 0 || dx >= W || dy >= H) continue;
      if(visited[dy][dx]) continue;
      if(stage[dy][dx] == '#') continue;
      que.push(State(dx,dy,s.cost+1,heuristic(dx,dy,gx,gy)));
    }
  }
}

void dfs(int sx,int sy){
  visited[sy][sx] = true;
  for(int i=0;i<4;i++){
    int dx = sx + tx[i];
    int dy = sy + ty[i];
    if(dx < 0 || dy < 0 || dx >= W || dy >= H) continue;
    if(visited[dy][dx]) continue;
    if(stage[dy][dx] == '#') continue;
    dfs(dx,dy);
  }
}

bool has_route(int time,const vector<P>& gates,
	       int gx,int gy){

  vector<P> skip;
  for(int i=0;i<time;i++){
    int x = gates[i].first;
    int y = gates[i].second;
    if(stage[y][x] == '.'){
      skip.push_back(gates[i]);
    }
    stage[y][x] = '.';
  }
  memset(visited,false,sizeof(visited));
  bfs(gx,gy);

  for(int i=0;i<time;i++){
    int x = gates[i].first;
    int y = gates[i].second;
    stage[y][x] = '#';
  }

  for(int i=0;i<skip.size();i++){
    int x = skip[i].first;
    int y = skip[i].second;
    stage[y][x] = '.';
  }
  return visited[gy][gx];
}

int main(){

  while(~scanf("%d %d",&W,&H)){

    int gx,gy;
    for(int y=0;y<H;y++){
      string line;
      cin >> line;
      for(int x=0;x<W;x++){
	stage[y][x] = line[x];
	if(line[x] == 't'){
	  gx = x;
	  gy = y;
	}
      }
    }

    vector<P> gates;
    int total_time;
    scanf("%d",&total_time);
    for(int time=0;time<total_time;time++){
      int x,y;
      scanf("%d %d",&x,&y);
      gates.push_back(P(x,y));
    }

    int min_time = 0;
    int max_time = gates.size();
    bool isok = false;
    for(int round=0;round<10;round++){
      int mid = (min_time + max_time) / 2;
      if(has_route(mid,gates,gx,gy)){
	max_time = mid;
	isok = true;
      }
      else{
	min_time = mid+1;
      }
    }

    printf("%d\n",isok ? max_time : -1);
  }
}
