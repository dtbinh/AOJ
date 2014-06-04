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
#include <complex>
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;
 
static const double EPS = 1e-10;

int stage[101][101];
int dp[101][101];

P move(int x,int y){
  if(stage[y][x] == 0){
    return P(x,y);
  }

  else if(stage[y][x] == 1
	  && stage[y][x+1] == 1){
    return move(x+1,y);
  }
  else if(stage[y][x] == 1
	  && stage[y][x+1] != 1){
    return P(x,y);
  }
  else if(stage[y][x] == 2){
    return move(x-1,y);
  }

  else{
    return P(-1,-1);
  }
}

void dfs(int sx,int sy,int cost,int n){
  for(int tx=0; tx <= 2; tx++){
    int dx = sx + tx;
    int dy = (sy + 1) % 2;

    if(dx < 0 || dx >= n || dy < 0 || dy >= 2) continue;

    P p = move(dx,dy);

    if(p.first < 0 || p.first >= n) continue;
    if(p.second < 0 || p.second >= 2) continue;
    if(dp[p.first][p.second] <= cost + 1){
      continue;
    }
    dp[p.first][p.second] = cost + 1;
    dfs(p.first,p.second,cost + 1,n);
  }
}

int main(){
  int n;
  while(~scanf("%d",&n)){
    if(n == 0) break;

    memset(dp,0x3f,sizeof(dp));
    memset(stage,0,sizeof(stage));
    for(int y=0;y<2;y++){
      for(int x=0;x<n;x++){
	scanf("%d",&stage[y][x]);
      }
    }

    P init_lhs = move(0,0);
    P init_rhs = move(0,1);
    dp[init_lhs.first][init_lhs.second] = 0;
    dp[init_rhs.first][init_rhs.second] = 0;

    dfs(init_lhs.first,init_lhs.second,0,n);
    dfs(init_rhs.first,init_rhs.second,0,n);

    if((dp[n-1][0] != INF) || (dp[n-1][1] != INF)){
      printf("%d\n",min(dp[n-1][0],dp[n-1][1]));
    }
    else{
      printf("NA\n");
    }
  }
}
