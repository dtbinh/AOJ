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
#include <complex>
#include <assert.h>
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;
 
static const int tx[] = {0,0,1,0,-1};
static const int ty[] = {0,-1,0,1,0};

static const double EPS = 1e-10;

int stage[11][11];
static const int H = 10;
static const int W = 10;

bool remove_large_dye(int cx,int cy);
bool can_remove_large_dye(int cx,int cy);

bool remove_medium_dye(int cx,int cy);
bool can_remove_medium_dye(int cx,int cy);

bool remove_small_dye(int cx,int cy);
bool can_remove_small_dye(int cx,int cy);

bool can_remove_large_dye(int cx,int cy) {
  if(cy < 0 || cy >= H
       || cx < 0 || cx >= W) return false;

  if(cy + 2 >= H) return false;
  if(stage[cy + 2][cx] <= 0) return false;

  if(cx + 2 >= W) return false;
  if(stage[cy][cx + 2] <= 0) return false;

  if(cy - 2 < 0) return false;
  if(stage[cy - 2][cx] <= 0) return false;

  if(cx - 2 < 0) return false;
  if(stage[cy][cx - 2] <= 0) return false;

  if(!can_remove_medium_dye(cx,cy)){
    return false;
  }

  return true;
}

bool remove_large_dye(int cx,int cy) {
  if(!can_remove_large_dye(cx,cy)) return false;

  stage[cy + 2][cx]--;
  stage[cy][cx + 2]--;
  stage[cy - 2][cx]--;
  stage[cy][cx - 2]--;
  remove_medium_dye(cx,cy);

  return true;
}

bool can_remove_medium_dye(int cx,int cy) {
  for(int dx = -1;dx <= 1;dx++){
    for(int dy = -1;dy <= 1;dy++){
      if(cy + dy < 0 || cy + dy >= H
	   || cx + dx < 0 || cx + dx >= W) return false;
      if(stage[cy + dy][cx + dx] <= 0) return false;
    }    
  }
  return true;
}

bool remove_medium_dye(int cx,int cy) {
  if(!can_remove_medium_dye(cx,cy)) return false;
  for(int dx = -1;dx <= 1;dx++){
    for(int dy = -1;dy <= 1;dy++){
      stage[cy + dy][cx + dx]--;
    }
  }
  return true;
}

bool can_remove_small_dye(int cx,int cy) {
  for(int i=0;i<5;i++){
    if(cy + ty[i] < 0 || cy + ty[i] >= H
       || cx + tx[i] < 0 || cx + tx[i] >= W) return false;
    if(stage[cy + ty[i]][cx + tx[i]] <= 0) return false;
  }
  
  return true;
}

bool remove_small_dye(int cx,int cy) {
  if(!can_remove_small_dye(cx,cy)) return false;
  for(int i=0;i<5;i++){
    stage[cy + ty[i]][cx + tx[i]]--;
  }
  return true;
}

 class State{
 public:
   int x;
   int y;
   int type;
   State(int _x,int _y,int _t)
     : x(_x),y(_y),type(_t) {}
 };

 vector<State> logs;
 vector<State> ans;
 bool check(){
   for(int y = 0; y < 10; y++){
     for(int x = 0; x < 10; x++){
       if(stage[y][x] > 0) return false;
     }
   }
   return true;
 }

 void dfs(int pos){
   if(pos > W*H) return;
   int x = pos % W;
   int y = pos / W;

   if(pos == W * H && check()){
     ans = logs;
     return;
   }

   int tmp[11][11];
   memcpy(tmp,stage,sizeof(int)*11*11);
   if(remove_small_dye(x,y)){
     logs.push_back(State(x,y,1));
     dfs(pos+1);
     logs.pop_back();
     memcpy(stage,tmp,sizeof(int)*11*11);
   }

   if(remove_medium_dye(x,y)){
     logs.push_back(State(x,y,2));
     dfs(pos+1);
     logs.pop_back();
     memcpy(stage,tmp,sizeof(int)*11*11);
   }

   if(remove_large_dye(x,y)){
     logs.push_back(State(x,y,3));
     dfs(pos+1);
     logs.pop_back();
     memcpy(stage,tmp,sizeof(int)*11*11);
   }

   dfs(pos+1);
 }

int main(){
  int n;
  while(~scanf("%d",&n)){
    logs.clear();
    for(int y = 0; y < 10; y++){
      for(int x = 0; x < 10; x++){
	int density;
	scanf("%d",&density);
	stage[y][x] = density;
      }
    }
    dfs(0);
    for(int i = 0; i < ans.size(); i++){
      printf("%d %d %d\n",ans[i].x,ans[i].y,ans[i].type);
    }
  }
}
