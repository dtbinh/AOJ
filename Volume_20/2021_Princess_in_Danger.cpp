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
  int city_num,refreez_limit,freezing_plant_num,
    road_num,capital_idx,hospital_idx;
  while(~scanf("%d %d %d %d %d %d",
	       &city_num,&refreez_limit,&freezing_plant_num,
	       &road_num,&capital_idx,&hospital_idx)){
    for(int i=0;i<freezing_plant_num;i++){
      int city_idx;
      scanf("%d",&city_idx);
    }
    for(int i=0;i<road_num;i++){
      int from,to,cost;
      scanf("%d %d %d",&from,&to,&cost);
    }
  }
}
