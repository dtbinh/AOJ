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

class Compare {
  int monster_x;
  int monster_y;
public:
  Compare(int monster_x,int monster_y)
    : monster_x(monster_x), monster_y(monster_y) {}
  bool operator()(const P& ci,const P& cj) const{
    int dist_i = (ci.first - monster_x) * (ci.first - monster_x)
      + (ci.second - monster_y) * (ci.second - monster_y);
    int dist_j = (cj.first - monster_x) * (cj.first - monster_x)
      + (cj.second - monster_y) * (cj.second - monster_y);
    return dist_i < dist_j;
  }
};

class State{
  int x;
  int y;
  double dist;
};

bool dfs(int hero_x,
	 int hero_y,
	 double current_time,
	 int S,
	 int monster_x,
	 int monster_y,
	 const vector<P>& cristals){
  bool res = false;

  if(S == (1<<cristals.size()) - 1) return true;
  for(int i=0;i<cristals.size();i++){
    if(S & (1<<i)) continue;
    double add_time = sqrt((hero_x - cristals[i].first) * (hero_x - cristals[i].first)
			   + (hero_y - cristals[i].second) * (hero_y - cristals[i].second));
    
    double impurity_arrive_time = sqrt((monster_x - cristals[i].first) * (monster_x - cristals[i].first)
				       + (monster_y - cristals[i].second) * (monster_y - cristals[i].second));
    if(current_time + add_time >= impurity_arrive_time){
      return false;
    }
    
    res |= dfs(cristals[i].first,cristals[i].second,current_time + add_time,
	       S | (1<<i),monster_x,monster_y,cristals);
    if(res) return res;
  }
  return res;
}

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
    for(int cristal_i = 0; cristal_i < total_cristals; cristal_i++){
      int x,y;
      scanf("%d %d",&x,&y);
      cristals.push_back(P(x,y));
    }
    Compare comp(monster_x,monster_y);
    sort(cristals.begin(),cristals.end(),comp);
    printf("%s\n", dfs(hero_x,hero_y,0,0,monster_x,monster_y,cristals)
	   ? "YES" : "NO");
  }
}
