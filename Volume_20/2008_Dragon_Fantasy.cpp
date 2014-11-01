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
 
static const double EPS = 1e-12;

double dp[1<<21][21];

int main(){
  int total_cristals;
  int hero_x;
  int hero_y;
  int monster_x;
  int monster_y;
  while(~scanf("%d %d %d %d %d",
	       &total_cristals,
	       &hero_x,
	       &hero_y,
	       &monster_x,
	       &monster_y)){
    if(total_cristals == 0 && hero_x == 0 && hero_y == 0
       && monster_x == 0 && monster_y == 0) break;
    vector<P> cristals;
    cristals.push_back(P(hero_x,hero_y));
    for(int cristal_i = 0; cristal_i < total_cristals; cristal_i++){
      int x,y;
      scanf("%d %d",&x,&y);
      cristals.push_back(P(x,y));
    }
    fill((double*)dp,(double*)dp + (1<<21) * 21,1000000000000);
    dp[(1<<0)][0] = 0;
    for(int S = 0; S < (1<<cristals.size()); S++){
      for(int from = 0; from < cristals.size(); from++){
	if(!(S & (1<<from))) continue;
	for(int to = 0; to < cristals.size(); to++){
	  if(S & (1<<to)) continue;
	  double diff_x = cristals[from].first - cristals[to].first;
	  double diff_y = cristals[from].second - cristals[to].second;
	  double dist = sqrt(diff_x * diff_x + diff_y * diff_y); 

	  double impurity = 
	    sqrt((monster_x - cristals[to].first) * (monster_x - cristals[to].first)
		 + (monster_y - cristals[to].second) * (monster_y - cristals[to].second));
	  if(impurity > dp[S][from] + dist){
	    dp[S | (1<<to)][to] = min(dp[S][from] + dist,
				      dp[S | (1<<to)][to]);
	  }
	}
      }
    }
    
    bool res = false;
    for(int to = 0; to < cristals.size(); to++){
      if(dp[(1<<cristals.size()) - 1][to] < 1000000000000){
	res = true;
	break;
      }
    }

    printf("%s\n",res ? "YES" : "NO");
  }
}
