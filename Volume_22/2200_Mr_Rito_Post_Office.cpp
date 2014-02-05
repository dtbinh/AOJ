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
#include <iterator>
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;
 
int tx[] = {0,1,0,-1};//URDL
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

struct Edge{
  int dst;
  int time;
  char type;
  Edge(int _d,int _ti,char _ty) : dst(_d),time(_ti),type(_ty){}
  Edge(){}
};

class State{
public:
  int next_target_idx;
  int current_pos;
  int cost;
  int ship_pos;
  State(int _nt,int _cp,int _c,int _s) : next_target_idx(_nt), current_pos(_cp),cost(_c),ship_pos(_s) {}
  bool operator <(const State& s) const {
    return cost < s.cost;
  }
  bool operator >(const State& s) const {
    return cost > s.cost;
  }
};

int heuristic(int src,int dst,int warshall_floyd[201][201]){
  return warshall_floyd[src][dst];
}

int dp[201][201][201]; //current_pos,target_pos,ship_pos

int main(){
  int total_cities;
  int total_roads;

  while(~scanf("%d %d",&total_cities,&total_roads)){
    if(total_cities == 0 && total_roads == 0) break;

    vector<Edge> edges[201];
    int warshall_floyd[201][201];
    memset(warshall_floyd,0x3f,sizeof(warshall_floyd));

    for(int road_idx = 0; road_idx < total_roads; road_idx++){
      int src,dst,time;
      char type[2];
      scanf("%d %d %d %s",&src,&dst,&time,type);
      edges[src].push_back(Edge(dst,time,type[0]));
      edges[dst].push_back(Edge(src,time,type[0]));
      warshall_floyd[src][dst] = time;
      warshall_floyd[dst][src] = time;
    }

    int total_routes;
    int routes[1001];
    scanf("%d",&total_routes);
    for(int route_idx = 0; route_idx < total_routes; route_idx++){
      int route;
      scanf("%d",&route);
      routes[route_idx] = route;
    }

    for(int k = 0; k <= total_cities; k++){
      for(int i = 0; i <= total_cities; i++){
	for(int j = 0; j <= total_cities; j++){
	  warshall_floyd[i][j]
	    = min(warshall_floyd[i][j],
		  warshall_floyd[i][k]+warshall_floyd[k][j]);
	}
      }
    }
    priority_queue<State,vector<State>,greater<State> > que;

    // next_target_idx,current_pos,cost,ship_pos
    que.push(State(0,routes[0],0,routes[0]));

    memset(dp,0x3f,sizeof(dp));

    int res = INF;
    while(!que.empty()){
      State s = que.top();
      que.pop();
      if(dp[s.current_pos][routes[s.next_target_idx]][s.ship_pos]
	 <= s.cost + heuristic(s.current_pos,routes[total_routes-1],warshall_floyd)) continue;
      dp[s.current_pos][routes[s.next_target_idx]][s.ship_pos]
	= s.cost + heuristic(s.current_pos,routes[total_routes-1],warshall_floyd);

      if(s.next_target_idx == total_routes - 1
	 && routes[s.next_target_idx] == s.current_pos){
	res = s.cost;
	goto found;
      }

      for(int dst_idx = 0; dst_idx < edges[s.current_pos].size(); dst_idx++){
	int dst = edges[s.current_pos][dst_idx].dst;
	int time = edges[s.current_pos][dst_idx].time;
	char type = edges[s.current_pos][dst_idx].type;

	if(type == 'S' && s.ship_pos != s.current_pos) continue;

	int next_target_idx = s.next_target_idx;
	if(s.current_pos == routes[s.next_target_idx]){
	  next_target_idx++;
	}
	int next_ship_pos = s.ship_pos;
	if(type == 'S' && s.current_pos == s.ship_pos){
	  next_ship_pos = dst;
	}
	// next_target_idx,current_pos,cost,ship_pos
	State next(next_target_idx,dst,s.cost + time,next_ship_pos);
	que.push(next);
      }
    }
  found:;

    printf("%d\n",res);
  }
}
