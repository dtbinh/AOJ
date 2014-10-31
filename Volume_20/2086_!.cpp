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
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

unsigned long long conv(int base,const string& fact){
  unsigned long long res = 0;
  unsigned long long digit = 1ULL;
  for(int i = fact.size() - 1; i >= 0; i--){
    if('A' <= fact[i] && fact[i] <= 'Z'){
      res += (fact[i] - 'A' + 10) * digit;
      digit *= base;
    }
    else{
      res += (fact[i] - '0') * digit;
      digit *= base;
    }
  }
  return res;
}

int main(){
  int base;
  string fact;
  while(cin >> base >> fact){
    if(base == 0 && fact == "0") break;
    unsigned long long init = conv(base,fact);
    unsigned long long prime_factor[37] = {};
    for(int i = 2; i <= base; i++){
      while(base % i == 0){
	prime_factor[i]++;
	base /= i;
      }
    }

    unsigned long long res = numeric_limits<unsigned long long>::max();
    for(unsigned long long i = 2; i <= 36; i++){
      if(prime_factor[i] == 0) continue;
      unsigned long long count = 0;
      unsigned long long tmp = init;

      while(tmp > 0){
	count += tmp / i;
	tmp /= i;
      }
      res = min(res,count / prime_factor[i]);
    }

    if(res == numeric_limits<unsigned long long>::max()) res = 0;    
    cout << res << endl;
  }
}
