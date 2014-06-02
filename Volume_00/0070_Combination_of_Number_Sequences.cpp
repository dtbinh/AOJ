#define _USE_MATH_DEFINES
#include <iostream>
#include <cstdio>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <queue>
#include <stack>
#include <limits>
#include <map>
#include <string>
#include <cstring>
#include <set>
#include <deque>

using namespace std;

typedef long long ll;
typedef pair<int,int> P;

int dp[11][331][1<<10];
int main(){
  memset(dp,0,sizeof(dp));
  dp[0][0][0] = 1;
  for(int multiply=1;multiply<=10;multiply++){
    for(int used = 0; used <= (1<<10) - 1; used++){
      for(int base = 330;base >= 0; base--){
	if(dp[multiply-1][base][used] == 0) continue;
	for(int to=0; to<=9; to++){
	  if(used & (1 << to)) continue;
	  if(to * multiply + base > 330) continue;

	  dp[multiply][to * multiply + base][used | (1<<to)]
	    += dp[multiply - 1][base][used];
	}
      }
    }
  }
  
  int n,target_sum;
  while(~scanf("%d %d",&n,&target_sum)){
    if(target_sum > 330 || n >= 11){
      printf("0\n");
    }
    else{
      int res = 0;
      for(int S=0;S<=(1<<10) - 1;S++){
	res += dp[n][target_sum][S];
      }
      printf("%d\n",res);
    }
  }
  return 0;
}

