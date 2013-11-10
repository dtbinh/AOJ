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
 
const static int tx[] = {0,1,1,1,0,-1,-1,-1};
const static int ty[] = {-1,-1,0,1,1,1,0,-1};
 
static const double EPS = 1e-8;

class Princess {
public:
  int pos;
  int money;
  int attacked_count;
  Princess(int _p,int _m,int _atk) :pos(_p), money(_m), attacked_count(_atk){}
  bool operator<(const Princess& p) const {
    return attacked_count < p.attacked_count;
  }
  bool operator>(const Princess& p) const {
    return attacked_count > p.attacked_count;
  }
};

int main(){
  int total_inns,total_roads,total_money;
  while(~scanf("%d %d %d",&total_inns,&total_roads,&total_money)){
    if(total_inns == 0 && total_roads == 0 && total_money == 0) break;

    int cost[101][101];
    int robber[101][101];
    int dp[101][101];
    memset(cost,0x3f,sizeof(cost));
    memset(robber,0x3f,sizeof(robber));
    memset(dp,0x3f,sizeof(dp));

    for(int road_idx=0;road_idx<total_roads;road_idx++){
      int from,to;
      int dist,robber_num;
      scanf("%d %d %d %d",&from,&to,&dist,&robber_num);
      cost[from][to] = dist;
      cost[to][from] = dist;
      robber[from][to] = robber_num;
      robber[to][from] = robber_num;
    }

    priority_queue<Princess,vector<Princess>,greater<Princess> > que;
    que.push(Princess(1,total_money,0));
    

    while(!que.empty()){
      Princess pr = que.top();
      int from = pr.pos;
      int remaining_money = pr.money;
      int attacked_count = pr.attacked_count;
      que.pop();

      for(int to=2;to<=total_inns;to++){
	if(to == from) continue;
	if(cost[from][to] == INF) continue;


	if(cost[from][to] <= remaining_money){
	  //use_money
	  int next_atk = attacked_count;
	  int next_money = remaining_money - cost[from][to];

	  if(dp[to][next_money] > next_atk){
	    dp[to][next_money] = next_atk;
	    Princess next(to,next_money,next_atk);
	    que.push(next);
	  }

	  //dont use
	  int next_atk2 = attacked_count + robber[from][to];
	  int next_money2 = remaining_money;

	  if(dp[to][next_money2] > next_atk2){
	    dp[to][next_money2] = next_atk2;
	    Princess next2(to,next_money2,next_atk2);
	    que.push(next2);
	  }
	}
	else{
	  //dont use
	  int next_atk2 = attacked_count + robber[from][to];
	  int next_money2 = remaining_money;

	  if(dp[to][next_money2] > next_atk2){
	    dp[to][next_money2] = next_atk2;
	    Princess next2(to,next_money2,next_atk2);
	    que.push(next2);
	  }
	}
      }
    }

    int res = INF;
    for(int money=0;money<=100;money++){
      res = min(res,dp[total_inns][money]);
    }
    printf("%d\n",res);
  }
}
