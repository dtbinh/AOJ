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

class Node {
public:
  int to;
  int dist;
  Node() {}
  Node(int _t,int _d) : to(_t),dist(_d){}
};

bool is_LPG[3005];
bool dp[3005][2005]; //dp[city_id][remaining_LPG] = dist;

int get_city_id(map<string,int>& cities,const string& city){
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
  int remaining_LPG;
  State(int _city_id,int _dist,int _con){
    city_id = _city_id;
    dist = _dist;
    remaining_LPG = _con;
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
  while(cin >> total_roads >> total_LPG_stations >>capacity){
    if(total_roads == 0
       && total_LPG_stations == 0
       && capacity == 0) break;

    map<string,int> cities;
    memset(is_LPG,false,sizeof(is_LPG));
    memset(dp,false,sizeof(dp));

    string src,dst;
    cin >> src >> dst;
    get_city_id(cities,src);
    get_city_id(cities,dst);

    vector<Node> nodes[6001];
    for(int road_idx = 0; road_idx < total_roads; road_idx++){
      string from_str,to_str;
      int dist;

      cin >> from_str >> to_str >> dist;
      int from_num = get_city_id(cities,from_str);
      int to_num = get_city_id(cities,to_str);

      nodes[from_num].push_back(Node(to_num,dist));
      nodes[to_num].push_back(Node(from_num,dist));
    }

    for(int LPG_idx = 0; LPG_idx < total_LPG_stations; LPG_idx++){
      string city;
      cin >> city;
      is_LPG[get_city_id(cities,city)] = true;
    }

    priority_queue<State,vector<State>, greater<State> > que;
    que.push(State(get_city_id(cities,src),0,10*capacity));

    int dst_id = get_city_id(cities,dst);

    int res = INF;
    while(!que.empty()){
      State s = que.top();
      que.pop();

      if(s.city_id == dst_id){
	res = s.dist;
	goto found;
      }
      if(dp[s.city_id][s.remaining_LPG]) continue;
      dp[s.city_id][s.remaining_LPG] = true;

      for(int to_idx=0;to_idx<nodes[s.city_id].size();to_idx++){
	int to = nodes[s.city_id][to_idx].to;
	int dist = nodes[s.city_id][to_idx].dist;
	if(s.remaining_LPG < dist) continue;

	int next_remaining_LPG = (is_LPG[to] ? 10 * capacity : s.remaining_LPG - dist);

	que.push(State(to,s.dist + dist,next_remaining_LPG));
      }
    }
  found:;
    printf("%d\n",res >= INF ? -1 : res);
  }
  return 0;
}
