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

bool is_prime[1000001];
int stage[1101][1101];
int dp[1101][1101];

int main(){
  memset(stage,-1,sizeof(stage));
  int x = 0;
  int y = 0;
  int dir = 1;
  const int offset = 500;
  for(int round = 1; round <= 1000000;round++){
    stage[y+offset][x+offset] = round;

    int prev_dir = dir;
    if(round > 1) dir = (dir + 3) % 4;
    int dx = x + tx[dir];
    int dy = y + ty[dir];
    if(stage[dy+offset][dx+offset] != -1){
      dir = prev_dir;
    }
    dx = x + tx[dir];
    dy = y + ty[dir];
    x = dx;
    y = dy;
  }
  
  memset(is_prime,true,sizeof(is_prime));

  is_prime[0] = false;
  is_prime[1] = false;

  for(int i=2;i*i<=1000000;i++){
    if(is_prime[i]){
      for(int j=i+i;j<=1000000;j+=i){
	is_prime[j] = false;
      }
    }
  }

  int start,total_caves;
  while(~scanf("%d %d",&total_caves,&start)){
    if(total_caves == 0 && start == 0) break;

    int sx=0,sy=0;
    for(int y=0;y<=1000;y++){
      for(int x=0;x<=1000;x++){
	if(stage[y][x]  == start){
	  sx = x;
	  sy = y;
	  break;
	}
      }
    }

    memset(dp,-1,sizeof(dp));

    int res_prime=0;
    int res_count=0;

    dp[sy][sx] = (int)is_prime[stage[sy][sx]];
    if(is_prime[stage[sy][sx]]){
      res_prime = stage[sy][sx];
      res_count = 1;
    }

    for(int y=sy+1;y<=1000;y++){
      for(int x=0;x<=1000;x++){
	if(stage[y][x] == -1) continue;
	if(stage[y][x] > total_caves) continue;

	int cost = (int)is_prime[stage[y][x]];
	if(dp[y-1][x-1] != -1){
	  dp[y][x] = max(dp[y-1][x-1] + cost,dp[y][x]);
	}
	if(dp[y-1][x] != -1){
	  dp[y][x] = max(dp[y-1][x] + cost,dp[y][x]);
	}

	if(dp[y-1][x+1] != -1){
	  dp[y][x] = max(dp[y-1][x+1] + cost,dp[y][x]);
	}
      }
    }

    for(int y=sy+1;y<=1000;y++){
      for(int x=0;x<=1000;x++){
	if(res_count < dp[y][x]
	   && is_prime[stage[y][x]]){
	  res_count = dp[y][x];
	  res_prime = stage[y][x];
	}
	if(res_count == dp[y][x]
	   && is_prime[stage[y][x]]
	   && res_prime < stage[y][x]){
	  res_prime = stage[y][x];
	}
      }
    }
    printf("%d %d\n",res_count,res_prime);
  }
}
