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
#include <assert.h>
  
using namespace std;
  
typedef long long ll;
typedef pair <int,int> P;
typedef pair <double,P> PP;
  
static const double EPS = 1e-8;

int gcd(int a, int b)
{
  if(b == 0) return a;
  return gcd(b, a % b);
}

class Rational {
public:
  ll x;
  ll y;
  Rational(ll x,ll y)
    : x(x),y(y) {}
  bool operator<(const Rational& r) const{
    // (x*x)/(y*y) < (r.x*r.x)/(r.y*r.y)
    return x * x * r.y * r.y < r.x * r.x * y * y;
  }
  bool operator>(const Rational& r) const{
    return x * x * r.y * r.y > r.x * r.x * y * y;
  }
  bool operator>(const ll v) const{
    return x * x > v * y * y;
  }
  bool operator<(const ll v) const{
    // x/y < sqrt(v)
    // (x*x)/(y*y) < v
    // x * x < v * y * y
    return x * x < v * y * y;
  }
};

int main(){
  int p;
  int n;

  while(~scanf("%d %d",&p,&n)){
    if(p == 0 && n == 0) break;

    vector<Rational> rational_numbers;
    for(int numerator = 1; numerator <= n; numerator++){
      for(int denominator = 1; denominator <= numerator; denominator++){
	int div = gcd(numerator,denominator);
	int x = numerator / div;
	int y = denominator / div;
	if(x != numerator || y != denominator) continue;
	rational_numbers.push_back(Rational(x,y));
      }
    }
    sort(rational_numbers.begin(),rational_numbers.end());

    int i = lower_bound(rational_numbers.begin(),rational_numbers.end(),p) - rational_numbers.begin();
    i--;
    int u = rational_numbers[i].x;
    int v = rational_numbers[i].y;
    
    int x = rational_numbers[i+1].x;
    int y = rational_numbers[i+1].y;
    printf("%d/%d %d/%d\n",x,y,u,v);
  }
}
