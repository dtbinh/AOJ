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

map<string,int> cities;
int dp[301][3001]; //dp[city_id][consumed_LPG] = dist;
int nodes[3001][3001];
bool is_LPG[3001];

int get_city_id(const string& city){
  if(cities.find(city) == cities.end()){
    int idx = cities.size();
    cities[city] = idx;
  }
  return cities[city];
}

class State {
public:
  int city_id;
  int dist;
  int consumed_LPG;
  State(int _city_id,int _dist,int _con){
    city_id = _city_id;
    dist = _dist;
    consumed_LPG = _con;
  }

  bool operator <(const State& s) const{
    return (dist < s.dist);
  }

  bool operator >(const State& s) const{
    return (dist > s.dist);
  }
};

int main(){
  int total_roads;
  int total_LPG_stations;
  int capacity;
  while(~scanf("%d %d %d",
	       &total_roads,
	       &total_LPG_stations,
	       &capacity)){
    if(total_roads == 0
       && total_LPG_stations == 0
       && capacity == 0) break;

    cities.clear();

    memset(nodes,0x3f,sizeof(nodes));
    memset(dp,0x3f,sizeof(dp));
    memset(is_LPG,false,sizeof(is_LPG));

    string src,dst;
    cin >> src >> dst;
    get_city_id(src);
    get_city_id(dst);

    for(int road_idx = 0; road_idx < total_roads; road_idx++){
      string from_str,to_str;
      int dist;

      cin >> from_str >> to_str >> dist;
      int from_num = get_city_id(from_str);
      int to_num = get_city_id(to_str);
      nodes[from_num][to_num] = dist;
      nodes[to_num][from_num] = dist;
    }

    for(int LPG_idx = 0; LPG_idx < total_LPG_stations; LPG_idx++){
      string city;
      cin >> city;
      is_LPG[get_city_id(city)] = true;
    }

    priority_queue<State,vector<State>, greater<State> > que;
    que.push(State(get_city_id(src),0,0));
    dp[get_city_id(src)][0] = 0;

    while(!que.empty()){
      State s = que.top();
      que.pop();
      for(int to=0;to<cities.size();to++){
	if(nodes[s.city_id][to] >= INF) continue;
	if(capacity*10 < s.consumed_LPG + nodes[s.city_id][to]) continue;
	int next_consumed_LPG = (is_LPG[to] ? 0 : (s.consumed_LPG + nodes[s.city_id][to]));

	if(dp[to][next_consumed_LPG]
	   <= s.dist + nodes[s.city_id][to]) continue;

	dp[to][next_consumed_LPG] = s.dist + nodes[s.city_id][to];
	que.push(State(to,s.dist + nodes[s.city_id][to],next_consumed_LPG));
      }
    }

    int dst_id = get_city_id(dst);
    int res = INF;
    for(int consumed_LPG = 0;consumed_LPG <= 3000; consumed_LPG++){
      res = min(dp[dst_id][consumed_LPG],res);
    }
    printf("%d\n",res >= INF ? -1 : res);
  }
}
