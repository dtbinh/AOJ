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

class Info {
public:
  int _to;
  int _fare;
  int _time;
  int _company_id;
  Info() : _fare(0),_time(0),_company_id(0) {}
  Info(int to,int fare,int time,int company_id)
    : _to(to),_fare(fare),_time(time),_company_id(company_id) {}
};

class State{
public:
  int _passed_time;
  int _cost;
  int _pos;
  State(int pass,int c,int pos) : _passed_time(pass),_cost(c),_pos(pos) {}
  bool operator<(const State& s) const {
    return _cost < s._cost;
  }
  bool operator>(const State& s) const {
    return _cost > s._cost;
  }

};

bool dp[101][30];

int main(){
  int num_of_stations;
  int num_of_lines;
  int time_limit;
  int num_of_JAG_companies;
  while(~scanf("%d %d %d %d",
	       &num_of_stations,
	       &num_of_lines,
	       &time_limit,
	       &num_of_JAG_companies)){
    if(num_of_stations == 0
       && num_of_lines == 0 
       && time_limit == 0
       && num_of_JAG_companies == 0) break;

    vector<Info> lines[501];

    for(int line_idx = 0; line_idx < num_of_lines; line_idx++){
      int from,to;
      int fare,time,company_id;
      scanf("%d %d %d %d %d",
	    &from,&to,&fare,&time,&company_id);
      company_id--;
      lines[to].push_back(Info(from,fare,time,company_id));
      lines[from].push_back(Info(to,fare,time,company_id));
    }

    int station_S;
    int station_T;
    scanf("%d %d",&station_S,&station_T);

    int num_of_passports;
    scanf("%d",&num_of_passports);

    int init_cost[1<<num_of_JAG_companies];
    memset(init_cost,0x3f,sizeof(init_cost));
    init_cost[0] = 0;

    for(int passport_idx = 0; passport_idx < num_of_passports; passport_idx++){
      int num_of_companies;
      int fare;
      scanf("%d %d",&num_of_companies,&fare);

      int S = 0;
      for(int company_idx=0; company_idx < num_of_companies; company_idx++){
	int company_id;
	scanf("%d",&company_id);
	company_id--;

	S |= (1 << company_id);
      }
      init_cost[S] = fare;
    }

    for(int S1 = 0; S1 <= (1<<num_of_JAG_companies) -1; S1++){
      for(int S2 = 0; S2 <= (1<<num_of_JAG_companies) -1; S2++){
	init_cost[S1 | S2] = min(init_cost[S1 | S2],
				 init_cost[S1] + init_cost[S2]);
      }
    }

    int res = INF;
    for(int S = 0; S <= (1<<num_of_JAG_companies) -1; S++){
      if(init_cost[S] >= INF) continue;

      priority_queue<State,vector<State>,greater<State> > que;
      que.push(State(0,init_cost[S],station_S));

      memset(dp,false,sizeof(dp));

      while(!que.empty()){
	State s = que.top();
	que.pop();

	if(dp[s._pos][s._passed_time]) continue;

	dp[s._pos][s._passed_time] = true;

	if(s._pos == station_T){
	  res = min(res,s._cost);
	  goto found;
	}

	for(int i = 0; i < lines[s._pos].size();i++){
	  int to = lines[s._pos][i]._to;

	  int next_time = s._passed_time + lines[s._pos][i]._time;
	  if(next_time > time_limit) continue;
	  if(dp[to][next_time]) continue;

	  int cost = (S & (1<<lines[s._pos][i]._company_id)) ? 0
	    : lines[s._pos][i]._fare;
	  int next_cost = s._cost + cost;

	  que.push(State(next_time,next_cost,to));
	}
      }
      
    found:;
    }

    printf("%d\n",res == INF ? -1 : res);
  }
}
