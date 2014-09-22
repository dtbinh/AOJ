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
typedef pair <int,P> PP;
  
static const double EPS = 1e-8;

int main(){
  int num_of_guards;
  int simulation_duration;
  while(~scanf("%d %d",&num_of_guards,&simulation_duration)){
    if(num_of_guards == 0 && simulation_duration == 0) break;

    vector<int> time_table[101];
    for(int guard_i = 0; guard_i < num_of_guards; guard_i++){
      int comsuming_duration;
      int charging_duration;
      while(~scanf("%d",&comsuming_duration)){
	if(comsuming_duration == 0) break;
	scanf("%d",&charging_duration);
	time_table[guard_i].push_back(comsuming_duration);
	time_table[guard_i].push_back(charging_duration);
      }
    }
    
    
  }
}
