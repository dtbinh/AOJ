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
typedef pair <int,P > PP;
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

int cost[100][100];
bool is_freezing_plant[100];
int dp[100][101]; //dp[pos][life] := min_cost
int city_num,refreezing_limit,freezing_plant_num,
  road_num,capital_idx,hospital_idx;

class Node{
public:
  Node(int _l,int _p,int _c) : life(_l),pos(_p),cost_sum(_c){}
  int life;
  int pos;
  int cost_sum;
  bool operator<(const Node& n) const{
    return cost_sum < n.cost_sum;
  }
  bool operator>(const Node& n) const{
    return cost_sum > n.cost_sum;
  }
};

int main(){
  while(~scanf("%d %d %d %d %d %d",
	       &city_num,&refreezing_limit,&freezing_plant_num,
	       &road_num,&capital_idx,&hospital_idx)){
    if(city_num == 0) break;

    memset(cost,0x3f,sizeof(cost));
    memset(is_freezing_plant,false,sizeof(is_freezing_plant));

    for(int i=0;i<freezing_plant_num;i++){
      int city_idx;
      scanf("%d",&city_idx);
      is_freezing_plant[city_idx] = true;
    }
    is_freezing_plant[capital_idx] = true;
    is_freezing_plant[hospital_idx] = true;

    for(int i=0;i<road_num;i++){
      int from,to,c;
      scanf("%d %d %d",&from,&to,&c);
      cost[from][to] = c;
      cost[to][from] = c;
    }

    memset(dp,0x3f,sizeof(dp));
    dp[capital_idx][refreezing_limit] = 0;

    Node n(refreezing_limit,capital_idx,0);
    priority_queue<Node,vector<Node>,greater<Node> > que;
    que.push(n);
    
    while(!que.empty()){
      Node n = que.top();
      que.pop();
      int from = n.pos;
      int life = n.life;
      int cost_sum = n.cost_sum;

      for(int to=0;to<city_num;to++){
	if(from == to) continue;

	if(is_freezing_plant[from]){
	  for(int stay=refreezing_limit-life;stay>=0;stay--){
	    if(stay+life-cost[from][to] < 0) break;

	    int remaining_life = life-cost[from][to]+stay;
	    if(dp[to][remaining_life] > cost_sum+cost[from][to]+stay){
	      dp[to][remaining_life] = cost_sum+cost[from][to]+stay;
	      que.push(Node(remaining_life,to,cost_sum+cost[from][to]+stay));
	    }
	  }
	}
	else{
	  if(life <= 0) break;
	  if(life-cost[from][to] < 0) continue;
	  int remaining_life = life-cost[from][to];
	  if(dp[to][remaining_life] > cost_sum+cost[from][to]){
	    dp[to][remaining_life] = cost_sum + cost[from][to];
	    que.push(Node(remaining_life,to,cost_sum+cost[from][to]));
	  }
	}
      }
    }
    
    int res = INF;
    for(int i=0;i<=refreezing_limit;i++){
      res = min(res,dp[hospital_idx][i]);
    }
    
    if(res >= INF){
      printf("Help!\n");
    }
    else{
      printf("%d\n",res);
    }

  }
}
