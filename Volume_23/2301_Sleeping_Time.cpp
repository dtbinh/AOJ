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
 
static const double EPS = 1e-10;

struct RL{
  double R;
  double L;
  double probability;
  RL(double _r,double _l,double _p) : R(_r),L(_l),probability(_p) {}
};

int main(){
  int total_nights;
  int R,L;

  while(~scanf("%d %d %d",&total_nights,&R,&L)){
    vector<RL> dp[31]; //dp[day][idx].{R,L} := probability
    dp[0].push_back(RL(R,L,1.0));

    double mistake_probability,reference_diff,optimal_sleep_time;
    scanf("%lf %lf %lf",&mistake_probability,&reference_diff,&optimal_sleep_time);
    
    for(int day=1;day<=total_nights;day++){
      for(int i=0;i<dp[day-1].size();i++){
	double H = (dp[day-1][i].R+dp[day-1][i].L)/2.0;

	if(H >= optimal_sleep_time){
	  double correct_next_L = H;
	  RL rl_c(dp[day-1][i].R,correct_next_L,
		  dp[day-1][i].probability * (1.0-mistake_probability));
	  dp[day].push_back(rl_c);

	  double wrong_next_R = H;
	  RL rl_w(wrong_next_R,dp[day-1][i].L,
		  dp[day-1][i].probability * mistake_probability);
	  dp[day].push_back(rl_w);
	}
	else{
	  double correct_next_R = H;
	  RL rl_c(correct_next_R,dp[day-1][i].L,
		  dp[day-1][i].probability * (1.0-mistake_probability));
	  dp[day].push_back(rl_c);

	  double wrong_next_L = H;
	  RL rl_w(dp[day-1][i].R,wrong_next_L,
		  dp[day-1][i].probability * mistake_probability);
	  dp[day].push_back(rl_w);
	}
      }

      dp[day-1].clear();
    }

    int last_night_day = total_nights;
    double prob = 0.0;
    for(int i=0;i<dp[last_night_day].size();i++){
      // cout << dp[last_night_day][i].R << " " << dp[last_night_day][i].L << " " <<dp[last_night_day][i].probability << endl;
      if(abs(optimal_sleep_time - (dp[last_night_day][i].R+dp[last_night_day][i].L)/2.0) <= reference_diff){
	prob += dp[last_night_day][i].probability;
      }
    }
    printf("%lf\n",prob);
  }
}
