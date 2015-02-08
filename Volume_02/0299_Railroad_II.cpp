#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
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

using namespace std;

typedef long long ll;
typedef pair<int,string> P;

static const double EPS = 1e-8;

int main(){
  int total_stations;
  int total_buy_stations;
  int dept_station;
  while(~scanf("%d %d %d",
	       &total_stations,
	       &total_buy_stations,
	       &dept_station)){
    vector<int> stations;
    for(int buy_i = 0; buy_i < total_buy_stations; buy_i++){
      int station_id;
      scanf("%d",&station_id);
      stations.push_back(station_id);
      stations.push_back((station_id > dept_station) ? 
			 station_id - total_stations
			 : station_id + total_stations);
    }

    sort(stations.begin(),stations.end());

    int res = INF;
    
    res = 100 * min(dept_station - stations[0],
		    stations[2 * total_buy_stations - 1] - dept_station);
    for(int i = 1; i < total_buy_stations; i++){
      int route1 = min(dept_station - stations[i],
		       stations[total_buy_stations + i - 1] - dept_station);
      int route2 = max(dept_station - stations[i],
		       stations[total_buy_stations + i - 1] - dept_station);
      res = min(res,100 * (route1 * 2 + route2));
    }
    printf("%d\n",res);
  }
}
