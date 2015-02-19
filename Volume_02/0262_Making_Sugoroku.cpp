#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
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

using namespace std;

typedef long long ll;
typedef pair<int,string> P;

static const double EPS = 1e-8;

class State {
public:
  int x;
  int cost;
  State(int x,int cost)
    : x(x), cost(cost) {}
  bool operator<(const State& s) const {
    return cost < s.cost;
  }
  bool operator>(const State& s) const {
    return cost > s.cost;
  }
};

int main(){
  int max_roulette_num;
  while(~scanf("%d",&max_roulette_num)){
    if(max_roulette_num == 0) break;

    int stage[320] = {};
    int total_cells;
    scanf("%d",&total_cells);
    for(int i = 0; i < total_cells; i++){
      int cell;
      scanf("%d",&cell);
      stage[i+1] = cell;
    }
    stage[0] = 0;
    stage[total_cells + 1] = 0;
    
    priority_queue<State,vector<State>,greater<State> > que;
    que.push(State(0,0));
    int dp[320];
    memset(dp,0x3f,sizeof(dp));
    dp[0] = 0;
    while(!que.empty()){
      State s = que.top();
      que.pop();
      for(int i = 1; i <= max_roulette_num; i++){
	int next = s.x + i;
	if(next > total_cells + 1) continue;
	next += stage[next];
	if(dp[next] <= s.cost + 1) continue;
	dp[next] = s.cost + 1;
	que.push(State(next,s.cost + 1));
      }
    }

    printf("%s\n", dp[total_cells + 1] < INF ? "OK" : "NG");
  }
}
