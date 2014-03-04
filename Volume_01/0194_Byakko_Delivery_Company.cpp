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

bool dp[201][4][21][21];

int main(){
  int total_east2west_roads;
  int total_north2south_roads;
  while(~scanf("%d %d",
	       &total_east2west_roads,
	       &total_north2south_roads)){
    if(total_east2west_roads == 0 && total_north2south_roads == 0) continue;
    int normal_required_time;
    scanf("%d",&normal_required_time);

    int traffic_light[21][21];
    bool has_construction[21][21][21][21];
    int traffic_jam[21][21][21][21];
    memset(traffic_light,0,sizeof(traffic_light));
    memset(traffic_jam,0,sizeof(traffic_jam));
    memset(has_construction,false,sizeof(has_construction));

    int total_traffic_lights;
    scanf("%d",&total_traffic_lights);
    for(int traffic_light_idx = 0; traffic_light_idx < total_traffic_lights; traffic_light_idx++){
      char point[32];
      int period;
      scanf("%s %d",point,&period);
      pair<char,int> pos = conv(point);
      traffic_light[pos.first - 'a'][pos.second - 1] = period;
    }
    int total_roads_being_constructed;
    scanf("%d",&total_roads_being_constructed);
    for(int road_idx = 0; road_idx < total_roads_being_constructed; road_idx++){
      char from[32];
      char to[32];
      scanf("%s %s",from,to);
      pair<char,int> pos_from = conv(from);
      pair<char,int> pos_to = conv(to);

      has_construction[pos_from.first - 'a'][pos_from.second - 1][pos_to.first - 'a'][pos_to.second - 1] = true;
      has_construction[pos_to.first - 'a'][pos_to.second - 1][pos_from.first - 'a'][pos_from.second - 1] = true;
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
      traffic_jam[pos_from.first - 'a'][pos_from.second - 1][pos_to.first - 'a'][pos_to.second - 1] = jam_required_time;
      traffic_jam[pos_to.first - 'a'][pos_to.second - 1][pos_from.first - 'a'][pos_from.second - 1] = jam_required_time;
    }
    
    char start[32];
    char goal[32];

    scanf("%s %s",start,goal);
    pair<char,int> pos_s = conv(start);
    pair<char,int> pos_g = conv(goal);

    int sx = pos_s.second - 1;
    int sy = pos_s.first - 'a';

    int gx = pos_g.second - 1;
    int gy = pos_g.first - 'a';


    memset(dp,false,sizeof(dp));
    dp[0][1][sy][sx] = true;
    dp[0][0][sy][sx] = true;
    dp[0][2][sy][sx] = true;
    dp[0][3][sy][sx] = true;

    for(int time = 0;time <= 100; time++){
      for(int x=0;x<total_north2south_roads;x++){
	for(int y=0;y<total_east2west_roads;y++){
	  for(int next_dir=0;next_dir<4;next_dir++){

	    int dx = x + tx[next_dir];
	    int dy = y + ty[next_dir];
	    if(dx < 0 || dx >= total_north2south_roads
	       || dy < 0 || dy >= total_east2west_roads) continue;
	    if(has_construction[y][x][dy][dx]) continue;

	    for(int org_dir = 0; org_dir < 4 ; org_dir++){	    
	      if((org_dir+2)%4 == next_dir) continue;

	      if((org_dir == 1 || org_dir == 3) 
		 && traffic_light[y][x] != 0
		 && (time / traffic_light[y][x]) % 2 == 0) continue;
	      
	      if((org_dir == 0 || org_dir == 2) 
		 && traffic_light[y][x] != 0
		 && (time / traffic_light[y][x]) % 2 != 0) continue;

	      int jam = traffic_jam[y][x][dy][dx];
	      dp[time + jam + normal_required_time][next_dir][dy][dx]
		|= dp[time][org_dir][y][x];
	    }
	  }
	}
      }
    }
    int res = INF;
    for(int time = 0;time <= 100; time++){
      for(int dir = 0;dir < 4; dir++){
	if(dp[time][dir][gy][gx]){
	  res = min(time,res);
	}
      }
    }

    printf("%d\n",res);

  }
}
