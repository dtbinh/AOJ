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

int main(){
  int total_nights;
  int R,L;
  int dp[31][13][13]; //dp[day][R][L] := probability
  
  while(~scanf("%d %d %d",&total_nights,&R,&L)){
    memset(dp,0,sizeof(dp));
    dp[0][R][L] = 1.0;

    double mistake_probability,reference_diff,optimal_sleep_time;
    scanf("%lf %lf %lf",&mistake_probability,&reference_diff,&optimal_sleep_time);
    for(int day=1;day<=total_nights;day++){
      for(int R=0;R<=12;R++){
	for(int L=0;L<=12;L++){
	  int H = (R+L)/2;
	  if(H >= optimal_sleep_time){
	    int correct_next_L = H;
	    dp[day][R][correct_next_L] += dp[day-1][R][L] * (1.0-mistake_probability);

	    int wrong_next_R = H;
	    dp[day][wrong_next_R][L] += dp[day-1][R][L] * mistake_probability;
	  }
	  else{
	    int correct_next_R = H;
	    dp[day][correct_next_R][L] += dp[day-1][R][L] * (1.0-mistake_probability);

	    int wrong_next_L = H;
	    dp[day][R][wrong_next_L] += dp[day-1][R][L] * mistake_probability;
	  }
	}
      }
    }

    
    int last_night_day = total_nights;

    double prob = 0.0;
    for(int R=0;R<=12;R++){
      for(int L=0;L<=12;L++){
	if(abs(optimal_sleep_time - (R+L)/2) <= reference_diff){
	  prob += dp[last_night_day][R][L];
	}
      }
    }
    
    printf("%lf\n",prob);
  }
}
