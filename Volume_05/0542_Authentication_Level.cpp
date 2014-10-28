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

int dfs(int sx,int sy,int W,int H,int auth_level,int office_i){
  if(visited[sy][sx]) return 0;
  if(auth_level < rooms[office_i][sy][sx]) return 0;

  visited[sy][sx] = true;
  int res = 1;
  for(int i = 0; i < 4; i++){
    int dx = sx + tx[i];
    int dy = sy + ty[i];
    if(dx < 0 || dx >= W || dy < 0 || dy >= H) continue;
    if(auth_level < rooms[office_i][dy][dx]) continue;
    res += dfs(dx,dy,W,H,auth_level,office_i);
  }
  return res;
}

int main(){
  int have_to_visit_rooms;
  while(~scanf("%d",&have_to_visit_rooms)){
    int elevator_x[2];
    int elevator_y[2];
    int W[2];
    int H[2];
    vector<int> auth_candidates;
    for(int office_i = 0; office_i < 2; office_i++){
      scanf("%d %d %d %d",&W[office_i],&H[office_i],
	    &elevator_x[office_i],&elevator_y[office_i]);
      elevator_x[office_i]--;
      elevator_y[office_i]--;

      for(int y = 0; y < H[office_i]; y++){
	for(int x = 0; x < W[office_i]; x++){
	  scanf("%d",&rooms[office_i][y][x]);
	  if(office_i == 1){
	    auth_candidates.push_back(rooms[office_i][y][x]);
	  }
	}
      }
    }

    sort(auth_candidates.begin(),auth_candidates.end());
    auth_candidates.erase(unique(auth_candidates.begin(),auth_candidates.end()),
			  auth_candidates.end());
    int res = 1000000000;
    for(int auth_i = 0; auth_i < auth_candidates.size(); auth_i++){
      int first_auth = auth_candidates[auth_i];

      int lhs = 0; 
      int rhs = 1000000000;

      for(int round = 0; round < 30; round++){
	int mid = lhs + (rhs - lhs) / 2;
	int sum = 0;
	for(int office_i = 0; office_i < 2; office_i++){
	  memset(visited,false,sizeof(visited));
	  if(office_i == 0){
	    sum += dfs(elevator_x[office_i],
		       elevator_y[office_i],
		       W[office_i],H[office_i],mid,office_i);
	  }
	  else{
	    sum += dfs(elevator_x[office_i],
		       elevator_y[office_i],
		       W[office_i],H[office_i],first_auth,office_i);
	  }
	}
	
	if(sum < have_to_visit_rooms){
	  lhs = mid;
	}
	else{
	  rhs = mid;
	  res = min(rhs + first_auth,res);	  
	}
      }
    }

    printf("%d\n",res);
  }
}
