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


int compute_cost(int p1,int p2,int dept_station,int total_stations,
		 const vector<int>& stations){
  
  int res = INF;

  if(stations[p1] < dept_station
     && dept_station < stations[p2] ){
    int dist1 = abs(stations[p1] - dept_station);
    int dist2 = abs(stations[p2] - dept_station);
    res = 100 * min(dist1 + dist2 * 2, dist1 * 2 + dist2);
  }

  else if(stations[p1] > dept_station){
    int dist1 = abs(dept_station - stations[p1]);
    int dist2 = (total_stations - stations[p2]) + dept_station;
    res = 100 * min(dist1 * 2 + dist2,dist1 + dist2 * 2);
  }
  else if(stations[p2] < dept_station){
    int dist1 = abs(dept_station - stations[p2]);
    int dist2 = (total_stations - dept_station) + stations[p1];
    res = 100 * min(dist1 * 2 + dist2,dist1 + dist2 * 2);
  }

  return res;
}

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
    }

    sort(stations.begin(),stations.end());

    int res = INF;

    if(dept_station < stations[0]){
      res = 100 * (stations[stations.size() - 1] - dept_station);
      res = min(res,100 * (dept_station + (total_stations - stations[0])));
    }

    if(dept_station > stations[stations.size() - 1]){
      res = min(res,100 * (dept_station - stations[0]));
      res = min(res,100 * ((total_stations - dept_station) + stations[stations.size() - 1]));
    }

    for(int i = 0; i < stations.size(); i++){
      int p1 = i;
      int p2 = (i + 1) % stations.size();
      res = min(compute_cost(p1,p2,dept_station,total_stations,stations),res);
    }
    printf("%d\n",res);
  }
}
