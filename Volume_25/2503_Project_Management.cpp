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
  
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};

int dp[401];
int path[401][401];

void dfs(int pos,int cost,int node_num){
  for(int to=0;to<=node_num;to++){
    if(path[pos][to] == 0) continue;
    if(dp[to] >= cost + path[pos][to]) continue;

    dp[to] = cost + path[pos][to];

    dfs(to,cost+path[pos][to],node_num);
  }
}

int main(){
  int node_num,work_num;
  while(~scanf("%d %d",&node_num,&work_num)){
    memset(dp,0,sizeof(dp));
    memset(path,0,sizeof(path));

    for(int i=0;i<work_num;i++){
      int from,to,cost;
      scanf("%d %d %d",&from,&to,&cost);
      path[from][to] = max(path[from][to],cost);
    }

    dfs(0,0,node_num);
    printf("%d\n",dp[node_num-1]);
  }
}
