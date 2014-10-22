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

    ll gain = limit * (1LL + limit) / 2;
    ll lost = 0;
    ll remaining_items = limit;
    for(int i=0;i<requirements.size();i++){
      bool is_already_computed = false;
      for(int j=0;j<i;j++){
      	if(requirements[i] % requirements[j] == 0){
      	  is_already_computed = true;
      	  break;
      	}
      }
      
      if(!is_already_computed){
	ll first_item = requirements[i];
	ll num_of_item = limit / requirements[i];
	ll last_item= num_of_item * requirements[i];
	remaining_items -= num_of_item;
	lost += num_of_item * (first_item + last_item) / 2;
      }
    }

    map<ll,bool> visited;
    for(int i=0;i<requirements.size();i++){
      if(visited[requirements[i]]) continue;
      for(int j=i+1;j<requirements.size();j++){
	ll lcm = LCM(requirements[i],requirements[j]);
	visited[lcm] = true;
	if(lcm == requirements[j]) continue;

	ll first_item = lcm;
	ll num_of_item = limit / lcm;
	ll last_item= num_of_item * lcm;
	remaining_items += num_of_item;
	lost -= num_of_item * (first_item + last_item) / 2;
      }
    }

    if(remaining_items == 0){
      printf("%.8lf\n",0);
    }
    else{
      printf("%.8lf\n",(double)(gain - lost)/(double)remaining_items);
    }
  }
}
