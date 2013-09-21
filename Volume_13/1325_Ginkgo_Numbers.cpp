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
 
const static int mx[] = {1,-1,1,-1};
const static int my[] = {1,-1,-1,1};

P multiply_ginkgo(const P& p1,const P& p2){
  int a = p1.first * p2.first;
  int b = p1.second * p2.second;
  return P(a-b,a+b);
}

bool is_divisor(const P& p1,const P& p2){
  //judge p1(m,n) is a divisor of p2(p,q)
  
  //if and only if the integer m^2 + n^2 is a common divisor
  //of mp + nq and mq − np
  
  int m = p1.first;
  int n = p1.second;
  
  int p = p2.first;
  int q = p2.second;

  int c = m*m+n*n;
  if((m*p+n*q) % c == 0 && (m*q-n*p) % c == 0){
    return true;
  }
  return false;
}

bool is_eight_divisor(const P& p1,int m,int n){
  //<1, 0>, <0, 1>, <-1, 0>, <0,-1>,
  //<m, n>, <-n,m>, <-m,-n> and <n,-m> 
  //are divisors of <m, n>.
  int p = p1.first;
  int q = p1.second;

  const int candidate_p[] = {1,0,-1,0,m,-n,-m,n};
  const int candidate_q[] = {0,1,0,-1,n,m,-n,-m};

  for(int i=0;i<8;i++){
    if(p == candidate_p[i]
       && q == candidate_q[i]) return true;
  }
  return false;
}
int main(){
  int N;
  while(~scanf("%d",&N)){
    for(int i=0;i<N;i++){
      int m,n;
      scanf("%d %d",&m,&n);
      bool is_ok = true;
      for(int x=0;x*x<20000;x++){
	for(int y=0;x*x+y*y<20000;y++){
	  if(x*x+y*y <= 1) continue;
	  
	  for(int mi=0;mi<4;mi++){
	    if(is_divisor(P(x*mx[mi],y*my[mi]),P(m,n)) 
	       && !is_eight_divisor(P(x*mx[mi],y*my[mi]),m,n)){
	      is_ok = false;
	      goto found;
	    }
	  }
	}
      }
    found:;
      printf("%c\n",is_ok ? 'P' : 'C');
    }
  }
}
