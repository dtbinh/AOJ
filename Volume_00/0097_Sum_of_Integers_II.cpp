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


int main(){
  ll dp[10][1001];
  memset(dp,0,sizeof(dp));
  dp[0][0] = 1;
  for(int num=0;num<=100;num++){
    for(int i=9;i>0;i--){
      for(int to=1000;to-num>=0;to--){
	dp[i][to] += dp[i-1][to-num];
      }
    }
  }

  int n,s;
  while(~scanf("%d %d",&n,&s)){
    if(n==0 && s==0) break;
    printf("%lld\n",dp[n][s]);
  }
}
