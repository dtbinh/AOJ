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
 
const static int tx[] = {+0,+1,+0,-1};
const static int ty[] = {-1,+0,+1,+0};
 
static const double EPS = 1e-8;

int W,H;
bool visited[51][51];
char stage[51][51];
vector<P> dfs(int sx,int sy,int gx,int gy,
	      vector<P>& route){

  vector<P> res;
  for(int i=0;i<4;i++){
    int dx = sx + tx[i];
    int dy = sy + ty[i];
    if(dx < 0 || dx >= W || dy < 0 || dy >= H) continue;
    if(visited[dy][dx]) continue;
    if(stage[dy][dx] == '#') continue;

    if(dx == gx && dy == gy){
      route.push_back(P(dx,dy));
      res = route;
      return res;
    }

    visited[dy][dx] = true;
    route.push_back(P(dx,dy));

    vector<P> tmp = dfs(dx,dy,gx,gy,route);
    if(tmp.size() > 0){
      res = tmp;
    }

    visited[dy][dx] = false;
    route.pop_back();
  }

  return res;
}

int main(){
  int task_rooms;
  while(~scanf("%d %d %d",&H,&W,&task_rooms)){
    int consumption_per_unit[51][51];
    int turn_off_cost[51][51];
    int turn_on_cost[51][51];


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


    int latest_time = 0;
    int prev_x = -1;
    int prev_y = -1;

    vector<int> move_log[51][51];
    for(int task_i = 0; task_i + 1 < task_rooms; task_i++){
      int sx = points[task_i].first;
      int sy = points[task_i].second;

      int gx = points[task_i+1].first;
      int gy = points[task_i+1].second;

      memset(visited,false,sizeof(visited));
      visited[sy][sx] = true;
      vector<P> route;
      route.push_back(P(sx,sy));
      route = dfs(sx,sy,gx,gy,route);

      for(int i=0; i< route.size();i++){
	int x = route[i].first;
	int y = route[i].second;

	if(x == prev_x && y == prev_y) continue;
	
	move_log[y][x].push_back(latest_time);
	latest_time++;

	prev_x = x;
	prev_y = y;
      }
    }

    int res = 0;
    for(int y = 0; y < H; y++){
      for(int x = 0; x < W; x++){
	res += turn_on_cost[y][x];
	for(int i = 0; i + 1< move_log[y][x].size(); i++){
	  int duration = move_log[y][x][i+1] - move_log[y][x][i] ;
	  res += min(turn_off_cost[y][x] + turn_on_cost[y][x],
		     consumption_per_unit[y][x] * duration);
	}
	res += turn_off_cost[y][x];
      }
    }

    printf("%d\n",res);
  }
}
