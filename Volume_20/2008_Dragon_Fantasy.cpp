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
    for(int cristal_i = 0; cristal_i < total_cristals; cristal_i++){
      int x,y;
      scanf("%d %d",&x,&y);
    }
  }
}
