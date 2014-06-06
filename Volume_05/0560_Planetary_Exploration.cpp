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

struct Field{
  int numJ;
  int numO;
  int numI;
  Field() : numJ(0), numO(0), numI(0) {}

};

Field dp[1001][1001];
int main(){
  int W,H;
  while(~scanf("%d %d",&H,&W)){
    int total_queries;
    scanf("%d",&total_queries);
    for(int y=0;y<H;y++){
      char line[1001];
      scanf("%s",line);
      for(int x=0;x<W;x++){
	if(x-1 >= 0) dp[y][x] = dp[y][x-1];
	if(line[x] == 'J') dp[y][x].numJ = (x-1 >= 0 ? dp[y][x-1].numJ + 1 : 1);
	else if(line[x] == 'O') dp[y][x].numO = (x-1 >= 0 ? dp[y][x-1].numO + 1 : 1);
	else if(line[x] == 'I') dp[y][x].numI = (x-1 >= 0 ? dp[y][x-1].numI + 1 : 1);
      }
    }

    for(int query_idx = 0; query_idx < total_queries; query_idx++){
      int lx,ly,rx,ry;
      scanf("%d %d %d %d",&ly,&lx,&ry,&rx);
      ly--; lx--; 
      ry--; rx--; 

      int numJ = 0;
      int numO = 0;
      int numI = 0;
      for(int y=ly;y<=ry;y++){
	numJ += dp[y][rx].numJ - (lx - 1 >= 0 ? dp[y][lx-1].numJ : 0);
	numO += dp[y][rx].numO - (lx - 1 >= 0 ? dp[y][lx-1].numO : 0);
	numI += dp[y][rx].numI - (lx - 1 >= 0 ? dp[y][lx-1].numI : 0);
      }
      printf("%d %d %d\n",numJ,numO,numI);
    }
  }
}
