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

string rotate(const string& str ,int offset,int turn_count,int mask_interval){
  int base_mask = (1<<mask_interval) - 1;
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
  return next_dial;
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

int compute_dist(int lhs,int rhs){
  if(lhs > rhs){
    //0...rhs...lhs...9
    return (9-lhs + rhs + 1);
  }
  else if(lhs < rhs){
    //0...lhs...rhs...9
    return rhs - lhs;
  }
  return 0;
}

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

      int change_idx = 0;
      for(int dial_idx = 0; dial_idx < s.dial.size(); dial_idx++){
	if(s.dial[dial_idx] == unlocked_state[dial_idx]) continue;
	change_idx = dial_idx;
	break;
      }
      int turn_count = compute_dist(s.dial[change_idx] - '0',unlocked_state[change_idx] - '0');
      for(int mask_interval = 1; change_idx + mask_interval <= s.dial.size(); mask_interval++){
	string candidate = rotate(s.dial,change_idx,turn_count,mask_interval);
	if(dp.find(candidate) == dp.end()){
	  dp[candidate] = s.cost + 1;
	  que.push(State(candidate,s.cost + 1));
	}
      }
    }

    printf("%d\n",dp[unlocked_state]);
  }
}
