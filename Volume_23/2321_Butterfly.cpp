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
 
const static int tx[] = {0,1,1,1,0,-1,-1,-1};
const static int ty[] = {-1,-1,0,1,1,1,0,-1};
 
static const double EPS = 1e-8;

int main(){
  int guy_num;
  while(~scanf("%d",guy_num)){
    
    int dp[(1<<22)];
    memset(dp,0,sizeof(dp));
    for(int i=0;i<guy_num;i++){
      int date_num,satisfaction_vol;
      scanf("%d %d",&date_num,&satisfaction_vol);
      int mask = 0;
      for(int j=0;j<date_num;j++){
	int begin,end;
	scanf("%d %d",&begin,&end);
	int tmp_mask = (1<<end) - 1;
	tmp_mask ^= (1<<begin) - 1;
	mask |= tmp_mask;
      }
      dp[mask] = max(dp[mask],satisfaction_vol);
    }
  }
}
