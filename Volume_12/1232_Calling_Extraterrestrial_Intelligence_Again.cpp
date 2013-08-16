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

bool isPrime[100001];

int main(){
  ll m,a,b;
  vector<ll> primes;
  memset(isPrime,true,sizeof(isPrime));
  isPrime[0] = false;
  isPrime[1] = false;

  for(int i=2;i*i<=100000;i++){
    if(!isPrime[i]) continue;
    primes.push_back(i);
    for(int j=i+i;j<=100000;j+=i){
      isPrime[j] = false;
    }
  }

  while(~scanf("%ld %ld %ld",&m,&a,&b)){
    if(m==0 && a==0 && b==0) break;

    ll opt_area = 0;
    ll opt_p = 0;
    ll opt_q = 0;
    for(int i=0;i<primes.size();i++){
      for(int j=i;j<primes.size();j++){

	if(primes[i] * primes[j] <= m){
	  ll p = primes[i];
	  ll q = primes[j];
	  if(a*q <= b*p && p <= q){
	    if(opt_area < p*q){
	      opt_area = p*q;
	      opt_p = p;
	      opt_q = q;
	    }
	  }
	}
      }
    }
    printf("%ld %ld\n",opt_p,opt_q);
  }
}
