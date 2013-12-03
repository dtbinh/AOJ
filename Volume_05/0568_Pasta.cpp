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

int total_days,total_predetermined_pastas;
int predetermined_pastas[101];
int dp[101][4][4];

int dfs(int day,int pasta,int successive){
  if(successive == 3) return 0;
  if(predetermined_pastas[day] != -1
     && predetermined_pastas[day] != pasta){
    return 0;
  }
  if(dp[day][pasta][successive] != -1){
    return dp[day][pasta][successive];
  }

  if(day >= total_days){
    return 1;
  }

  int res = 0;

  if(predetermined_pastas[day+1] != -1){
    if(predetermined_pastas[day+1] == pasta){
      res = dfs(day+1,predetermined_pastas[day+1],successive+1);
    }
    else{
      res = dfs(day+1,predetermined_pastas[day+1],1);
    }
  }
  else{
    for(int next = 1; next<=3; next++){
      if(next == pasta){
	res += dfs(day+1,next,successive+1);
      }
      else{
	res += dfs(day+1,next,1);
      }
    }
  }
  return dp[day][pasta][successive] = (res % 10000);
}

int main(){

  while(~scanf("%d %d",&total_days,&total_predetermined_pastas)){
    memset(predetermined_pastas,-1,sizeof(predetermined_pastas));
    for(int pasta_idx = 0; pasta_idx < total_predetermined_pastas; pasta_idx++){
      int day,type;
      scanf("%d %d",&day,&type);
      predetermined_pastas[day] = type;
    }

    memset(dp,-1,sizeof(dp));

    if(predetermined_pastas[1] == -1){
      printf("%d\n",(dfs(1,1,1)+dfs(1,2,1)+dfs(1,3,1)) % 10000);
    }
    else{
      printf("%d\n",dfs(1,predetermined_pastas[1],1));
    }
  }
}
