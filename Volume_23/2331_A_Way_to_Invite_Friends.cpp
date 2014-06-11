#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
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
  int N;
  while(~scanf("%d",&N)){
    int dp[100100];
    memset(dp,0,sizeof(dp));

    for(int i=0;i<N;i++){
      int lower,upper;
      scanf("%d %d",&lower,&upper);
      dp[lower - 1]++;
      dp[upper]--;
    }

    int res = 0;
    int sum = 0;
    for(int participants=0;participants<=100001;participants++){
      sum += dp[participants];
      if(sum >= participants) res = participants;
    }
    printf("%d\n",res);
  }
}
