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

class Edge{
public:
  int to;
  int distance;
  int cost;
  int road_idx;
  Edge(int _t,int _d,int _c,int _r) : to(_t),distance(_d),cost(_c),road_idx(_r) {}
  Edge() {}
  bool operator<(const Edge& e) const{
    return distance < e.distance;
  }

  bool operator>(const Edge& e) const{
    return distance > e.distance;
  }
};

class State {
public:
  int city;
  int total_distance;
  int total_cost;
  int prev_road;
  State(int _c,int _td,int _tc,int _pr) : city(_c), total_distance(_td), total_cost(_tc),prev_road(_pr) {}
  bool operator<(const State& s) const{
    return total_distance < s.total_distance;
  }
  bool operator>(const State& s) const{
    return total_distance > s.total_distance;
  }
};

int main(){
  int total_cities;
  int total_roads;
  while(~scanf("%d %d",&total_cities,&total_roads)){
    if(total_cities == 0 &&  total_roads == 0) break;

    vector<Edge> edges[20001];

    int road_cost[20001];
    memset(road_cost,0,sizeof(road_cost));

    for(int road_idx = 0; road_idx < total_roads; road_idx++){
      int from,to,distance,cost;
      scanf("%d %d %d %d",&from,&to,&distance,&cost);
      edges[from-1].push_back(Edge(to-1,distance,cost,road_idx));
      edges[to-1].push_back(Edge(from-1,distance,cost,road_idx));
      road_cost[road_idx] = cost;
    }
    
    int dp[20001];
    memset(dp,0x3f,sizeof(dp));

    priority_queue<State,vector<State>,greater<State> > que;
    que.push(State(0,0,0,-1));
    
    while(!que.empty()){
      State s = que.top();
      que.pop();

      if(dp[s.city] <= s.total_distance) continue;
      dp[s.city] = s.total_distance;

      for(int i=0;i<edges[s.city].size();i++){
	int to = edges[s.city][i].to;
	int next_distance = edges[s.city][i].distance;
	int next_cost = edges[s.city][i].cost;

	que.push(State(to,s.total_distance + next_distance,s.total_cost + next_cost,i));
      }
    }

    int res = 0;
    for(int to=1; to<total_cities; to++){
      int min_v = INF;
      for(int from_idx=0; from_idx<edges[to].size(); from_idx++){
	int from = edges[to][from_idx].to;
	int distance = edges[to][from_idx].distance;
	int cost = edges[to][from_idx].cost;
	
	//check whether the path is corresponding to the dijkstra's shortest path or not
	if(dp[from] + distance == dp[to] && cost < min_v){
	  min_v = cost;
	}
      }
      res += min_v;
    }

    printf("%d\n",res);
  }
}
