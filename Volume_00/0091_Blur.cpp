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
 
static const int tx[] = {+0,+0,+1,+0,-1};
static const int ty[] = {+0,-1,+0,+1,+0};

static const double EPS = 1e-10;

char stage[10][10];
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
int sum;

class Strategy{
public:
  virtual bool remove(int x,int y) = 0;
  virtual void recover(int x,int y) = 0;
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
  void recover(int cx,int cy) {
    for(int i=0;i<5;i++){
      stage[cy + ty[i]][cx + tx[i]]++;
    }
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
  void recover(int cx,int cy) {
    for(int dx = -1;dx <= 1;dx++){
      for(int dy = -1;dy <= 1;dy++){
	stage[cy + dy][cx + dx]++;
      }
    }
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
    
    if(!can_remove_medium_dye(cx,cy)){
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
  void recover(int cx,int cy) {
    stage[cy + 2][cx]++;
    stage[cy][cx + 2]++;
    stage[cy - 2][cx]++;
    stage[cy][cx - 2]++;
    for(int dx = -1;dx <= 1;dx++){
      for(int dy = -1;dy <= 1;dy++){
	stage[cy + dy][cx + dx]++;
      }
    }
  }
};

class None : public Strategy{
public:
  bool remove(int x,int y){
    return true;
  }
  void recover(int x,int y){
    return;
  }
};

Strategy* dye[5];

void disp(){
  for(int y=0; y < H; y++){
    for(int x=0; x < W; x++){
      printf("%d ",stage[y][x]);
    }
    printf("\n");
  }
}

bool dfs(int pos,int life){
  if(life == 0 && sum == 0){
    return true;
  }

  else{
    if(life == 0) return false;
    if(pos >= W*H) return false;
  }

  int x = pos % W;
  int y = pos / W;

  if(stage[y][x] == 0){
    if(dfs(pos+1,life)){
      return true;
    }
  }

  for(int i=2;i>=0;i--){
    int cx = x + (i <= 1 ? 1 : 2);
    int cy = y + (i <= 1 ? 1 : 2);
    if(dye[i+1]->remove(cx,cy)){
      logs.push_back(State(cx,cy,i+1));
      sum -= (i+1) * 5 - i;
      if(dfs(pos,life-1)){
	return true;
      }
      sum += (i+1) * 5 - i;
      logs.pop_back();
      dye[i+1]->recover(cx,cy);
    }
  }
  return false;
}

int main(){
  int n;
  StrategyMedium stm;
  StrategyLarge stl;
  StrategySmall sts;
  None none;

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
	sum += density;
      }
    }
    dfs(0,n);
    for(int i = 0; i < logs.size(); i++){
      printf("%d %d %d\n",logs[i].x,logs[i].y,logs[i].type);
    }
  }
}
