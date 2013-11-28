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
  
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};

int main(){
  ll money,rate_d,rate_r,consume_d,consume_r;
  while(~scanf("%lld %lld %lld %lld %lld",
	       &money,&rate_d,&rate_r,&consume_d,&consume_r)){
    ll x1 = consume_d*100/rate_d;
    if(rate_d * x1 % 100 != 0) x1++;
    ll x2 = consume_r*100/rate_r;
    if(rate_r * x2 % 100 != 0) x2++;
    
    printf("%lld\n",money - x1 -x2 >= 0 ? money - x1 -x2 : -1);
  }
}
