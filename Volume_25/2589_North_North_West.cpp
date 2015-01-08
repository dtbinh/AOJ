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
typedef pair <ll,ll> P;
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

P compute_dir(ll lhs_numerator,ll lhs_denominator,
	      ll rhs_numerator,ll rhs_denominator){

  ll numerator = lhs_numerator * rhs_denominator + rhs_numerator * lhs_denominator;
  ll denominator = lhs_denominator * rhs_denominator;
  ll div = GCD(numerator,denominator);
  return P(numerator / div,denominator / div);

}

int main(){
  string str;
  while(cin >> str){
    if(str == "#") break;

    int west_count = 0;
    int north_count = 0;
    ll numerator = -1;
    ll denominator = -1;
    for(int i = str.size() -1; i >= 0; i--){
      if(str[i] == 'n'){
	if(numerator == -1){
	  numerator = 0;
	  denominator = 1;
	}
	else{
	  P next = compute_dir(numerator,denominator,
			       -90,fast_pow(2,north_count + west_count));
	  numerator = next.first;
	  denominator = next.second;
	}
	north_count++;
      }
      else if(str[i] == 'w'){
	if(numerator == -1){
	  numerator = 90;
	  denominator = 1;
	}
	else{
	  P next = compute_dir(numerator,denominator,
			       90,fast_pow(2,north_count + west_count));
	  numerator = next.first;
	  denominator = next.second;
	}
	west_count++;
      }
    }

    if(denominator <= 1){
      printf("%lld\n",numerator);
    }
    else{
      printf("%lld/%lld\n",numerator,denominator);
    }
  }
}
