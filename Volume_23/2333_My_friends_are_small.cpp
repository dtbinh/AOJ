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
 
static const double EPS = 1e-12;
static const int MOD = 1000000007;

int dp[201][10001];

int main(){
  int total_friends;
  int weight_limit;
  while(~scanf("%d %d",&total_friends,&weight_limit)){
    memset(dp,0,sizeof(dp));
    int friends[201];
    int remaining[201];
    memset(friends,0,sizeof(friends));
    memset(remaining,0,sizeof(remaining));
    for(int friend_idx = 0; friend_idx < total_friends; friend_idx++){
      scanf("%d",friends + friend_idx);
    }
    sort(friends,friends + total_friends,greater<int>());

    remaining[total_friends] = 0;
    for(int i=total_friends-1;i>=0;i--){
      remaining[i] = remaining[i+1] + friends[i];
    }

    dp[0][0] = 1;    
    for(int i=0;i<total_friends;i++){
      for(int w = 0; w <= 10000; w++){
	if(w + remaining[i] > weight_limit){
	  dp[i+1][w] += dp[i][w] % MOD;
	  dp[i+1][w] %= MOD;
	}

	if(w + friends[i] > 10000) continue;
	dp[i+1][w + friends[i]] += dp[i][w] % MOD;
	dp[i+1][w + friends[i]] %= MOD;
      }
    }

    int res = 0;
    for(int w = 0; w<= weight_limit; w++){
      res += dp[total_friends][w] % MOD;
      res %= MOD;
    }
    printf("%d\n",res);
  }
}
