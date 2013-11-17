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

vector<string> rotate(const string& str ,int turn_count,int mask_interval){
  vector<string> res;
  
  int base_mask = (1<<mask_interval) - 1;
  for(int offset=0;offset+mask_interval<=str.size();offset++){
    int current_mask = (base_mask << offset);

    string next_dial="";
    for(int i=0;i<str.size();i++){
      if((current_mask >> i) & 1){
	int next_num = (str[i] - '0' + turn_count) % 10;
	next_dial.push_back('0' + next_num);
      }
      else{
	next_dial.push_back(str[i]);
      }
    }
    res.push_back(next_dial);
  }

  return res;
}

class State{
public:
  string dial;
  int cost;
  State(string _d,int _c) : dial(_d),cost(_c) {}
  State() : dial(""),cost(0) {}

  bool operator <(const State& s) const{
    return cost < s.cost;
  }

  bool operator >(const State& s) const{
    return cost > s.cost;
  }
};

int main(){
  int total_dials;
  while(~scanf("%d",&total_dials)){
    if(total_dials == 0) break;
    
    string initial_state,unlocked_state;
    cin >> initial_state >> unlocked_state;
    map<string,int> dp;
    dp[initial_state] = 0;

    priority_queue<State,vector<State>,greater<State> > que;
    que.push(State(initial_state,0));

    while(!que.empty()){
      State s = que.top();
      que.pop();
      
      for(int turn_count=0;turn_count<10;turn_count++){
	for(int mask_interval = 1; mask_interval <= s.dial.size(); mask_interval++){
	  vector<string> candidates = rotate(s.dial,turn_count,mask_interval);
	  for(int candidate_idx = 0;candidate_idx < candidates.size(); candidate_idx++){
	    if(dp.find(candidates[candidate_idx]) == dp.end()){
	      dp[candidates[candidate_idx]] = s.cost + 1;

	      if(candidates[candidate_idx] == unlocked_state) goto found;

	      if(s.cost + 1 >= 5) continue;
	      que.push(State(candidates[candidate_idx],s.cost + 1));
	    }
	  }
	}
      }
    }

  found:;
    printf("%d\n",dp[unlocked_state]);
  }
}
