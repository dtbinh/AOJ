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

int dp[5000002]; //dp[capacity] ::= min_price

int main(){
  int total_manju;
  int total_box;
  while(~scanf("%d %d",&total_manju,&total_box)){
    vector<int> manju;
    for(int manju_idx=0;manju_idx<total_manju;manju_idx++){
      int price;
      scanf("%d",&price);
      manju.push_back(price);
    }

    sort(manju.begin(),manju.end(),greater<int>());
    int sum[10001];
    memset(sum,0,sizeof(sum));
    for(int manju_idx=0;manju_idx<total_manju;manju_idx++){
      sum[manju_idx + 1] = sum[manju_idx] + manju[manju_idx];
    }


    memset(dp,0x3f,sizeof(dp));

    dp[0] = 0;
    for(int box_idx=0;box_idx<total_box;box_idx++){
      int capacity;
      int price;
      scanf("%d %d",&capacity,&price);
      for(int prev_manju_num = 10000; prev_manju_num >=0; prev_manju_num--){
	dp[prev_manju_num + capacity]
	  = min(dp[prev_manju_num + capacity],
		dp[prev_manju_num] + price);
      }
    }

    for(int prev_manju_num = 500*10000; prev_manju_num >=0; prev_manju_num--){
      dp[prev_manju_num] = min(dp[prev_manju_num],dp[prev_manju_num + 1]);
    }
    
    int res = 0;
    for(int manju_num=1;manju_num<=total_manju;manju_num++){
      res = max(sum[manju_num] - dp[manju_num],res);
    }

    printf("%d\n",res);
  }
}
