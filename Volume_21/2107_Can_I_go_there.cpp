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
  int total_stations;
  int total_sections;
  int total_steps;
  while(~scanf("%d %d %d",
	       &total_stations,
	       &total_sections,
	       &total_steps)){
    if(total_stations == 0 && total_sections == 0 && total_steps == 0) break;
    for(int section_i = 0; section_i < total_sections; section_i++){
      int src,dst;
      scanf("%d %d",&src,&dst);
    }
  }
}
