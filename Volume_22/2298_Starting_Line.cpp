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

    bool carrots[10001];
    memset(carrots,false,sizeof(carrots));

    for(int carrot_idx=0;carrot_idx< total_carrots; carrot_idx++){
      int distance;
      scanf("%d",&distance);
      carrots[distance] = true;
    }

    int current_pos = 0;

    int current_carrots = 0;
    int life = 0;

    int high_speed_interval =0;
    for(int pos=0;pos< goal_distance; pos++,life--){
      if(carrots[pos]){
	current_carrots++;
      }

      if((life <= 0 && current_carrots > 0)
	 || (current_carrots > carrot_store_ability)){
	current_carrots--;
	life = power_up_duration * power_up_speed;
      }

      if(life > 0){
	high_speed_interval++;
      }
    }

    printf("%.9lf\n",(double)high_speed_interval/(double)power_up_speed
	   + (double)(goal_distance - high_speed_interval)/(double)normal_speed);
  }

}
