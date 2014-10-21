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
 
int main(){
  int limit;
  int total_requirements;
  while(~scanf("%d %d",&limit,&total_requirements)){
    if(limit == 0 && total_requirements == 0) break;
    vector<int> requirements;
    for(int require_i = 0; require_i < total_requirements; require_i++){
      int num;
      scanf("%d",&num);
      requirements.push_back(num);
    }

    sort(requirements.begin(),requirements.end());

    double exp = 0.0;
    double sum = EPS;
    map<int,int> can_make;
    for(int round = 0; round < 100000000; round++){
      int year = rand() % limit + 1;
      bool can_make = true;
      for(int require_i = 0; require_i < requirements.size(); require_i++){
	if(requirements[require_i] > year) break;
	if(year % requirements[require_i] == 0){
	  can_make = false;
	  break;
	}
      }
      if(!can_make) continue;
      sum += 1.0;
      exp += (double)year;
    }

    printf("%lf\n",exp / sum);
  }
}
