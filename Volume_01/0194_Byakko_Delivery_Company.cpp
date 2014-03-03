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

vector<string> split(const string &str, char delim){
  vector<string> res;
  size_t current = 0, found;
  while((found = str.find_first_of(delim, current)) != string::npos){
    res.push_back(string(str, current, found - current));
    current = found + 1;
  }
  res.push_back(string(str, current, str.size() - current));
  return res;
}

pair<char,int> conv(char point[32]){
  vector<string> v_pos = split(point,'-');
  string alpha = v_pos[0];
  string num = v_pos[1];
  return make_pair(alpha[0],atoi(num.c_str()));
}

int main(){
  int total_east2west_roads;
  int total_north2south_roads;
  while(~scanf("%d %d",
	       &total_east2west_roads,
	       &total_north2south_roads)){
    int normal_required_time;
    scanf("%d",&normal_required_time);

    int nodes[21][21];
    int edges[21][21][21][21];


    int total_traffic_lights;
    scanf("%d",&total_traffic_lights);
    for(int traffic_light_idx = 0; traffic_light_idx < total_traffic_lights; traffic_light_idx++){
      char point[32];
      int period;
      scanf("%s %d",point,&period);
      pair<char,int> pos = conv(point);
      nodes[pos->first - 'a'][pos->second - 1] = 1;
    }
    int total_roads_being_constructed;
    scanf("%d",&total_roads_being_constructed);
    for(int road_idx = 0; road_idx < total_roads_being_constructed; road_idx++){
      char from[32];
      char to[32];
      scanf("%s %s",from,to);
      pair<char,int> pos_from = conv(from);
      pair<char,int> pos_to = conv(to);

      edges[pos_from->first - 'a'][pos_from->second - 1][pos_to->first - 'a'][pos_to->second - 1] = 1;
    }

    int total_traffic_jam_roads;
    scanf("%d",&total_traffic_jam_roads);
    for(int road_idx = 0; road_idx < total_traffic_jam_roads; road_idx++){
      char from[32];
      char to[32];
      int jam_required_time;     
      scanf("%s %s %d",from,to,&jam_required_time);
      pair<char,int> pos_from = conv(from);
      pair<char,int> pos_to = conv(to);
      edges[pos_from->first - 'a'][pos_from->second - 1][pos_to->first - 'a'][pos_to->second - 1] = 1;
    }
    
    char start[32];
    char goal[32];

    scanf("%s %s",start,goal);
    pair<char,int> pos_s = conv(start);
    pair<char,int> pos_g = conv(goal);

    int sx = pos_s->second - 1;
    int sy = pos_s->first - 'a';

    int gx = pos_g->second - 1;
    int gy = pos_g->first - 'a';
  }
}
