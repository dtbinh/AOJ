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
  int num_of_switches;
  int num_of_light_bulbs;
  int num_of_operations;
  while(~scanf("%d %d %d",
	       &num_of_switches,
	       &num_of_light_bulbs,
	       &num_of_operations)){
    if(num_of_switches == 0
       && num_of_light_bulbs == 0
       && num_of_operations == 0) break;

    bool flags[50] = {};
    bool states[50][1001] = {};
    vector<string> light_bulbs_log;
    for(int operation_i = 0; operation_i < num_of_operations; operation_i++){
      string switches;
      string light_bulbs;
      cin >> switches >> light_bulbs;
      for(int switch_i = 0; switch_i < switches.size(); switch_i++){
	if(switches[switch_i] == '1'){
	  flags[switch_i] = !flags[switch_i];
	}
	states[switch_i][operation_i] = flags[switch_i];
      }
      light_bulbs_log.push_back(light_bulbs);
    }
    
    for(int light_i = 0; light_i < num_of_light_bulbs; light_i++){

      vector<int> candidates;
      for(int switch_i = 0; switch_i < num_of_switches; switch_i++){
	bool isok = true;
	for(int operation_i = 0; operation_i < light_bulbs_log.size(); operation_i++){
	  bool state = (light_bulbs_log[operation_i][light_i] == '1' ? true : false);
	  if(states[switch_i][operation_i] != state){
	    isok = false;
	    break;
	  }
	}

	if(isok){
	  candidates.push_back(switch_i);
	}
      }

      if(candidates.size() != 1){
	printf("?");
      }
      else{
	if(candidates[0] >= 10){
	  printf("%c",candidates[0] - 10 + 'A');
	}
	else{
	  printf("%c",candidates[0] + '0');
	}
      }
    }
    cout << endl;
  }
}
