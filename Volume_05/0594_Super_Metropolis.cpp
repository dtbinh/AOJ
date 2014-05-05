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

int main(){
  int W,H,N;
  while(~scanf("%d %d %d",&W,&H,&N)){
    int res = 0;
    int sx,sy;
    scanf("%d %d",&sx,&sy);

    for(int i=1;i<N;i++){
      int x,y;
      scanf("%d %d",&x,&y);
      int diff_x = x - sx;
      int diff_y = y - sy;

      if((diff_x <= 0 && diff_y >= 0)
	 || ((diff_x >= 0 && diff_y <= 0))){
	res += abs(diff_x) + abs(diff_y);
      }
      else{
	int abs_diff_x = abs(diff_x);
	int abs_diff_y = abs(diff_y);
	int min_diff = min(abs_diff_x,abs_diff_y);
	res += min_diff;
	abs_diff_x -= min_diff;
	abs_diff_y -= min_diff;
	res += max(abs_diff_x,abs_diff_y);
      }
      sx = x;
      sy = y;

    }
    printf("%d\n",res);
  }
}
