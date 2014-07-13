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
  
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};

int dp[5001][5001]; //dp[city][life] ::= cost

class State{
public:
  short city;
  int cost;
  short life;
  State(short _ci,int _co,short _l) :
    city(_ci),cost(_co),life(_l) {}
  bool operator<(const State& s) const {
    return cost < s.cost;
  }
  bool operator>(const State& s) const {
    return cost > s.cost;
  }
};

struct Taxi{
  int cost;
  short life;
  Taxi() : cost(0),life(0) {}
  Taxi(int _c,short _l) : cost(_c), life(_l) {}
};

int main(){
  int total_cities;
  int total_roads;
  while(~scanf("%d %d",&total_cities,&total_roads)){
    Taxi taxi[5001];
    memset(dp,0x3f,sizeof(dp));
    vector<short> roads[5001];

    for(int city_idx = 0; city_idx < total_cities; city_idx++){
      int cost;
      short life;
      scanf("%d %hd",&cost,&life);
      taxi[city_idx] = Taxi(cost,life);
    }

    for(int road_idx = 0;road_idx < total_roads;road_idx++){
      short from,to;
      scanf("%hd %hd",&from,&to);
      from--; to--;
      roads[from].push_back(to);
      roads[to].push_back(from);
    }
    
    priority_queue<State,vector<State>,greater<State> > que;
    que.push(State(0,0,0));

    int res = INF;
    while(!que.empty()){
      State s = que.top();
      que.pop();

      // cout << s.city << endl;
      if(s.city == total_cities - 1){
	res = min(res,s.cost);
	break;
      }

      for(int i=0; i < roads[s.city].size(); i++){
	short next_city = roads[s.city][i];
	if(s.life == 0){
	  //have to ride
	  int next_cost = s.cost + taxi[s.city].cost;
	  short next_life = taxi[s.city].life - 1;
	  if(dp[next_city][next_life] <= next_cost) continue;
	  que.push(State(next_city,next_cost,next_life));
	}
	else{
	  //ride
	  int next_cost = s.cost + taxi[s.city].cost;
	  short next_life = taxi[s.city].life - 1;
	  if(dp[next_city][next_life] > next_cost){
	    dp[next_city][next_life] = next_cost;
	    que.push(State(next_city,next_cost,next_life));
	  }

	  //don't ride
	  next_cost = s.cost;
	  next_life = s.life - 1;
	  if(dp[next_city][next_life] > next_cost){
	    dp[next_city][next_life] = next_cost;
	    que.push(State(next_city,next_cost,next_life));
	  }
	}
      }
    }

    printf("%d\n",res);
  }
}
