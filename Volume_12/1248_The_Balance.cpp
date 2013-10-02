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

int main(){
  ll lhs,rhs,d;
  while(~scanf("%ld %ld %ld",&lhs,&rhs,&d)){
    if(lhs==rhs && rhs==d && lhs==0) break;
    //abs(lhs*x-rhs*y) = d or abs(lhs*x+rhs*y) = d
    //lhs^2*x^2 -2*lhs*rhs*x*y +rhs^2*y^2 = d^2
    //lhs^2*x^2 +2*lhs*rhs*x*y +rhs^2*y^2 = d^2
    //(rhs^2)*y^2 + (-2*lhs*rhs*x)*y + (lhs^2*x^2 - d^2) = 0;
    //(rhs^2)*y^2 + (+2*lhs*rhs*x)*y + (lhs^2*x^2 - d^2) = 0;

    ll res_x=INF,res_y=INF;
    for(ll x=0;x<=50000;x++){
      ll a = rhs*rhs;
      ll b1 = (-2*lhs*rhs*x);
      ll b2 = (2*lhs*rhs*x);
      ll c = lhs*lhs*x*x - d*d;

      ll numerator[4];
      ll D = b1*b1 - 4*a*c;
      
      numerator[0] = -b1 + sqrt(D);
      numerator[1] = -b1 - sqrt(D);
      numerator[2] = -b2 + sqrt(D);
      numerator[3] = -b2 - sqrt(D);

      if(D < 0) continue;
      for(int i=0;i<4;i++){
	if(numerator[i] >= 0 && (numerator[i] % (2*a) == 0)){
	  ll y = numerator[i] / (2*a);
	  if(x + y <= res_x + res_y
	     && x*lhs + y*rhs <= res_x*lhs + res_y*rhs){
	    res_x = x;
	    res_y = y;
	  }
	}
      }
    }
    printf("%ld %ld\n",res_x,res_y);
  }
}
