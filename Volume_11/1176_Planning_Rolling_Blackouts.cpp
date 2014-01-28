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

int area[33][33][33][33];
pair<int,int> dp[33][33][33][33];
int H,W,provided_power;

pair<int,int> dfs(int lx,int ly,int rx,int ry){
  if(dp[lx][ly][rx][ry].first != -1) return dp[lx][ly][rx][ry];

  if(area[0][0][W-1][H-1] - area[lx][ly][rx][ry] > provided_power){
    dp[lx][ly][rx][ry].first = 0;
    return dp[lx][ly][rx][ry];
  }

  int diff = abs((area[0][0][W-1][H-1] - area[lx][ly][rx][ry]) - provided_power);
  pair<int,int> res(1,diff);
  for(int x=lx;x+1<=rx;x++){
    pair<int,int> left = dfs(lx,ly,x,ry);
    pair<int,int> right = dfs(x+1,ly,rx,ry);

    if(left.first > 0 && right.first > 0){
      pair<int,int> tmp = make_pair(left.first + right.first,min(left.second,right.second));
      res = max(tmp,res);
    }
  }

  for(int y=ly;y+1<=ry;y++){
    pair<int,int> upper = dfs(lx,ly,rx,y);
    pair<int,int> lower = dfs(lx,y+1,rx,ry);
    if(upper.first > 0 && lower.first > 0){
      pair<int,int> tmp = make_pair(upper.first + lower.first,min(upper.second,lower.second));
      res = max(tmp,res);
    }
  }

  return (dp[lx][ly][rx][ry] = res);
}

int main(){
  while(~scanf("%d %d %d",&H,&W,&provided_power)){
    if(H==0 && W==0 && provided_power == 0) break;
    int stage[33][33];
    for(int y=0;y<H;y++){
      for(int x=0;x<W;x++){
	int needs;
	scanf("%d",&needs);
	stage[y][x] = needs;
      }
    }

    //compute area
    memset(area,0,sizeof(area));
    for(int ly=0;ly<H;ly++){
      for(int lx=0;lx<W;lx++){
	for(int ry=0;ry<H;ry++){
	  for(int rx=0;rx<W;rx++){
	    int sum = 0;
	    for(int y=ly;y<=ry;y++){
	      for(int x=lx;x<=rx;x++){
		sum += stage[y][x];
	      }
	    }
	    //init dp
	    dp[lx][ly][rx][ry].first = -1;
	    dp[lx][ly][rx][ry].second = INF;

	    area[lx][ly][rx][ry] = sum;
	  }
	}
      }
    }

    pair<int,int> res = dfs(0,0,W-1,H-1);
    printf("%d %d\n",res.first,res.second);
  }
}
