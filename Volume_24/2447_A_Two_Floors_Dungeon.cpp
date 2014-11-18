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
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

int W,H;
char stage[51][51];
char switches[11][51][51];
int dp[1<<10][51][51][2];
int total_switches;

bool check_floor(int S,int dx,int dy,int current){
  if(stage[dy][dx] == '|') return true;

  int floor = 0;
  if('a' <= stage[dy][dx] && stage[dy][dx] <= 'z'
     || stage[dy][dx] == '_'
     || stage[dy][dx] == '&'
     || stage[dy][dx] == '%'){
    floor = 0;
  }
  else if('A' <= stage[dy][dx] && stage[dy][dx] <= 'Z'
     || stage[dy][dx] == '^'){
    floor = 1;
  }

  for(int switch_i = 0; switch_i < total_switches; switch_i++){
    if((S & (1<<switch_i)) && switches[switch_i][dy][dx] == '*'){
      floor++;
      floor %= 2;
    }
  }
  return (current == floor);
}

int alpha2idx(char alpha){
  if('A' <= alpha && alpha <= 'Z'){
    return alpha - 'A';
  }
  return alpha - 'a';
}

class State{
public:
  int S;
  int x;
  int y;
  int floor;
  int cost;
  State(int S,int x,int y,int floor,int cost) :
    S(S),x(x),y(y),floor(floor),cost(cost) {}
  bool operator<(const State& s) const {
    return cost < s.cost;
  }
  bool operator>(const State& s) const {
    return cost > s.cost;
  }
};

int bfs(int sx,int sy){
  priority_queue<State,vector<State>,greater<State> > que;
  que.push(State(0,sx,sy,0,0));

  while(!que.empty()){
    State s = que.top();
    que.pop();
    int S = s.S;
    int floor = s.floor;
    int cost = s.cost;

    for(int i = 0; i < 4; i++){
      int dx = s.x + tx[i];
      int dy = s.y + ty[i];
      if(dx < 0 || dx >= W || dy < 0 || dy >= H) continue;
      if(stage[dy][dx] == '#') continue;
      if(!check_floor(S,dx,dy,floor)) continue;

      if(dp[S][dx][dy][floor] > cost + 1){
	dp[S][dx][dy][floor] = cost + 1;
	que.push(State(S,dx,dy,floor,cost + 1));
      }

      if(isalpha(stage[dy][dx])){
	//use switch
	int switch_i = alpha2idx(stage[dy][dx]);
	int next_S = S ^ (1<<switch_i);
	int next_floor = floor;
	
	if(switches[switch_i][dy][dx] == '*'){
	  next_floor++;
	  next_floor %= 2;
	}
	
	if(dp[next_S][dx][dy][next_floor] > cost + 2){
	  dp[next_S][dx][dy][next_floor] = cost + 2;
	  que.push(State(next_S,dx,dy,next_floor,cost + 2));
	}
	
	//don't use switch
	if(dp[S][dx][dy][floor] > cost + 1){
	  dp[S][dx][dy][floor] = cost + 1;
	  que.push(State(S,dx,dy,floor,cost + 1));
	}
      }
      else{
	int next_floor = floor;
	
	if(stage[dy][dx] == '|'){
	  next_floor++;
	  next_floor %= 2;
	  if(dp[S][dx][dy][next_floor] > cost + 2){
	    dp[S][dx][dy][next_floor] = cost + 2;
	    que.push(State(S,dx,dy,next_floor,cost + 2));
	  }
	}
      }
    }
  }
}

int main(){
  while(~scanf("%d %d",&W,&H)){
    memset(dp,0x3f,sizeof(dp));
    int sx,sy;
    int gx,gy;
    for(int y = 0; y < H; y++){
      char line[64];
      scanf("%s",line);
      for(int x = 0; x < W; x++){
	stage[y][x] = line[x];
	if(stage[y][x] == '%'){
	  sx = x;
	  sy = y;
	}
	if(stage[y][x] == '&'){
	  gx = x;
	  gy = y;
	}
      }
    }
    scanf("%d",&total_switches);
    for(int switch_i = 0; switch_i < total_switches; switch_i++){
      for(int y = 0; y < H; y++){
	char line[64];
	scanf("%s",line);
	for(int x = 0; x < W; x++){
	  switches[switch_i][y][x] = line[x];
	}
      }
    }
    bfs(sx,sy);
    int res = INF;
    for(int S = 0; S < (1<<total_switches); S++){
      for(int floor = 0; floor < 2; floor++){
	res = min(dp[S][gx][gy][floor],res);
      }
    }
    printf("%d\n",res >= INF ? -1 : res);
  }
}
