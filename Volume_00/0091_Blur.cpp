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

class State{
public:
  int x;
  int y;
  int type;
  State(int _x,int _y,int _t)
    : x(_x),y(_y),type(_t) {}
};

vector<State> logs;

bool check(){
  for(int y = 0; y < 10; y++){
    for(int x = 0; x < 10; x++){
      if(stage[y][x] > 0) return false;
    }
  }
  return true;
}

class Strategy{
public:
  virtual bool remove(int x,int y) = 0;
};

class StrategySmall : public Strategy {
private:
  bool can_remove_small_dye(int cx,int cy) {
    for(int i=0;i<5;i++){
      if(cy + ty[i] < 0 || cy + ty[i] >= H
	 || cx + tx[i] < 0 || cx + tx[i] >= W) return false;
      if(stage[cy + ty[i]][cx + tx[i]] <= 0) return false;
    }
    
    return true;
  }
public:
  bool remove(int cx,int cy) {
    if(!can_remove_small_dye(cx,cy)) return false;
    for(int i=0;i<5;i++){
      stage[cy + ty[i]][cx + tx[i]]--;
    }
    return true;
  }
};

class StrategyMedium : public Strategy {
private:
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
public:
  bool remove(int cx,int cy) {
    if(!can_remove_medium_dye(cx,cy)) return false;
    for(int dx = -1;dx <= 1;dx++){
      for(int dy = -1;dy <= 1;dy++){
	stage[cy + dy][cx + dx]--;
      }
    }
    return true;
  }
};

class StrategyLarge : public Strategy {
private:
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
    
    if(can_remove_medium_dye(cx,cy)){
      return false;
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

public:
  bool remove(int cx,int cy) {
    if(!can_remove_large_dye(cx,cy)) return false;
    
    stage[cy + 2][cx]--;
    stage[cy][cx + 2]--;
    stage[cy - 2][cx]--;
    stage[cy][cx - 2]--;
    remove_medium_dye(cx,cy);
    
    return true;
  }
};

class None : public Strategy{
public:
  bool remove(int x,int y){
    return true;
  }
};

StrategyMedium stm;
StrategyLarge stl;
StrategySmall sts;
None none;
Strategy* dye[5];

void dfs(int pos,int life){
  if(pos > W*H) return;
  if(life < 0) return;

  int x = pos % W;
  int y = pos / W;

  if(pos == W * H && check()){
    for(int i = 0; i < logs.size(); i++){
      printf("%d %d %d\n",logs[i].x,logs[i].y,logs[i].type);
    }
    // exit(0);
    return;
  }
  
  int tmp[11][11];
  memcpy(tmp,stage,sizeof(int)*11*11);

  for(int S=0;S<=(1<<3)-1;S++){
    bool isok = true;

    int count =0;
    for(int i=0;i<3;i++){
      if(S & (1<<i)){
	isok &= dye[i+1]->remove(x,y);
	logs.push_back(State(x,y,i+1));
	count++;
      }
    }

    if(isok){
      dfs(pos+1,life - count);
    }
    while(count-- > 0){
      logs.pop_back();
    }
    memcpy(stage,tmp,sizeof(int)*11*11);
  }
}

int main(){
  int n;
  dye[0] = &none;
  dye[1] = &sts;
  dye[2] = &stm;
  dye[3] = &stl;

  while(~scanf("%d",&n)){
    logs.clear();

    for(int y = 0; y < 10; y++){
      for(int x = 0; x < 10; x++){
	int density;
	scanf("%d",&density);
	stage[y][x] = density;
      }
    }
    dfs(0,n);
  }
}
