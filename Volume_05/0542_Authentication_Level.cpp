#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
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
#include <cstdio>

using namespace std;

typedef long long ll;
typedef pair <int,int> P;

static const double eps = 1e-8;

const int tx[4] = {+0,+1,+0,-1};
const int ty[4] = {-1,+0,+1,+0};

bool visited[501][501];
int rooms[2][501][501];
int required_auth_level[2][250001];

struct State {
  int x;
  int y;
  int auth;
  bool operator<(const State& s) const {
    return auth < s.auth;
  }
  bool operator>(const State& s) const {
    return auth > s.auth;
  }
  State(int x,int y,int auth) : x(x), y(y), auth(auth) {}
};

void bfs(int sx,int sy,int W,int H,int office_i){
  memset(visited,false,sizeof(visited));
  priority_queue<State,vector<State>, greater<State> > que;
  que.push(State(sx,sy,1));
  int current_auth_level = 0;
  int count = 0;
  while(!que.empty()){
    State s = que.top();
    que.pop();
    if(visited[s.y][s.x]) continue;
    visited[s.y][s.x] = true;

    count++;
    current_auth_level = max(s.auth,current_auth_level);
    required_auth_level[office_i][count] = current_auth_level;

    for(int i = 0; i < 4; i++){
      int dx = s.x + tx[i];
      int dy = s.y + ty[i];
      if(dx < 0 || dx >= W || dy < 0 || dy >= H) continue;
      if(visited[dy][dx]) continue;
       que.push(State(dx,dy,rooms[office_i][dy][dx]));
    }
  }
}

int main(){
  int have_to_visit_rooms;
  while(~scanf("%d",&have_to_visit_rooms)){
    if(have_to_visit_rooms == 0) break;
    memset(required_auth_level,0x3f,sizeof(required_auth_level));
    required_auth_level[0][0] = 0;
    required_auth_level[1][0] = 0;
    int elevator_x[2];
    int elevator_y[2];
    int W[2];
    int H[2];
    for(int office_i = 0; office_i < 2; office_i++){
      scanf("%d %d %d %d",&W[office_i],&H[office_i],
	    &elevator_x[office_i],&elevator_y[office_i]);
      elevator_x[office_i]--;
      elevator_y[office_i]--;

      for(int y = 0; y < H[office_i]; y++){
	for(int x = 0; x < W[office_i]; x++){
	  scanf("%d",&rooms[office_i][y][x]);
	}
      }

      bfs(elevator_x[office_i],
	  elevator_y[office_i],
	  W[office_i],H[office_i],office_i);
    }
    int res = 0x3f3f3f3f;
    for(int i = have_to_visit_rooms; i >= 0; i--){
      int j = have_to_visit_rooms - i;
      res = min(required_auth_level[0][i] + required_auth_level[1][j],res);
    }
    printf("%d\n",res);
  }
}
