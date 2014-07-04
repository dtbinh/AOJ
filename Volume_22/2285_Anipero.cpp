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
 
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

// dp[picked secret][picked standard][money] ::= max satisfaction
int dp[3][105][1005]; 

int main(){
  int money_limit;
  int total_secret_artists;
  int total_standard_artists;
  int to_pick_standard_artists;
  while(~scanf("%d %d %d %d",
	       &money_limit,
	       &total_secret_artists,
	       &total_standard_artists,
	       &to_pick_standard_artists)){
    
    if(money_limit == 0
       && total_secret_artists == 0
       && total_standard_artists == 0
       && to_pick_standard_artists == 0) break;

    memset(dp,-1,sizeof(dp));
    dp[0][0][0] = 0;
    for(int artist_idx=0;artist_idx<total_secret_artists;artist_idx++){
      string name;
      int cost;
      int satisfaction;

      cin >> name >> cost >> satisfaction;
      for(int prev_picked=1;prev_picked>=0;prev_picked--){
	for(int prev_money=1000;prev_money>=0;prev_money--){
	  if(prev_money + cost > 1000) continue;

	  if(dp[prev_picked][0][prev_money] == -1) continue;
	  dp[prev_picked + 1][0][prev_money + cost]
	    = max(dp[prev_picked][0][prev_money] + satisfaction,
		  dp[prev_picked + 1][0][prev_money + cost]);
	}
      }
    }
    for(int artist_idx=0;artist_idx<total_standard_artists;artist_idx++){
      string name;
      int cost;
      int satisfaction;
      cin >> name >> cost >> satisfaction;
      for(int picked_secret=min(2,total_secret_artists);picked_secret>=1;picked_secret--){
	for(int prev_picked_standard = artist_idx; prev_picked_standard  >= 0; prev_picked_standard--){
	  for(int prev_money=1000;prev_money>=0;prev_money--){
	  if(prev_money + cost > 1000) continue;

	  if(dp[picked_secret][prev_picked_standard][prev_money] == -1) continue;
	  dp[picked_secret][prev_picked_standard + 1][prev_money + cost]
	    = max(dp[picked_secret][prev_picked_standard + 1][prev_money + cost],
		  dp[picked_secret][prev_picked_standard][prev_money] + satisfaction);
	  }

	}
      }	
    }

    int res = 0;
    for(int picked_secret=min(2,total_secret_artists);picked_secret>=1;picked_secret--){
      for(int picked_standard = total_standard_artists; picked_standard  >=to_pick_standard_artists; picked_standard--){
	for(int money=money_limit;money>=0;money--){
	  res = max(dp[picked_secret][picked_standard][money],res);
	}
      }
    }

    printf("%d\n",res);
  }
}
