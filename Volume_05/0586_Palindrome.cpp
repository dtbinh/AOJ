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

bool is_prime(ll n){
  for(ll x = 2; x * x <= n;x++){
    if(n % x == 0) return false;
  }
  return true;
}

enum Type{
  EVEN,
  ODD,
};

Type type;

ll dfs(ll pos,ll sum,ll len,ll center){
  if(pos == len/2){
    sum += (type == EVEN ? 0 : center * fast_pow(10,len/2));
    if(is_prime(sum)){
      return sum;
    }
    return 0;
  }
  ll res = 0;
  
  for(ll i=0;i<=9;i++){
    if(pos == 0 && i == 0) continue;
    ll lhs = i * fast_pow(10,pos);
    ll rhs = i * fast_pow(10,len-pos-1);
    res = max(dfs(pos + 1,sum + lhs + rhs,len,center),res);
  }
  return res;
}

int main(){
  ll n,center;
  while(~scanf("%lld %lld",&n,&center)){
    //odd
    if(center < 0){
      type = EVEN;

      if(n == 1){
	cout << "11" << endl;
      }
      else{
	cout << string(2*n,'9') << endl;
      }
    }
    //even
    else{
      type = ODD;
      ll len = 2 * n + (type == ODD ? 1 : 0);      
      ll ans = 0;
      ll none_ans = 0;
      
      for(int i=0;i<len;i++){
	none_ans += 9 * fast_pow(10,i);
      }
      printf("%lld\n",(ans = dfs(0,0,len,center)) == 0 ? none_ans : ans);
    }
  }
}
