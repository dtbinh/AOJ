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

ll compute_euler_phi(int n){

  ll res = n;
  for(int i=2;i*i<=n;i++){
    if(n % i == 0){
      res = res / i * (i - 1);
      while(n % i == 0){
	n /= i;
      }
    }
  }

  if(n != 1) res = res / n * (n - 1);
  return res;
}

ll dp[1000005];

int main(){
  int total_queries;

  memset(dp,0,sizeof(dp));
  for(int i=0;i<=1000000;i++){
    dp[i+1] = dp[i] + compute_euler_phi(i+1);
  }
  while(~scanf("%d",&total_queries)){
    for(int query_idx=0;query_idx<total_queries;query_idx++){
      int n;
      scanf("%d",&n);
      printf("%lld\n",dp[n] + 1);
    }
  }
}
