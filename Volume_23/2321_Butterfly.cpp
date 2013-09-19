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

class Data {
public:
  Data () : satisfaction_vol(0),mask(0) {}
  ll satisfaction_vol;
  int mask;
};

ll dp[101][1<<16];

int main(){
  int guy_num;
  while(~scanf("%d",&guy_num)){
    if(guy_num == 0) break;
    Data guy[100];

    memset(dp,0,sizeof(dp));

    for(int i=0;i<guy_num;i++){

      int date_num;
      ll satisfaction_vol;
      scanf("%d %lld",&date_num,&satisfaction_vol);
      int mask = 0;
      for(int j=0;j<date_num;j++){
    	int begin,end;
    	scanf("%d %d",&begin,&end);
	for(int k=begin-6;k<end-6;k++) mask |= (1<<k);
      }
      guy[i].mask = mask;
      guy[i].satisfaction_vol = satisfaction_vol;
    }

    for(int i=0;i<guy_num;i++){
      for(int S=0;S<=(1<<16)-1;S++){
	dp[i+1][S] = max(dp[i+1][S],dp[i][S]);
    	if((S & guy[i].mask) == 0){
    	  int next = S | guy[i].mask;
    	  dp[i+1][next] = max(dp[i+1][next],dp[i][S]+guy[i].satisfaction_vol);
    	}
      }
    }

    ll max_v = 0;
    for(int S=0;S<=(1<<16)-1;S++) max_v = max(dp[guy_num][S],max_v);
    printf("%lld\n",max_v);
  }
}
