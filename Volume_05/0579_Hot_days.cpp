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

class Wear{
public:
  int lower_temperature;
  int upper_temperature;
  int gaudiness;
  Wear(int _l,int _u, int _g)
    : lower_temperature(_l),upper_temperature(_u),gaudiness(_g) {}
  Wear() : lower_temperature(0),upper_temperature(0),gaudiness(0){}
};

int main(){
  int total_days;
  int total_wears;
  while(~scanf("%d %d",&total_days,&total_wears)){

    int temperatures[201];
    for(int day=0;day<total_days;day++){
      scanf("%d",temperatures+day);
    }

    Wear wears[201];
    for(int wear_idx=0;wear_idx<total_wears;wear_idx++){
      int lower_temperature,upper_temperature;
      int gaudiness;
      scanf("%d %d %d",&lower_temperature,&upper_temperature,&gaudiness);
      wears[wear_idx] = Wear(lower_temperature,upper_temperature,gaudiness);
    }

    int dp[201][201];
    memset(dp,0,sizeof(dp));

    for(int day = 0; day<total_days; day++){
      for(int from_idx = 0; from_idx < total_wears; from_idx++){
	for(int to_idx = 0; to_idx < total_wears; to_idx++){
	  if(day+1 < total_days
	     && (temperatures[day+1] < wears[to_idx].lower_temperature
		 || wears[to_idx].upper_temperature < temperatures[day+1])) continue;
	  
	  if(temperatures[day] < wears[from_idx].lower_temperature
	     || wears[from_idx].upper_temperature < temperatures[day]) continue;

	  int from = wears[from_idx].gaudiness;
	  int to = wears[to_idx].gaudiness;
	  dp[day+1][to_idx] = max(dp[day+1][to_idx],
				  dp[day][from_idx] + abs(from-to));
	}
      }
    }

    int res = 0;
    for(int wear_idx=0;wear_idx < total_wears;wear_idx++){
      res = max(res,dp[total_days-1][wear_idx]);
    }
    printf("%d\n",res);
  }
}
