#define _USE_MATH_DEFINES
#define INF 100000000
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
#include <cstdio>

using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P> PP;
 
static const double EPS = 1e-8;
 
const int tx[] = {0,1,0,-1};
const int ty[] = {-1,0,1,0};

ll GCD(ll a ,ll b){
  return b > 0 ? GCD(b,a%b) : a;
}

ll LCM(ll a ,ll b){
  return a / GCD(a,b) * b;
}

int main(){
  ll limit;
  int total_requirements;
  while(~scanf("%lld %d",&limit,&total_requirements)){
    if(limit == 0 && total_requirements == 0) break;
    vector<ll> requirements;
    for(int require_i = 0; require_i < total_requirements; require_i++){
      ll num;
      scanf("%lld",&num);
      requirements.push_back(num);
    }
    sort(requirements.begin(),requirements.end());

    ll gain = limit * (1 + limit) / 2LL;
    ll remaining_items = limit;

    ll lost = 0;
    ll set_size = 0;
    for(int S=1;S<(1<<total_requirements);S++){
      ll lcm = 1;
      for(int i=0;i<requirements.size();i++){
	if(S & (1<<i)){
	  lcm = LCM(requirements[i],lcm);
	  if(lcm > limit) break;
	}
      }
      if(lcm > limit) continue;

      ll sign = -1;
      if(__builtin_popcount(S) & 1){
	sign = 1;
      }
      ll first_item = lcm;
      ll num_of_item = limit / lcm;
      ll last_item = num_of_item * lcm;
      set_size += sign * num_of_item;
      lost += sign * num_of_item * (first_item + last_item) / 2LL;
    }
    
    remaining_items -= set_size;
    gain -= lost;
    if(remaining_items == 0){
      printf("%.8lf\n",0);
    }
    else{
      printf("%.8lf\n",(double)gain/(double)remaining_items);
    }
  }
}
