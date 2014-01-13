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

int dp[301][301];
map<string,int> cities;

int store_city(const string& city){
  if(cities.find(city) == cities.end()){
    cities[city] = cities.size();
  }
  return cities[city];
}

int main(){
  int total_roads;
  int total_LPG_stations;
  int capacity;
  while(~scanf("%d %d %d",
	       &total_roads,
	       &total_LPG_stations,
	       &capacity)){
    cities.clear();

    string src,dst;
    cin >> src >> dst;
    for(int road_idx = 0; road_idx < total_roads; road_idx++){
      string from_str,to_str;
      int dist;

      cin >> from_str >> to_str >> dist;
      int from_num = store_city(from_str);
      int to_num = store_city(to_str);
      dp[from_num][to_num] = dist;
      dp[to_num][from_num] = dist;
    }
  }
}
