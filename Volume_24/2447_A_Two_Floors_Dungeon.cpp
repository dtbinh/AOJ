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

int W,H;
char stage[51][51];
char switches[11][51][51];
int dp[1<<10][51][51][2];

int detect_floor(int S,int dx,int dy){
  int floor;
  if('a' <= stage[dy][dx] && stage[dy][dx] <= 'z'
     || stage[dy][dx] == '_'
     || stage[dy][dx] == '&'
     || stage[dy][dx] == '%'){
    floor = 0;
  }
  else if('A' <= stage[dy][dx] && stage[dy][dx] <= 'Z'
     || stage[dy][dx] == '^'){
    floor = 1;
  }

  for(int switch_i = 0; switch_i < 10; switch_i++){
    if((S & (1<<switch_i)) && switches[switch_i][dy][dx] == '*'){
      floor++;
      floor %= 2;
    }
  }
  return floor;
}

int alpha2idx(char alpha){
  if('A' <= alpha && alpha <= 'Z'){
    return alpha - 'A';
  }
  return alpha - 'a';
}

int dfs(int S,int sx,int sy,int floor,int cost){
  for(int i = 0; i < 4; i++){
    int dx = sx + tx[i];
    int dy = sy + ty[i];
    if(dx < 0 || dx >= W || dy < 0 || dy >= H) continue;
    if(stage[dy][dx] != '|' && detect_floor(S,dx,dy) != floor) continue;
    if(stage[dy][dx] == '#') continue;
    int next_floor = floor;
    int next_S = S;
    if(isalpha(stage[dy][dx])){
      //use switch
      next_floor++;
      next_floor %= 2;

      int switch_i = alpha2idx(stage[dy][dx]);
      if(S & (1<<switch_i)){
	next_S &= ~(1<<switch_i);
      }
      else{
	next_S |= (1<<switch_i);
      }
      if(dp[next_S][dx][dy][next_floor] > cost + 1){
	dp[next_S][dx][dy][next_floor] = cost + 1;
	dfs(next_S,dx,dy,next_floor,cost + 1);
      }

      //don't use switch
      if(dp[S][dx][dy][floor] > cost + 1){
      	dp[S][dx][dy][floor] = cost + 1;
      	dfs(S,dx,dy,floor,cost + 1);
      }
    }
    else{
      if(stage[dy][dx] == '|'){
	next_floor++;
	next_floor %= 2;
	if(dp[S][dx][dy][next_floor] > cost + 1){
	  dp[S][dx][dy][next_floor] = cost + 1;
	  dfs(S,dx,dy,next_floor,cost + 1);
	}
      }
      if(dp[S][dx][dy][floor] > cost + 1){
	dp[S][dx][dy][floor] = cost + 1;
	dfs(S,dx,dy,floor,cost + 1);
      }
    }
  }
}

int main(){
  while(~scanf("%d %d",&W,&H)){
    memset(dp,0x3f,sizeof(dp));
    int sx,sy;
    int gx,gy;
    for(int y = 0; y < H; y++){
      char line[64];
      scanf("%s",line);
      for(int x = 0; x < W; x++){
	stage[y][x] = line[x];
	if(stage[y][x] == '%'){
	  sx = x;
	  sy = y;
	}
	if(stage[y][x] == '&'){
	  gx = x;
	  gy = y;
	}
      }
    }
    int total_switches;
    scanf("%d",&total_switches);
    for(int switch_i = 0; switch_i < total_switches; switch_i++){
      for(int y = 0; y < H; y++){
	char line[64];
	scanf("%s",line);
	for(int x = 0; x < W; x++){
	  switches[switch_i][y][x] = line[x];
	}
      }
    }
    dfs(0,sx,sy,0,0);
    int res = INF;
    for(int S = 0; S < (1<<total_switches); S++){
      for(int floor = 0; floor < 2; floor++){
	res = min(dp[S][gx][gy][floor],res);
      }
    }
    printf("%d\n",res);
  }
}
