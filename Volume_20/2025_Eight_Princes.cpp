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
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

ll nCr(int n,int r){
 return (r==0 || n==r) ? 1 : nCr(n-1,r) + nCr(n-1,r-1);
}

ll fact(ll n)
{
  return (n <= 1 ? 1 : n * fact(n-1));
}

ll dp[10][101][2][2];
ll seats;

ll dfs(int used,int pos,int current,int next){
  if(used >= 8) return 1;
  if(pos >= seats/2) return 0;
  if(dp[used][pos][current][next] != -1){
    return dp[used][pos][current][next];
  }

  ll res = 0;
  res += dfs(used,pos+1,0,0);
  if(current == 0) res += dfs(used+1,pos+1,1,0);
  if(next == 0 && pos + 1 < seats/2) res += dfs(used+1,pos+1,0,1);
  return (dp[used][pos][current][next] = res);
}

int main(){
  while(~scanf("%lld",&seats)){
    if(seats == 0) break;

    if(seats % 2 != 0){
      memset(dp,-1,sizeof(dp));
      printf("%lld\n",dfs(1,0,1,0) * seats * fact(8 - 1));
    }
    else{
      if(seats <= 16){
	printf("%lld\n",0);
      }
      else{
	printf("%lld\n",seats * nCr(seats/2,8) * fact(8 - 1));
      }
    }
  }
}
