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
 
const static int tx[] = {0,1,0,-1};
const static int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

int main(){
  int N,T,L,B;

  while(~scanf("%d %d %d %d",&N,&T,&L,&B)){
    if(N==0) break;
    char stage[101];
    double dp[101][101][2] = {0.0};

    memset(stage,'.',sizeof(stage));

    for(int i=0;i<L;i++){
      int pos;
      scanf("%d",&pos);
      stage[pos] = 'L';
    }
    for(int i=0;i<B;i++){
      int pos;
      scanf("%d",&pos);
      stage[pos] = 'B';
    }

    //dp[pos][turn][stop_flag]
    dp[0][0][0] = 1.0;
    for(int turn=1;turn<=T;turn++){
      for(int from=0;from<N;from++){
	for(int spots=1; spots<=6;spots++){
	  int to = (from + spots > N ? 
		    N - (from + spots - N) 
		    : from+spots);

	  if(stage[to] == 'B'){
	     dp[0][turn][0]
	       += dp[from][turn-1][0] * 1.0/6.0;
	  }
	  
	  else if(stage[to] == 'L'){
	    //rest
	    dp[to][turn][1]
	      += dp[from][turn-1][0] * 1.0/6.0;
	  }
	  else if(stage[to] == '.'){
	    dp[to][turn][0]
	      += dp[from][turn-1][0] * 1.0/6.0;
	  }
	}
	dp[from][turn][0]
	  += dp[from][turn-1][1];
      }
    }

    double sum = 0;
    for(int turn=1;turn<=T;turn++){
      sum += dp[N][turn][0];
      sum += dp[N][turn][1];
    }
    printf("%.7lf\n",sum);
  }
}
