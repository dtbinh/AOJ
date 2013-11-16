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
  int total_carrots;
  int carrot_store_ability;
  int power_up_duration;
  int normal_speed;
  int power_up_speed;
  int goal_distance;
  while(~scanf("%d %d %d %d %d %d",
	       &total_carrots,
	       &carrot_store_ability,
	       &power_up_duration,
	       &normal_speed,
	       &power_up_speed,
	       &goal_distance)){

    int carrots[201];
    for(int carrot_idx=0;carrot_idx< total_carrots; carrot_idx++){
      int distance;
      scanf("%d",&distance);
      carrots[carrot_idx] = distance;
    }

    int current_pos = 0;
    for(int carrot_idx=0;carrot_idx< total_carrots; carrot_idx++){
    }
  }

}
