#define _USE_MATH_DEFINES
#define INF 0x11111111
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
#include <iterator>
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;
 
int tx[] = {0,1,0,-1};//URDL
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

int main(){
  int total_cities;
  int total_roads;

  while(~scanf("%d %d",&total_cities,&total_roads)){
    if(total_cities == 0 && total_roads == 0) break;

    int sea[201][201];
    int land[201][201];
    memset(sea,0x11,sizeof(sea));
    memset(land,0x11,sizeof(land));

    for(int road_idx = 0; road_idx < total_roads; road_idx++){
      int src,dst,time;
      char type[2];
      scanf("%d %d %d %s",&src,&dst,&time,type);
      if(type[0] == 'S'){
	sea[src][dst] = min(sea[src][dst],time);
	sea[dst][src] = min(sea[dst][src],time);
      }
      else if(type[0] == 'L'){
	land[src][dst] = min(land[src][dst],time);
	land[dst][src] = min(land[dst][src],time);
      }
    }
    for(int src=1;src<=total_cities;src++){
      int dst = src;
      sea[src][dst] = 0;
      land[src][dst] = 0;
    }
    int total_routes;
    int routes[1001];
    scanf("%d",&total_routes);
    for(int route_idx = 0; route_idx < total_routes; route_idx++){
      int route;
      scanf("%d",&route);
      routes[route_idx] = route;
    }

    int dp[201][201];
    memset(dp,0x11,sizeof(dp));

    for(int mid=1;mid<=total_cities;mid++){
      for(int src=1;src<=total_cities;src++){
	for(int dst=1;dst<=total_cities;dst++){
	  land[src][dst] = min(land[src][dst],land[src][mid] + land[mid][dst]);
	  sea[src][dst] = min(sea[src][dst],sea[src][mid] + sea[mid][dst]);
	}
      }
    }
    
    int ship[1001][201]; // ship[route_idx][city] = cost
    memset(ship,0x11,sizeof(ship));
    ship[0][routes[0]] = 0;

    for(int route_idx = 1; route_idx < total_routes; route_idx++){
      int prev_target = routes[route_idx - 1];
      int target = routes[route_idx];

      for(int mid1 = 1; mid1 <= total_cities; mid1++){
	ship[route_idx][mid1] = min(ship[route_idx][mid1],ship[route_idx-1][mid1] + land[prev_target][target]);

	for(int mid2 = 1; mid2 <= total_cities; mid2++){
	  ship[route_idx][mid2] = min(ship[route_idx][mid2],
				      ship[route_idx-1][mid1] + land[prev_target][mid1] + sea[mid1][mid2] + land[mid2][target]);
	}
      }
    }
    int res = INF;
    for(int city=1;city<=total_cities;city++){
      res = min(ship[total_routes-1][city],res);
    }
    printf("%d\n",res);
  }
}
