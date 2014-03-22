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
map<P,int> stage;

void dfs(map<int,int>& dp,int total_caves,int sx,int sy,int count){
  if(is_prime[stage[P(sy,sx)]]){
    count++;
  }

  map<int,int>::iterator it = dp.find(stage[P(sy,sx)]);
  if(it != dp.end() && it->second >= count){
    return;
  }

  dp[stage[P(sy,sx)]] = count;

  for(int nx=-1;nx<=1;nx++){
    int dx = sx + nx;
    int dy = sy+1;
    if(stage.find(P(dy,dx)) == stage.end()) continue;
    if(stage[P(dy,dx)] > total_caves) continue;
    dfs(dp,total_caves,dx,dy,count);
  }
}

int main(){
  int x = 0;
  int y = 0;
  int dir = 1;
  for(int round = 1; round <= 1000000;round++){
    stage[P(y,x)] = round;

    int prev_dir = dir;
    if(round > 1) dir = (dir + 3) % 4;
    int dx = x + tx[dir];
    int dy = y + ty[dir];
    if(stage.find(P(dy,dx)) != stage.end()){
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
    map <int,int> dp;
    int sx=0,sy=0;
    for(map<P,int>::iterator it = stage.begin();
	it != stage.end();
	it++){
      int x = it->first.second;
      int y = it->first.first;
      int num = it->second;
      if(num == start){
	sx = x;
	sy = y;
	break;
      }
    }

    dfs(dp,total_caves,sx,sy,0);

    int res_prime=0;
    int res_count=0;
    for(map<int,int>::iterator it = dp.begin();
	it != dp.end();
	it++){
      if(!is_prime[it->first]) continue;

      if(res_count < it->second){
	res_count = it->second;
	res_prime = it->first;
      }
      if(res_count == it->second
	 && res_prime < it->first){
	res_prime = it->first;
      }
    }
    printf("%d %d\n",res_count,res_prime);
  }
}
