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

int dp[31][1<<16];

int main(){
  int total_light_patterns;
  int total_techniques;
  while(~scanf("%d %d",&total_light_patterns,&total_techniques)){
    if(total_light_patterns == 0
       && total_techniques == 0) break;

    vector<int> light_patterns;
    for(int light_idx=0;light_idx<total_light_patterns;light_idx++){
      int bits = 0;
      for(int j=0;j<16;j++){
	int is_light;
	scanf("%d",&is_light);
	if(is_light > 0) bits |= (1<<j);
      }
      light_patterns.push_back(bits);
    }
    vector<int> techniques;
    for(int tech_idx=0;tech_idx<total_techniques;tech_idx++){
      int bits = 0;
      for(int j=0;j<16;j++){
	int is_light;
	scanf("%d",&is_light);
	if(is_light > 0) bits |= (1<<j);
      }
      techniques.push_back(bits);
    }

    memset(dp,-1,sizeof(dp));
    dp[0][0] = 0;
    for(int light_idx=0;light_idx<total_light_patterns;light_idx++){
      for(int prev=0;prev<=(1<<16)-1;prev++){
	if(dp[light_idx][prev] == -1) continue;
	int next = (prev | light_patterns[light_idx]);
	for(int tech_idx=0;tech_idx<total_techniques;tech_idx++){
	  dp[light_idx+1][next ^ (next & techniques[tech_idx])]
	    = max(dp[light_idx][prev] + __builtin_popcount(next & techniques[tech_idx]),
		  dp[light_idx + 1][next ^ (next & techniques[tech_idx])]);
	}
      }
    }

    int res = 0;
    for(int S=0;S<=(1<<16)-1;S++){
      res = max(res,dp[total_light_patterns][S]);
    }
    printf("%d\n",res);
  }
}
