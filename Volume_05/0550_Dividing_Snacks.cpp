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

int dp[2][10001][2];

int main(){
  int N;
  while(~scanf("%d",&N)){
    vector<int> costs;
    for(int i = 0; i < N - 1; i++){
      int cost;
      scanf("%d",&cost);
      costs.push_back(cost);
    }

    memset(dp,0x3f,sizeof(dp));
    dp[0][0][0] = 0;
    for(int pos = 0; pos < N; pos++){
      for(int num_of_zero = pos; num_of_zero >= 0; num_of_zero--){
	dp[(pos+1) % 2][num_of_zero+1][0]
	  = min(dp[pos % 2][num_of_zero][0],dp[pos % 2][num_of_zero][1] + costs[pos]);
	dp[(pos+1) % 2][num_of_zero][1]
	  = min(dp[pos % 2][num_of_zero][1],dp[pos % 2][num_of_zero][0] + costs[pos]);
      }
      memset(dp[pos % 2],0x3f,sizeof(dp[pos % 2]));
    }
    printf("%d\n",dp[N % 2][N / 2][0]);
    break;
  }
}
