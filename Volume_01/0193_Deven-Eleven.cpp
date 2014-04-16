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
  
static const double EPS = 1e-8;
  
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};


pair<int,int> hanicam(int x,int y,int angle){
  if(y % 2 == 0){
    switch(angle){
    case 0:
      //upper left
      return pair<int,int>(x,y-1);
      break;
    case 1:
      //upper right
      return pair<int,int>(x+1,y-1);
      break;
    case 2:
      //right
      return pair<int,int>(x+1,y);
      break;
    case 3:
      //lower right
      return pair<int,int>(x+1,y+1);
      break;
    case 4:
      //lower left
      return pair<int,int>(x-1,y+1);
      break;
    case 5:
      //left
      return pair<int,int>(x-1,y);
      break;
    default:
      break;
    }
  }
  else if(y %2 != 0){
    switch(angle){
    case 0:
      //upper left
      return pair<int,int>(x,y-1);
      break;
    case 1:
      //upper right
      return pair<int,int>(x+1,y-1);
      break;
    case 2:
      //right
      return pair<int,int>(x+1,y);
      break;
    case 3:
      //lower right
      return pair<int,int>(x+1,y+1);
      break;
    case 4:
      //lower left
      return pair<int,int>(x,y+1);
      break;
    case 5:
      //left
      return pair<int,int>(x-1,y);
      break;
    default:
      break;
    }
  }
}

class State{
public:
  int x,y;
  int cost;
  int id;
  State(int _x,int _y,int _c,int _i) : x(_x),y(_y),cost(_c), id(_i) {}
  bool operator<(const State& s) const{
    return cost < s.cost;
  }
  bool operator>(const State& s) const{
    return cost > s.cost;
  }
};

int min_cost[101][101];
int id_list[101][101];
int W,H;

void bfs(int sx,int sy,int id){
  priority_queue<State,vector<State>,greater<State> > que;
  que.push(State(sx,sy,0,id));

  while(!que.empty()){
    State s = que.top();
    que.pop();
    min_cost[s.x][s.y] = s.cost;

    for(int angle=0;angle < 6;angle++){
      pair<int,int> next = hanicam(sx,sy,angle);
      int dx = next.first;
      int dy = next.second;
      if(dx < 0 || dx >= W || dy < 0 || dy >= H) continue;
      if(min_cost[dx][dy] <= s.cost + 1) continue;
      min_cost[dx][dy] = s.cost + 1;
      id_list[dx][dy] = s.id;

      que.push(State(dx,dy,s.cost + 1,s.id));
    }
  }
}

int candidate_bfs(int sx,int sy){
  int candidate_cost[101][101];
  memset(candidate_cost,0x3f,sizeof(candidate_cost));

  priority_queue<State,vector<State>,greater<State> > que;
  
  que.push(State(sx,sy,0,0));

  while(!que.empty()){
    State s = que.top();
    que.pop();
    candidate_cost[s.x][s.y] = s.cost;

    for(int angle=0;angle < 6;angle++){
      pair<int,int> next = hanicam(sx,sy,angle);
      int dx = next.first;
      int dy = next.second;
      if(dx < 0 || dx >= 100 || dy < 0 || dy >= 100) continue;
      if(min_cost[dx][dy] <= s.cost + 1) continue;
      if(candidate_cost[dx][dy] <= s.cost + 1) continue;

      que.push(State(dx,dy,s.cost + 1,s.id));
    }
  }

  int res = 0;
  for(int y=0;y<H;y++){
    for(int x=0;x<W;x++){
      if(candidate_cost[x][y] != INF){
	res++;
      }
    }
  }
  return res;
}

int main(){

  while(~scanf("%d %d",&W,&H)){
    if(W == 0 && H == 0) break;
    memset(min_cost,0x3f,sizeof(min_cost));
    memset(id_list,-1,sizeof(id_list));

    map<pair<int,int>,bool> stage;
    int total_existing_stores;
    scanf("%d",&total_existing_stores);
    for(int store_idx = 0; store_idx < total_existing_stores; store_idx++){
      int x,y;
      scanf("%d %d",&x,&y);
      x--;
      y--;
      bfs(x,y,store_idx);
    }

    int total_new_stores;

    int res = 0;
    scanf("%d",&total_new_stores);
    for(int store_idx = 0; store_idx < total_new_stores; store_idx++){
      int sx,sy;
      scanf("%d %d",&sx,&sy);

      sx--;
      sy--;
      res = max(res,candidate_bfs(sx,sy));
    }
    printf("%d\n",res);
  }
}
