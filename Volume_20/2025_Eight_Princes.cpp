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

ll _nCr[300][300];
ll nCr(int n,int r){
  if(_nCr[n][r] != -1) return _nCr[n][r];
  return (r==0 || n==r) ? 1 : (_nCr[n][r] = nCr(n-1,r) + nCr(n-1,r-1));
}

ll _fact[300];

ll fact(ll n)
{
  if(_fact[n] != -1) return _fact[n];
  return (n <= 1 ? 1 : (_fact[n] = n * fact(n-1)));
}

struct Comparer {
  bool operator() (const bitset<71> &b1, const bitset<71> &b2) const {
    return b1.to_ulong() < b2.to_ulong();
  }
};

ll dp[101][10][2][2];
ll seats;

ll dfs(int pos,int used,bool here,bool opposite){
  if(used >= 8) return 1;
  if(pos >= seats/2) return 0;
  if(dp[pos][used][here][opposite] != -1) return dp[pos][used][here][opposite];
  if(pos + 1 == seats/2) here = false;

  ll res = 0;
  res += dfs(pos+1,used,true,true);
  if(here) res += dfs(pos+1,used + 1,false,true);
  if(opposite) res += dfs(pos+1,used + 1,true,false);

  return (dp[pos][used][here][opposite] = res);
}

int main(){

  memset(_nCr,-1,sizeof(_nCr));
  memset(_fact,-1,sizeof(_fact));
  while(~scanf("%lld",&seats)){
    if(seats == 0) break;

    if(seats <= 16){
      printf("%d\n",0);
    }
    else if(seats % 2 != 0){
      printf("%lld\n",seats * nCr(seats - 9,7) * fact(7));
    }
    else{
      memset(dp,-1,sizeof(dp));
      printf("%lld\n",seats * dfs(1,1,false,true) * fact(7));
    }
  }
}
