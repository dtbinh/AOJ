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
int dp[3][101][1001]; 

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
    
    memset(dp,0,sizeof(dp));
    for(int i=0;i<total_secret_artists;i++){
      string name;
      int cost;
      int satisfaction;

      cin >> name >> cost >> satisfaction;
      for(int prev_picked=1;prev_picked>=0;prev_picked--){
	for(int prev_money=1000;prev_money>=0;prev_money--){
	  dp[prev_picked + 1][0][prev_money + cost]
	    = max(dp[prev_picked][0][prev_money],
		  dp[prev_picked + 1][0][prev_money + cost]);
	}
      }
    }
    for(int i=0;i<total_standard_artists;i++){
      string name;
      int cost;
      int satisfaction;
      cin >> name >> cost >> satisfaction;
      for(int picked_secret=2;picked_secret>=0;picked_secret--){
	for(int prev_picked_standard = 100; prev_picked_standard  >= 0; prev_picked_standard--){
	  for(int prev_money=1000;prev_money>=0;prev_money--){
	    dp[picked_secret][prev_picked_standard + 1][prev_money + cost]
	      = max(dp[picked_secret][prev_picked_standard + 1][prev_money + cost],
		    dp[picked_secret][prev_picked_standard][prev_money]);
	  }
	}
      }	
    }

    int res = 0;
    for(int picked_secret=2;picked_secret>=0;picked_secret--){
      for(int picked_standard = 100; picked_standard  >= 0; picked_standard--){
	for(int money=money_limit;money>=0;money--){
	  res = max(dp[picked_secret][picked_standard][money],res);
	}
      }
    }

    printf("%d\n",res);
  }
}
