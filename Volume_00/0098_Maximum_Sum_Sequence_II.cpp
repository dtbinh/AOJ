#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#define MINF 0xc0c0c0c0

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
#include <assert.h>
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;
 
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};

static const double EPS = 1e-10;

int main(){
  int W;
  while(~scanf("%d",&W)){
    int H = W;
    int dp[102][102];
    memset(dp,0,sizeof(dp));

    for(int y = 0; y < H; y++){
      for(int x = 0; x < W; x++){
	int num;
	scanf("%d",&num);
	dp[y+1][x+1] = dp[y+1][x] + dp[y][x+1] - dp[y][x] + num;
      }
    }

    int res = MINF;
    for(int ly = 1; ly <= H; ly++){
      for(int lx = 1; lx <= W; lx++){
	for(int ry = ly; ry <= H; ry++){
	  for(int rx = lx; rx <= W; rx++){
	    int sum = dp[ry][rx] - dp[ry][lx-1] - dp[ly-1][rx] + dp[ly-1][lx-1];
	    res = max(sum,res);
	  }
	}
      }
    }

    printf("%d\n",res);
  }
}
