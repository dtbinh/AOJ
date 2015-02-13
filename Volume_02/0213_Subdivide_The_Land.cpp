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

int stage_w,stage_h,total_buyers;
int ans[50][50];

void disp(int stage[50][50]){
  for(int y = 0; y < stage_h; y++){
    for(int x = 0; x < stage_w; x++){
      printf("%d%s",stage[y][x], x == stage_w - 1 ? "" : " ");
    }
    printf("\n");
  }
}

bool check(int stage[50][50]){
  for(int y = 0; y < stage_h; y++){
    for(int x = 0; x < stage_w; x++){
      if(stage[y][x] == 0) return false;
    }
  }
  memcpy(ans,stage,sizeof(int)*50*50);
  return true;
}

int dfs(int id,int areas[50],P occupied[50],int stage[50][50]){
  if(id > total_buyers){
    return check(stage) ? 1 : 0;
  }

  int res = 0;
  for(int w = 1; w <= areas[id]; w++){
    int h = areas[id] / w;
    if(h * w != areas[id]) continue;
    int cx = occupied[id].first;
    int cy = occupied[id].second;

    for(int lx = cx - w + 1; lx <= cx; lx++){
      if(lx < 0) continue;

      int rx = lx + w - 1;

      if(rx >= stage_w) continue;
      for(int ly = cy - h + 1; ly <= cy; ly++){
	if(ly < 0) continue;

	int ry = ly + h - 1;
	if(ry >= stage_h) continue;

	int prev[50][50];
	memcpy(prev,stage,sizeof(int)*50*50);
	for(int x = lx; x <= rx; x++){
	  for(int y = ly; y <= ry; y++){
	    if(stage[y][x] == 0){
	      stage[y][x] = id;
	    }
	    else if(stage[y][x] != id){
	      goto fail;
	    }
	  }
	}
	res += dfs(id + 1,areas,occupied,stage);
      fail:;
	memcpy(stage,prev,sizeof(int)*50*50);
      }
    }
  }

  return res;
}

int main(){

  while(~scanf("%d %d %d",&stage_w,&stage_h,&total_buyers)){
    if(stage_w == 0 && stage_h == 0) break;

    int stage[50][50];
    int areas[50];
    for(int buyer_i = 0; buyer_i < total_buyers; buyer_i++){
      int id;
      int area;
      scanf("%d %d",&id,&area);
      areas[id] = area;
    }

    P occupied[50];
    for(int y = 0; y < stage_h; y++){
      for(int x = 0; x < stage_w; x++){
	scanf("%d",&stage[y][x]);
	if(stage[y][x] != 0){
	  occupied[stage[y][x]] = P(x,y);
	}
      }
    }

    if(dfs(1,areas,occupied,stage) == 1){
      disp(ans);
    }
    else{
      printf("NA\n");
    }
  }
}
