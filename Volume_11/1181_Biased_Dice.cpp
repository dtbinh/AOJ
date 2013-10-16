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
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

enum dir {
  TOP,
  FRONT,
  REAR,
  BOTTOM,
  LEFT,
  RIGHT
};

class Dice {
public:
  int surface[6];

  Dice(int top,int front){
    surface[TOP] = 1;
    surface[FRONT] = 3;
    surface[BOTTOM] = 6;
    surface[REAR] = 4;
    surface[RIGHT] = 2;
    surface[LEFT] = 5;

    for(int i=0;i<4;i++){
      for(int j=0;j<4;j++){
	for(int k=0;k<4;k++){
	  int tmp[6];
	  memcpy(tmp,surface,sizeof(int)*6);
	  
	  pitch(i);
	  yaw(j);
	  roll(k);
	  if(surface[TOP] == top
	     && surface[FRONT] == front){
	    goto complete;
	  }

	  memcpy(surface,tmp,sizeof(int)*6);
	}
      }
    }

  complete:;
  }

  
  void pitch(int num){
    //FRONT,BOTTOM,REAR,TOP
    for(int i=0;i<num;i++){
      int next[6];
      memcpy(next,surface,sizeof(int)*6);
      next[FRONT] = surface[BOTTOM];
      next[BOTTOM] = surface[REAR];
      next[REAR] = surface[TOP];
      next[TOP] = surface[FRONT];
      memcpy(surface,next,sizeof(int)*6);
    }
  }
  void yaw(int num){
    //LEFT,FRONT,RIGHT,REAR
    for(int i=0;i<num;i++){
      int next[6];
      memcpy(next,surface,sizeof(int)*6);
      next[LEFT] = surface[FRONT];
      next[FRONT] = surface[RIGHT];
      next[RIGHT] = surface[REAR];
      next[REAR] = surface[LEFT];
      memcpy(surface,next,sizeof(int)*6);
    }
  }
  void roll(int num){
    //TOP,LEFT,BOTTOM,RIGHT
    for(int i=0;i<num;i++){
      int next[6];
      memcpy(next,surface,sizeof(int)*6);
      next[TOP] = surface[LEFT];
      next[LEFT] = surface[BOTTOM];
      next[BOTTOM] = surface[RIGHT];
      next[RIGHT] = surface[TOP];
      memcpy(surface,next,sizeof(int)*6);
    }
  }
};

deque<int> stage[250][250];

void dfs(Dice dice,int sx,int sy){
  //check stage
  //1 2
  // 0
  //3 4
  bool isok = false;

  for(int num=6;num>=4;num--){
    if(dice.surface[FRONT] == num){
      int dx = sx;
      int dy = sy - 1;
      if(stage[dy][dx].size() < stage[sy][sx].size()){
	dice.pitch(3);
	dfs(dice,dx,dy);
	isok = true;
	goto found;
      }
    }
    else if(dice.surface[REAR] == num){
      int dx = sx;
      int dy = sy + 1;
      if(stage[dy][dx].size() < stage[sy][sx].size()){
	dice.pitch(1);
	dfs(dice,dx,dy);
	isok = true;
	goto found;
      }
    }
    else if(dice.surface[LEFT] == num){
      int dx = sx - 1;
      int dy = sy;
      if(stage[dy][dx].size() < stage[sy][sx].size()){
	dice.roll(3);
	dfs(dice,dx,dy);
	isok = true;
	goto found;
	      
      }
    }
    else if(dice.surface[RIGHT] == num){
      int dx = sx + 1;
      int dy = sy;
      if(stage[dy][dx].size() < stage[sy][sx].size()){
	dice.roll(1);
	dfs(dice,dx,dy);
	isok = true;
	goto found;
      }
    }
  }
 found:;
  if(!isok){
    stage[sy][sx].push_back(dice.surface[TOP]);
  }
}

int main(){
  int n;
  while(~scanf("%d",&n)){
    if(n==0) break;

    int sx = 250/2;
    int sy = 250/2;

    for(int y=0;y<250;y++){
      for(int x=0;x<250;x++){
	stage[y][x].clear();
      }
    }

    for(int i=0;i<n;i++){
      int top,front;
      scanf("%d %d",&top,&front);
      Dice dice(top,front);
      dfs(dice,sx,sy);
    }

    int freq[7];
    memset(freq,0,sizeof(freq));
    
    for(int y=0;y<250;y++){
      for(int x=0;x<250;x++){
	if(stage[y][x].size() > 0){
	  freq[stage[y][x][stage[y][x].size()-1]]++;
	}
      }
    }

    for(int i=1;i<=6;i++){
      printf("%s%d",i==1 ? "" : " ", freq[i]);
    }
    printf("\n");
  }
}
