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

int main(){
  int total_data_sets;
  while(~scanf("%d",&total_data_sets)){
    for(int data_set_idx = 0; data_set_idx < total_data_sets; data_set_idx++){
      int total_boards;
      for(int board_idx = 0; board_idx < total_boards; board_idx++){
	int x,height;
	scanf("%d %d",&x,&height);
      }
      int total_faucets;
      for(int foucet_idx = 0; foucet_idx < total_faucets; foucet_idx++){
	int x,cm3_per_second;
	scanf("%d %d",&x,&cm3_per_second);
      }

      int total_observation_times;
      for(int observation_time_idx = 0; observation_time_idx < total_observation_times; observation_time_idx++){
	int x,time;
	scanf("%d %d",&x,&time);
      }
    }
  }
}
