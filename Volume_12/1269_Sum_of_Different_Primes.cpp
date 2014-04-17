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

bool is_prime[1121];
int dp[40001][20]; //dp[num][size] = count

int main(){

  memset(is_prime,true,sizeof(is_prime));

  is_prime[0] = false;
  is_prime[1] = false;
  for(int i=2;i*i<=1120;i++){
    if(!is_prime[i]) continue;

    for(int j=i+i;j<=1120;j+=i){
      is_prime[j] = false;
    }
  }

  vector<int> primes;
  for(int i=0;i<=1120;i++){
    if(is_prime[i]) {
      primes.push_back(i);
    }
  }

  memset(dp,0,sizeof(dp));
  dp[0][0] = 1;
  for(int i=0;i<primes.size();i++){
    for(int num=1120*14;num>=0;num--){
      for(int j=14;j>=0;j--){
	dp[num + primes[i]][j+1] += dp[num][j];
      }
    }
  }
  
  int target;
  int size;
  while(~scanf("%d %d",&target,&size)){
    if(target == 0 && size == 0) break;
    printf("%d\n",dp[target][size]);
  }
}
