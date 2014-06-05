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
  
static const double EPS = 1e-8;
  
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};

int direction[1001][1001];
int dp[1001][1001];

int main(){
  int H,W,n;
  while(~scanf("%d %d %d",&H,&W,&n)){
    if(H == 0 && W == 0) break;

    memset(direction,0,sizeof(direction));
    memset(dp,0,sizeof(dp));

    for(int y=0;y<H;y++){
      for(int x=0;x<W;x++){
	scanf("%d",&direction[y][x]);
      }
    }
    
    dp[0][0] = n-1; //offset
    for(int y=0;y<H;y++){
      for(int x=0;x<W;x++){
	//dir
	//0 v
	//1 ->
	if(y+1 < H) dp[y+1][x] += (dp[y][x] + (direction[y][x] == 0 ? 1:0)) / 2;
	if(x+1 < W) dp[y][x+1] += (dp[y][x] + (direction[y][x] == 1 ? 1:0)) / 2;
      }
    }
    
    int x = 0;
    int y = 0;
    while(y < H && x < W){
      if((dp[y][x] + direction[y][x]) % 2 == 0) y++;
      else if((dp[y][x] % 2 + direction[y][x]) % 2 == 1) x++;
    }
    printf("%d %d\n",y+1,x+1);
  }
}
