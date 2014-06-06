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

int main(){

  int total_stores,last_time,firework_time;

  while(~scanf("%d %d %d",&total_stores,&last_time,&firework_time)){
    int dp[3001];
    memset(dp,0,sizeof(dp));

    int fun[3001];
    int cost[3001];
    for(int store_idx = 0; store_idx < total_stores; store_idx++){
      scanf("%d %d",fun + store_idx,cost + store_idx);
    }

    for(int store_idx = 0; store_idx < total_stores; store_idx++){
      for(int time=last_time;time>=0;time--){
	if(time + cost[store_idx] > last_time) continue;
	if(time < firework_time && firework_time < time + cost[store_idx]) continue;
	dp[time + cost[store_idx]]
	  = max(dp[time + cost[store_idx]],dp[time] + fun[store_idx]);
      }
    }
    
    int res = 0;
    for(int time=0;time<=last_time;time++){
      res = max(res,dp[time]);
    }
    printf("%d\n",res);
  }
}
