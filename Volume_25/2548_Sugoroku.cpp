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

class State {
public:
  int pos;
  int cost;
  int prev_hand;
  int prev_pos;
  State(int _p,int _c) : pos(_p),cost(_c),prev_hand(-1000),prev_pos(-1000) {}
  State(int _p,int _c,int _ph,int _pp) : pos(_p),cost(_c),prev_hand(_ph),prev_pos(_pp) {}
  bool operator<(const State& s) const{
    return cost < s.cost;
  }
  bool operator>(const State& s) const{
    return cost > s.cost;
  }
};

struct DP{
  int cost;
  int prev_hand;
  int prev_pos;
  DP(int _c,int _ph,int _pp) : cost(_c),prev_hand(_ph),prev_pos(_pp){}
  DP() : cost(INF),prev_hand(-1000),prev_pos(-1000){}
};

int main(){
  int total_cells;
  while(~scanf("%d",&total_cells)){
    int dice[7];
    for(int i=1;i<=6;i++){
      scanf("%d",dice + i);
    }
    int start,goal;
    scanf("%d %d",&start,&goal);
    int stage[303];
    for(int i=1;i<=total_cells;i++){
      scanf("%d",stage + i);
    }
    
    priority_queue<State,vector<State>,greater<State> > que;
    que.push(State(start,0,-1000,-1000));

    DP dp[303];

    while(!que.empty()){
      State s = que.top();
      que.pop();

      if(dp[s.pos].cost <= s.cost) continue;

      dp[s.pos].cost = s.cost;
      dp[s.pos].prev_hand = s.prev_hand;
      dp[s.pos].prev_pos = s.prev_pos;

      for(int i=1;i<=6;i++){
	int dx1 = s.pos + dice[i];
	int dx2 = s.pos - dice[i];

	if(1 <= dx1 && dx1 <= total_cells){
	  dx1 += stage[dx1];
	  que.push(State(dx1,s.cost + 1,i,s.pos));
	}
	if(1 <= dx2 && dx2 <= total_cells){
	  dx2 += stage[dx2];
	  que.push(State(dx2,s.cost + 1,-i,s.pos));
	}
      }
    }

    vector<int> hands;
    int prev_x = goal;
    for(int round = 0;round <= 3000;round++){
      hands.push_back(dp[prev_x].prev_hand);
      prev_x = dp[prev_x].prev_pos;
      if(prev_x == start) break;
    }

    reverse(hands.begin(),hands.end());

    int hand_idx = 0;
    for(int round = 0;round <= 3000;round++){
      int num;
      scanf("%d", &num);
      
      if(num != abs(hands[hand_idx])){
	printf("0\n"); fflush(stdout);
      }

      else if(num == abs(hands[hand_idx])){
	if(hands[hand_idx] > 0){
	  printf("1\n"); fflush(stdout);
	}
	else{
	  printf("-1\n"); fflush(stdout);
	}
	hand_idx++;
      }

      if(hand_idx >= hands.size()) break;
    }
  }
}
