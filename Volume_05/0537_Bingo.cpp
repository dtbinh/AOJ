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

int dp[3001][50];
const static int MOD = 100000;

int main(){
  int bingo_card_size;
  int upper_number;
  int bingo_card_sum;
  while(~scanf("%d %d %d",
	       &bingo_card_size,
	       &upper_number,
	       &bingo_card_sum)){
    if(bingo_card_size == 0
       && upper_number == 0
       && bingo_card_sum== 0) break;

    memset(dp,0,sizeof(dp));
    dp[0][0] = 1;
    for(int num=1;num<=upper_number;num++){
      for(int sum=bingo_card_sum;sum-num>=0;sum--){
	for(int filled_count=bingo_card_size*bingo_card_size;filled_count-1>=0;filled_count--){
	  dp[sum][filled_count] += dp[sum-num][filled_count-1];
	  dp[sum][filled_count] %= MOD;
	}
      }
    }

    printf("%d\n",dp[bingo_card_sum][bingo_card_size*bingo_card_size]);
  }
}
