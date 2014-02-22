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
  
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};

class Star {
public:
  int lower_bound_time;
  int upper_bound_time;
  Star(int _l,int _u) : lower_bound_time(_l),upper_bound_time(_u){}
  Star() : lower_bound_time(0),upper_bound_time(0){}
  bool operator<(const Star& s) const{
    return lower_bound_time < s.lower_bound_time;
  }
  bool operator>(const Star& s) const{
    return lower_bound_time > s.lower_bound_time;
  }
};

class State{
public:
  int time;
  int pos;
  int age7_duration;
  State(int _t,int _p,int _d) : time(_t),pos(_p), age7_duration(_d){}
  bool operator<(const State& s) const{
    return age7_duration < s.age7_duration;
  }
  bool operator>(const State& s) const{
    return age7_duration > s.age7_duration;
  }
};

int main(){
  int total_stars;
  int start;
  while(~scanf("%d %d",&total_stars,&start)){
    start--;

    Star stars[501];
    for(int star_idx = 0; star_idx < total_stars; star_idx++){
      int lower_bound_time,upper_bound_time;
      scanf("%d %d",&lower_bound_time,&upper_bound_time);
      stars[star_idx] = Star(lower_bound_time,upper_bound_time);
    }

    sort(stars,stars+total_stars);

    int cost[501][501];
    memset(cost,0x3f,sizeof(cost));
    for(int from_star_idx = 0; from_star_idx < total_stars; from_star_idx++){
      for(int to_star_idx = 0; to_star_idx < total_stars; to_star_idx++){
	scanf("%d",&cost[from_star_idx][to_star_idx]);
      }
    }
    for(int mid_star_idx = 0; mid_star_idx < total_stars; mid_star_idx++){
      for(int from_star_idx = 0; from_star_idx < total_stars; from_star_idx++){
	for(int to_star_idx = 0; to_star_idx < total_stars; to_star_idx++){
	  cost[from_star_idx][to_star_idx]
	    = min(cost[from_star_idx][mid_star_idx]
		  + cost[mid_star_idx][to_star_idx],
		  cost[from_star_idx][to_star_idx]);
	}
      }
    }

    map<P,int> visited;
    priority_queue<State,vector<State> > que;
    que.push(State(0,start,0));

    int max_duration = 0;
    while(!que.empty()){
      State s = que.top();
      que.pop();

      int remainings = 0;
      if(s.time < stars[s.pos].upper_bound_time){
	remainings = min(stars[s.pos].upper_bound_time - stars[s.pos].lower_bound_time,
			 stars[s.pos].upper_bound_time - s.time);
      }
      max_duration = max(s.age7_duration + remainings,max_duration);


      if(visited.find(P(s.time,s.pos)) != visited.end()
	 && visited[P(s.time,s.pos)] >= s.age7_duration) continue;
      visited[P(s.time,s.pos)] = s.age7_duration;

      for(int to=0;to<total_stars;to++){
	if(s.pos == to) continue;

	int mission_ignored_time = s.time + cost[s.pos][to];
	que.push(State(mission_ignored_time,to,s.age7_duration));

	int considering_mission_time = stars[s.pos].upper_bound_time + cost[s.pos][to];
	int age7_duration = min(stars[s.pos].upper_bound_time - stars[s.pos].lower_bound_time,
				stars[s.pos].upper_bound_time - s.time);

	if(age7_duration > 0){
	  que.push(State(considering_mission_time,to,s.age7_duration + age7_duration));
	}
      }
    }
    printf("%d\n",max_duration);
  }
}
