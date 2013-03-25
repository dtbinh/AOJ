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

int ComputeCost(int stage[20][20],int dst,int visited,int N){
  int res = stage[dst][0];
  for(int i=0;i<N;i++){
    if(visited & (1<<i)){
      res = min(stage[dst][i+1],res);
    }
  }
  return res;
}
int main(){
  int N;
  while(~scanf("%d",&N)){
    if(N==0) break;
    int stage[20][20];//[N][N+1]
    for(int y=0;y<N;y++){
      for(int x=0;x<N+1;x++){
	int num;
	scanf("%d",&num);
	stage[y][x] = num;
      }
    }

    int dp[16][1<<16];
    memset(dp,0x3f,sizeof(dp));
    //init dp
    for(int i=0;i<N;i++){
      int got = (1 << i);
      dp[i][got] = stage[i][0];
    }

    for(int visited = 1;visited <= (1<<N) -1; visited++){
      for(int from = 0; from < N; from++){
	for(int to = 0; to < N; to++){
	  if(!(visited & (1<<from))) continue;
	  if(visited & (1<<to)) continue;
	  int cost = ComputeCost(stage,to,visited,N);
	  // printf("cost:%d\n",cost);
	  dp[to][visited | (1<<to)] 
	    = min(dp[to][visited | (1<<to)],dp[from][visited] + cost);
	}
      }
    }

    int res = INF;
    for(int i=0;i<N;i++){
      res = min(dp[i][(1<<N)-1],res);
    }
    printf("%d\n",res);
  }
}
