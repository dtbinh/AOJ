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

class Road{
public:
  int distance;
  int speed_limit;
  Road(int _d,int _s) : distance(_d),speed_limit(_s) {}
  Road() : distance(INF),speed_limit(0) {}
};

class State{
public:
  int city;
  int speed;
  double time;
  int prev;
  State() : city(0),speed(1),time(0.0), prev(0){}
  State(int _c,int _s,double _t,int _p) : city(_c),speed(_s),time(_t),prev(_p){}
  
  bool operator<(const State& s) const{
    return time < s.time;
  }

  bool operator>(const State& s) const{
    return time > s.time;
  }
};

int main(){
  int total_cities;
  int total_roads;
  while(~scanf("%d %d",&total_cities,&total_roads)){
    if(total_cities == 0 && total_roads == 0) break;
    int start,goal;
    scanf("%d %d",&start,&goal);

    Road edges[100][100];
    for(int road_idx = 0; road_idx < total_roads; road_idx++){
      int from,to,distance,speed_limit;
      scanf("%d %d %d %d",&from,&to,&distance,&speed_limit);
      edges[from][to].distance = distance;
      edges[from][to].speed_limit = speed_limit;
      edges[to][from].distance = distance;
      edges[to][from].speed_limit = speed_limit;
    }

    priority_queue<State,vector<State>,greater<State> > que;
    que.push(State(start,1,0.0,0)); //pos,speed,time

    bool dp[50][50][50];

    memset(dp,false,sizeof(dp));
    double res = -0.1;
    while(!que.empty()){
      State s = que.top();
      que.pop();

      if(dp[s.prev][s.city][s.speed]) continue;

      if(s.city == goal && s.speed == 1){
	res = s.time;
	break;
      }

      dp[s.prev][s.city][s.speed] = true;

      for(int to = 1; to <= total_cities; to++){
	if(edges[s.city][to].distance >= INF) continue;

	if(edges[s.city][to].speed_limit >= s.speed - 1
	   && s.speed-1 >= 1){
	  que.push(State(to,
			 s.speed -1,
			 s.time + (double)edges[s.city][to].distance/(double)(s.speed - 1),
			 s.city));
	}

	if(edges[s.city][to].speed_limit >= s.speed + 1
	   && s.time != 0.0){
	  que.push(State(to,
			 s.speed + 1,
			 s.time + (double)edges[s.city][to].distance/(double)(s.speed + 1),
			 s.city));
	}
	
	if(edges[s.city][to].speed_limit >= s.speed){
	  que.push(State(to,
			 s.speed,
			 s.time + (double)edges[s.city][to].distance/(double)(s.speed),
			 s.city));

	}
      }
    }

    if(res < 0){
      printf("unreachable\n");
    }
    else{
      printf("%.5f\n",res);
    }

  }
}
