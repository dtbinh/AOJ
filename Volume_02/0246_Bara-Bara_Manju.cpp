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
typedef pair <int,P> PP;
 
static const int tx[] = {+0,+1,+0,-1};
static const int ty[] = {-1,+0,+1,+0};
 
static const double EPS = 1e-8;

int main(){
  int total_buns;
  while(~scanf("%d",&total_buns)){
    if(total_buns == 0) break;

    vector<int> buns;
    for(int i = 0; i < total_buns; i++){
      int weight;
      scanf("%d",&weight);
      buns.push_back(weight);
    }
    sort(buns.begin(),buns.end());
    int dp[11];
    memset(dp,0,sizeof(dp));
    dp[0] = 1;
    for(int i = 0; i < buns.size(); i++){
      for(int prev = 10; prev >= 0; prev--){
	if(prev + buns[i] > 10) continue;
	dp[prev + buns[i]] += dp[prev];
      }
    }
    for(int i = 0; i <= 10; i++){
      printf("%d: %d\n",i,dp[i]);
    }
  }
}
