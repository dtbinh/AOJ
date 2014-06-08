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

int dp[1200000];
      
int main(){
  memset(dp,0,sizeof(dp));
  for(int S=0;S<=(1<<20)-1;S++){
    int sum = 0;
    for(int i=0;i<20;i++){
      if(S & (1<<i)){
	sum += (i+1);
      }
    }
    dp[S] = sum;
  }
  int upper,num_of_elements,target_sum;
  while(~scanf("%d %d %d",
	       &upper,
	       &num_of_elements,
	       &target_sum)){
    if(upper == 0 
       && num_of_elements == 0 
       && target_sum == 0) break;

    int res = 0;
    for(int S=0;S<=(1<<upper)-1;S++){
      if(__builtin_popcount(S) != num_of_elements) continue;
      if(dp[S] != target_sum) continue;
      res++;
    }
    printf("%d\n",res);
  }
}
