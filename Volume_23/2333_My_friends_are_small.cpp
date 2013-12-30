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

int dp[201][10001];

int main(){
  int total_friends;
  int weight_limit;
  while(~scanf("%d %d",&total_friends,&weight_limit)){
    memset(dp,0,sizeof(dp));
    int friends[200];
    for(int friend_idx = 0; friend_idx < total_friends; friend_idx++){
      scanf("%d",friends + friend_idx);
    }
    
    for(int i=0;i<total_friends;i++){
      dp[i][0] = 1;
      for(int w = 0; w <= 10000; w++){
	if(w + friends[i] > 10000) continue;
	dp[i+1][w] += dp[i][w];
	dp[i+1][w + friends[i]] += dp[i][w];
      }
    }

    for(int w = 0; w <= 10000; w++){
      for(int i=0;i<=total_friends;i++){
	  if(dp[i][w] == 0) continue;
	  printf("i:%d w:%d %d\n",i,w,dp[i][w]);
      }
    }
  }
}
