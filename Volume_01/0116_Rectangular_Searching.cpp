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
      char line[501];
      scanf("%s",line);
      for(int x=0;x<W;x++){
	dp[y+1][x+1] = dp[y][x+1] + dp[y+1][x] - dp[y][x];
	if(line[x] == '.'){
	  dp[y+1][x+1]++;
	}
      }
    }

    int res = 0;
    for(int ly=1;ly<=H;ly++){
      for(int lx=1;lx<=W;lx++){
	for(int ry=ly;ry<=H;ry++){
	  for(int rx=lx;rx<=W;rx++){
	    int count = dp[ry][rx] - dp[ly-1][rx] - dp[ry][lx-1] + dp[ly-1][lx-1];
	    if(count == (ry - ly + 1) * (rx - lx + 1)){
	      res = max(count,res);
	    }
	  }
	}
      }
    }

    printf("%d\n",res);
  }
}
