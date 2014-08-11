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

class Facility {
public:
  bool is_cake_store;
  int cal;
  vector<int> to;
  Facility() : is_cake_store(false),cal(0) {}
};

class State {
public:
  int pos;
  int cal;
  int visited_cake_store;

  State() : pos(0),cal(0),visited_cake_store(0) {}
  State(int _p,int _c,int _v) : pos(_p),cal(_c),visited_cake_store(_v) {}
  
  bool operator<(const class State& s) const{
    return cal < s.cal;
  }

  bool operator>(const class State& s) const{
    return cal > s.cal;
  }

};

int main(){
  int num_of_cake_stores;
  int num_of_landmarks;
  int consume_cal_per_unit;
  int num_of_distance_datas;
  while(~scanf("%d %d %d %d",
	       &num_of_cake_stores,
	       &num_of_landmarks,
	       &consume_cal_per_unit,
	       &num_of_distance_datas)){

    if(num_of_cake_stores == 0
       && num_of_landmarks == 0
       && consume_cal_per_unit == 0
       && num_of_distance_datas == 0) break;

    int edges[201][201];
    int dp[201][1<<10];
    Facility nodes[201];

    memset(dp,0x3f,sizeof(dp));
    memset(edges,0x3f,sizeof(edges));

    for(int cake_store_idx = 0; cake_store_idx < num_of_cake_stores; cake_store_idx++){
      int cal;
      scanf("%d",&cal);
      nodes[num_of_landmarks + cake_store_idx + 1].is_cake_store = true;
      nodes[num_of_landmarks + cake_store_idx + 1].cal = cal;
    }

    for(int dist_idx = 0; dist_idx < num_of_distance_datas; dist_idx++){
      string from,to;
      int distance;
      int from_pos;
      int to_pos;
      cin >> from >> to >> distance;
      
      if(from[0] == 'H'){
	from_pos = 0;
      }

      else if(from[0] == 'D'){
	from_pos = 1 + num_of_landmarks + num_of_cake_stores;
      }

      else if(from[0] == 'L'){
	from_pos = 1 + (atoi(from.substr(1,from.size()-1).c_str()) - 1);
      }

      else if(from[0] == 'C'){
	from_pos = 1 + num_of_landmarks + (atoi(from.substr(1,from.size()-1).c_str()) - 1);
      }

      if(to[0] == 'H'){
	to_pos = 0;
      }

      else if(to[0] == 'D'){
	to_pos = 1 + num_of_landmarks + num_of_cake_stores;
      }

      else if(to[0] == 'L'){
	to_pos = 1 + (atoi(to.substr(1,to.size()-1).c_str()) - 1);
      }

      else if(to[0] == 'C'){
	to_pos = 1 + num_of_landmarks + (atoi(to.substr(1,to.size()-1).c_str()) - 1);
      }
      
      edges[from_pos][to_pos] = distance;
      edges[to_pos][from_pos] = distance;

      nodes[from_pos].to.push_back(to_pos);
      nodes[to_pos].to.push_back(from_pos);
    }

    
    priority_queue<State,vector<State>,greater<State> > que;
    que.push(State(0,0,0));
    dp[0][0] = 0;

    while(!que.empty()){
      State s = que.top();
      que.pop();
      for(int i = 0; i < nodes[s.pos].to.size(); i++){
	int next = nodes[s.pos].to[i];
	if(nodes[next].is_cake_store){
	  int cake_store_idx = next - num_of_landmarks - 1;
	  if(s.visited_cake_store & (1 << cake_store_idx)){
	    continue;
	  }

	  int next_cal = s.cal + edges[s.pos][next] * consume_cal_per_unit - nodes[next].cal;
	  if(dp[next][s.visited_cake_store] > next_cal){

	    dp[next][s.visited_cake_store | (1 << cake_store_idx)]
	      = next_cal;
	    que.push(State(next,next_cal,s.visited_cake_store | (1 << cake_store_idx)));
	  }
	}
	else{
	  int next_cal = s.cal + edges[s.pos][next] * consume_cal_per_unit;
	  if(dp[next][s.visited_cake_store] > next_cal){
	    dp[next][s.visited_cake_store] = next_cal;
	    que.push(State(next,next_cal,s.visited_cake_store));
	  }
	}
      }
    }
    
    int res = numeric_limits<int>::max();
    for(int S = 0; S <= (1<<num_of_cake_stores)-1; S++){
      res = min(dp[num_of_landmarks + num_of_cake_stores + 1][S],res);
    }
    printf("%d\n",res);
  }
}
