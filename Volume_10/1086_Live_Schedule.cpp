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

using namespace std;

typedef long long ll;
typedef pair <int,int> P;

static const double EPS = 1e-8;

int main(){
  int total_regions;
  int total_live_days;
  int load_limit;
  int continuous_live_limit;
  while(~scanf("%d %d %d %d",
	       &total_regions,
	       &total_live_days,
	       &load_limit,
	       &continuous_live_limit)){
    if(total_live_days == 0) break;

    int benefits[16][31];
    for(int region=0;region<total_regions;region++){
      for(int day=0;day<total_live_days;day++){
	scanf("%d",&benefits[region][day] );
      }
    }
    int loads[16][31];
    for(int region=0;region<total_regions;region++){
      for(int day=0;day<total_live_days;day++){
	scanf("%d",&loads[region][day] );
      }
    }

    int dp[32][51][35]; //dp[day][load][count] := benefit
    memset(dp,0,sizeof(dp));
    for(int day=0;day<total_live_days;day++){
      for(int first_region=0;first_region<total_regions;first_region++){
	for(int last_region=first_region;last_region<total_regions;last_region++){
	  int load_sum = 0;
	  int benefit_sum = 0;
	  int continuous_live_count = 0;
	  for(int region=first_region;
	      region <= last_region;
	      region++){
	    load_sum += loads[region][day];
	    benefit_sum += benefits[region][day];
	    continuous_live_count++;
	  }
	  
	  if(continuous_live_count > 1){
	    for(int load=0;load<=load_limit;load++){	  
	      for(int c=0;c<=continuous_live_limit;c++){
		dp[day+1][load+load_sum][c+1]
		  = max(dp[day+1][load+load_sum][c+1],
			dp[day][load][c] + benefit_sum);
	      }
	    }
	  }
	  else if(continuous_live_count == 1){
	    for(int load=0;load<=load_limit;load++){	  
	      for(int c=0;c<=continuous_live_limit;c++){
		dp[day+1][load+load_sum][c]
		  = max(dp[day+1][load+load_sum][c],
			dp[day][load][c] + benefit_sum);
	      }
	    }
	  }
	}
      }
    }

    int res = 0;
    for(int day=0;day<=total_live_days;day++){
      for(int load=0;load<=load_limit;load++){
	for(int continuous_live_count=0;continuous_live_count<=continuous_live_limit;continuous_live_count++){
	  res = max(res,dp[day][load][continuous_live_count]);
	}
      }
    }
    printf("%d\n",res);
  } 
}
