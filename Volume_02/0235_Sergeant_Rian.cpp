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
  
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};

int dp[20][1<<20];
int edges[20][20];

int main(){
  int N;
  while(~scanf("%d",&N)){
    if(N == 0) break;

    memset(edges,0x3f,sizeof(edges));
    for(int i=0;i<N-1;i++){
      int from,to,cost;
      scanf("%d %d %d",&from,&to,&cost);

      from--; to--;
      edges[from][to] = cost;
      edges[to][from] = cost;
    }

    memset(dp,0x3f,sizeof(dp));
    dp[0][(1<<0)] = 0;
    for(int S = 0; S < (1<<N); S++){
      for(int from=0;from < N; from++){
	if(!(S & (1<<from))) continue; 
	for(int to=0;to < N; to++){
	  if(S & (1<<to)) continue;
	  dp[to][S | (1<<to)] = min(dp[to][S | (1<<to)],
				    dp[from][S] + edges[from][to]);
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
