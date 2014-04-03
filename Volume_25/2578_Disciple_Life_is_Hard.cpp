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

int dp[101][101];
int cost2cal[101][101];
int cal2well[10101];

int main(){
  //STUNOD
  int upper_HP;
  int total_trainings;
  int training_norma;
  int total_donuts;
  int recover;
  int total_days;
  while(~scanf("%d %d %d %d %d %d",
	       &upper_HP,
	       &total_trainings,
	       &training_norma,
	       &total_donuts,
	       &recover,
	       &total_days)){
    vector<P> trainings;
    for(int training_idx=0;training_idx<total_trainings;training_idx++){
      int training_cost,consume_cal;
      scanf("%d %d",&training_cost,&consume_cal);
      trainings.push_back(P(training_cost,consume_cal));
    }
    vector<P> donuts;
    for(int donuts_idx=0;donuts_idx<total_donuts;donuts_idx++){
      int well_being_level,retain_cal;
      scanf("%d %d",&well_being_level,&retain_cal);
      donuts.push_back(P(well_being_level,retain_cal));
    }

    memset(cost2cal,-1,sizeof(cost2cal));

    cost2cal[0][0] = 0;
    for(int training_idx=0;training_idx<total_trainings;training_idx++){
      int cal = trainings[training_idx].second;
      int training_cost = trainings[training_idx].first;

      for(int prev=training_norma;prev>=0;prev--){
	for(int consumed_HP = upper_HP;consumed_HP >= 0 ;consumed_HP--){
	  if(cost2cal[consumed_HP][prev] == -1) continue;

	  if(consumed_HP + training_cost > upper_HP) continue;
	  cost2cal[consumed_HP + training_cost][prev+1]
	    = max(cost2cal[consumed_HP][prev] + cal,
		  cost2cal[consumed_HP + training_cost][prev+1]);
	}
      }
    }

    memset(cal2well,0,sizeof(cal2well));
    for(int donuts_idx=0;donuts_idx<total_donuts;donuts_idx++){
      int well = donuts[donuts_idx].first;
      int retain = donuts[donuts_idx].second;
      for(int cal=0;cal<=10000;cal++){
	cal2well[cal + retain] = max(cal2well[cal] + well,
				     cal2well[cal + retain]);
      }
    }


    memset(dp,-1,sizeof(dp));
    dp[0][upper_HP] = 0;
    for(int day=0;day<total_days;day++){
      for(int HP=0;HP<=upper_HP;HP++){
	if(dp[day][HP] == -1) continue;
	for(int training_cost=0;training_cost<=HP;training_cost++){
	  if(cost2cal[training_cost][training_norma] == -1) continue;

	  int next_HP = min(HP - training_cost + recover,upper_HP);
	  dp[day+1][next_HP]
	    = max(dp[day][HP] + cal2well[cost2cal[training_cost][training_norma]],
		  dp[day+1][next_HP]);
	}
      }
    }

    int res = -1;
    for(int HP=0;HP<=upper_HP;HP++){
      res = max(dp[total_days][HP],res);
    }
    printf("%d\n",res);
  }
}
