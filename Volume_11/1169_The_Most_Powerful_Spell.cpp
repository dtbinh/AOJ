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

class State {
public:
  string cost;
  int pos;
  bool operator<(const State& s) const{
    return cost < s.cost;
  }
  bool operator>(const State& s) const{
    return cost > s.cost;
  }
  State() : cost(""),pos(0) {}
  State(const string& _c,int _p) : cost(_c),pos(_p) {}
};

int main(){
  int total_nodes;
  int total_arrows;
  int star_node_idx;
  int gold_node_idx;
  while(~scanf("%d %d %d %d",
	       &total_nodes,
	       &total_arrows,
	       &star_node_idx,
	       &gold_node_idx)){
    if(total_nodes == 0
       && total_arrows == 0
       && star_node_idx == 0
       && gold_node_idx == 0) break;

    string dp[total_nodes][401];
    vector<string> nodes[total_nodes][total_nodes];
    
    for(int i=0;i<total_nodes;i++){
      for(int j=0;j<=400;j++){
	dp[i][j] = string(1000,'~');
      }
    }

    for(int arrow_idx = 0; arrow_idx < total_arrows; arrow_idx++){
      int from,to;
      string word;
      cin >> from >> to >> word;
      nodes[from][to].push_back(word);
    }

    priority_queue<State,vector<State>,greater<State> >  que;
    que.push(State("",star_node_idx));
    dp[star_node_idx][0] = "";

    string res(1000,'~');
    while(!que.empty()){
      State s = que.top();
      que.pop();
      if(s.cost >= res) continue;

      for(int to=0;to<total_nodes;to++){
	for(int str_idx = 0; str_idx < nodes[s.pos][to].size(); str_idx++){
	  string next_cost = s.cost + nodes[s.pos][to][str_idx];
	  if(next_cost >= res) continue;
	  if(next_cost.size() >= 400) continue;

	  if(next_cost < dp[to][next_cost.size()]){
	    dp[to][next_cost.size()] = next_cost;
	    if(to == gold_node_idx
	       && res > next_cost){
	      res = next_cost;
	    }
	    que.push(State(next_cost,to));
	  }
	}
      }
    }

    if(res.size() > total_nodes * 6){
      cout << "NO" << endl;
    }
    else{
      cout << res << endl;
    }
  }
}
