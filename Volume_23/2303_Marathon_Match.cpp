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
typedef pair <double,double> P;
typedef pair <int,P > PP;
 
int tx[] = {0,1,0,-1};//URDL
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-12;

class State{
public:
  double probability;
  double cost;
  State(double _p,double _c) : probability(_p),cost(_c){}
  bool operator<(const State& s) const{
    return cost < s.cost;
  }
  bool operator>(const State& s) const{
    return cost > s.cost;
  }
};

int main(){
  int total_players;
  int total_resting_places;
  int goal_distance;
  while(~scanf("%d %d %d",&total_players,&total_resting_places,&goal_distance)){

    vector<vector<State> > players;

    for(int player_idx=0;player_idx<total_players;player_idx++){
      int probability;
      int resting_duration;
      int speed;
      scanf("%d %d %d",&probability,&resting_duration,&speed);
      
      double dp[51][5001];
      vector<State> player;
      memset(dp,0,sizeof(dp));

      dp[0][0] = 1.0;
      for(int resting_place_idx=0;resting_place_idx<total_resting_places;resting_place_idx++){
	for(int total_resting_duration = 0; total_resting_duration <= 5000; total_resting_duration++){
	  if(dp[resting_place_idx][total_resting_duration] <= EPS) continue;

	  dp[resting_place_idx+1][total_resting_duration + resting_duration]
	    += dp[resting_place_idx][total_resting_duration] * (double)probability/100.0;

	  dp[resting_place_idx+1][total_resting_duration]
	    += dp[resting_place_idx][total_resting_duration] * (1.0 - (double)probability/100.0);
	}
      }

      for(int total_resting_duration = 0; total_resting_duration <= 5000; total_resting_duration++){
	if(dp[total_resting_places][total_resting_duration] != 0){
	  // printf("rest:%d prob:%lf\n",total_resting_duration,dp[total_resting_places][total_resting_duration]);
	  player.push_back(State(dp[total_resting_places][total_resting_duration],total_resting_duration + (double)goal_distance/(double)speed));
	}
      }
      sort(player.begin(),player.end());
      players.push_back(player);
    }

    for(int player_idx=0;player_idx<total_players;player_idx++){

      double win_prob = 0.0;
      for(int state_idx=0;state_idx<players[player_idx].size();state_idx++){
	double cost = players[player_idx][state_idx].cost;
	double player_prob = players[player_idx][state_idx].probability;

	double rival_prob = 1.0;
	for(int rival_idx=0;rival_idx<total_players;rival_idx++){
	  if(player_idx == rival_idx) continue;
	  double tmp_prob = 0.0;
	  for(int rival_state_idx=0;rival_state_idx<players[rival_idx].size();rival_state_idx++){
	    if(players[rival_idx][rival_state_idx].cost > cost){
	      tmp_prob += players[rival_idx][rival_state_idx].probability;
	    }
	  }

	  rival_prob *= tmp_prob;
	}
	win_prob += player_prob * rival_prob;
      }

      printf("%.7lf\n",win_prob);
    }
  }
}
