#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#define MINF 0xc0c0c0c0
 
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

int compute_optimal_swing(int level2_satisfaction,
			  int level1_satisfaction,
			  int none_satisfaction,
			  int level2_remaining,
			  int level1_remaining
){
  int res = none_satisfaction;
  for(int use_level2 = 0; use_level2 <= level2_remaining; use_level2++){
    for(int use_level1 = 0; use_level1 <= level1_remaining; use_level1++){
      if(use_level2 + use_level1 > 8) continue;
      res = max(level2_satisfaction * use_level2
		+ level1_satisfaction * use_level1,res);
    }
  }
  return res;
}

int main(){
  int total_songs;
  int cyalume;
  while(~scanf("%d %d",
	       &total_songs,
	       &cyalume)){

    int dp[51][51]; //next accumulate
    memset(dp,0xc0,sizeof(dp));
    dp[0][0] = 0;

    int res = MINF;
    for(int song_idx=0;song_idx < total_songs;song_idx++){
      int level2_satisfaction,level1_satisfaction,none_satisfaction;
      scanf("%d %d %d",
	    &level2_satisfaction,
	    &level1_satisfaction,
	    &none_satisfaction);

      int next_dp[51][51];
      memset(next_dp,0xc0,sizeof(next_dp));
      
      for(int accumulate=cyalume;accumulate>=0;accumulate--){
	for(int prev=0;prev<=cyalume;prev++){
	  if(prev > accumulate) continue;

	  for(int next=0;next<=cyalume;next++){
	    if(dp[prev][accumulate - next] < -100000000) continue;
	    if(accumulate - next < 0) continue;

	    next_dp[next][accumulate] 
	      = max(dp[prev][accumulate - next]
		    + compute_optimal_swing(level2_satisfaction,
					    level1_satisfaction,
					    none_satisfaction,
					    next,prev),
		    next_dp[next][accumulate]);

	    if(song_idx == total_songs - 1){
	      res = max(res,next_dp[next][accumulate]);
	    }
	  }
	}
      }
      
      memcpy(dp,next_dp,sizeof(int)*51*51);
    }

    printf("%d\n",res);
  }
}
