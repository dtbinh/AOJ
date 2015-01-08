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

ll fast_pow(ll x, ll n) {
  ll res = 1;
  while(n > 0) {
    if (n & 1) res = res * x;
    x = x * x;
    n >>= 1;
  }
  return res;
}

ll GCD(ll a ,ll b){
  return b > 0 ? GCD(b,a%b) : a;
}

int main(){
  string str;
  while(cin >> str){
    if(str == "#") break;

    int west_count = 0;
    int north_count = 0;
    for(int i = 0; i < str.size(); i++){
      if(str[i] == 'n'){
	north_count++;
      }
      else if(str[i] == 'w'){
	west_count++;
      }
    }

    ll max_count = max(north_count,west_count);

    int sum = 0;
    sum += fast_pow(2,max_count - 1) * 90;
    for(ll i = 1; i <= north_count; i++){
      sum -= 90 * fast_pow(2,max_count - i);
    }
    for(ll i = 1; i <= west_count; i++){
      sum += 90 * fast_pow(2,max_count - i);
    }
    ll div = GCD(sum,fast_pow(2,max_count));

    if(fast_pow(2,max_count) / div == 1){
      printf("%lld\n",sum / div);
    }
    else{
      printf("%lld/%lld\n",sum / div,fast_pow(2,max_count) / div);
    }
  }
}
