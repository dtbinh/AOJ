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
  int n,s;
  while(~scanf("%d %d",&n,&s)){
    int dp[10][1001];
    memset(dp,0,sizeof(dp));
    dp[0][0] = 1;
    for(int i=0;i<n;i++){
      for(int from=0;from<=s;from++){
	for(int num=0;num<=100;num++){
	  if(from+num > s) continue;
	  if(from == num) continue;
	  dp[i+1][from+num] += dp[i][from];
	}
      }
    }

    printf("%d\n",dp[n][s]);
  }
}
