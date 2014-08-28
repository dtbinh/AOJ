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
  
static const double EPS = 1e-8;
  
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};

ll sum[200001];

int main(){
  int N;
  while(~scanf("%d",&N)){
    vector<ll> baumkuchen;

    memset(sum,0,sizeof(sum));
    for(int i=0;i<N;i++){
      ll width;
      scanf("%lld",&width);
      baumkuchen.push_back(width);
      sum[i+1] = sum[i] + width;
    }
    
    for(int i=0;i<N;i++){
      sum[N + i + 1] = sum[N] + sum[i + 1];
    }

    ll lhs = 0;
    ll rhs = 100000000000000LL;
    for(int round = 0; round < 50; round++){
      ll mid = lhs + (rhs - lhs) / 2LL;

      bool isok = false;
      for(int i=0;i<N;i++){
	ll offset = sum[i];
	int div_idx = lower_bound(sum,sum + 2 * N,offset + mid) - sum;
	div_idx = lower_bound(sum,sum + 2 * N,sum[div_idx] + mid) - sum;
	div_idx = lower_bound(sum,sum + 2 * N,sum[div_idx] + mid) - sum;
	if(div_idx <= i + N){
	  isok = true;
	  break;
	}
      }
      if(isok){
	lhs = mid;
      }
      else{
	rhs = mid;
      }
    }

    printf("%lld\n",lhs);
  }
}
