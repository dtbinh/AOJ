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
 

static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-10;

int dp[510][510];
int main(){
  int H,W;
  while(~scanf("%d %d",&H,&W)){
    if(H == 0 && W == 0) break;
    memset(dp,0,sizeof(dp));

    for(int y=0;y<H;y++){
      char line[505];
      scanf("%s",line);
      for(int x=0;x<W;x++){
	dp[y+1][x+1] = dp[y][x+1];
	if(line[x] == '.'){
	  dp[y+1][x+1]++;
	}
	else{
	  dp[y+1][x+1] = 0;
	}
      }
    }

    int res = 0;
    for(int y=0;y<H;y++){
      priority_queue<P> que;
      for(int x=0;x<=W;x++){
	int next = dp[y+1][x+1];
	int len = 0;
	while(!que.empty() && que.top().first >= next){
	  len += que.top().second;
	  res = max(res,len * que.top().first);
	  que.pop();
	}
	len++;
	que.push(P(next,len));
      }
    }
    printf("%d\n",res);
  }
}
