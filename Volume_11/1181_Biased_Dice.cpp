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

class Dice {
public:
  int surface[6];
  enum dir {
    TOP,
    FRONT,
    REAR,
    BOTTOM,
    LEFT,
    RIGHT
  };

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
	    goto found;
	  }

	  memcpy(surface,tmp,sizeof(int)*6);
	}
      }
    }

  found:;
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
      int next[6];
      memcpy(next,surface,sizeof(int)*6);
      next[TOP] = surface[LEFT];
      next[LEFT] = surface[BOTTOM];
      next[BOTTOM] = surface[RIGHT];
      next[RIGHT] = surface[TOP];
      memcpy(surface,next,sizeof(int)*6);
  }
};


int main(){
  int n;
  while(~scanf("%d",&n)){
    if(n==0) break;

    int stage[101][3];
    
    for(int i=0;i<n;i++){
      int top,front;
      scanf("%d %d",&top,&front);
      Dice dice(top,front);

    }
  }
}
