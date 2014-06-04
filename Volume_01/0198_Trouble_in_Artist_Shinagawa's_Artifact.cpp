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
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-10;

enum dir {
  TOP,
  FRONT,
  REAR,
  BOTTOM,
  LEFT,
  RIGHT
};


map<string,int> dict;

class Dice {
public:
  int surface[6];

  Dice(const vector<string>& colors){
    surface[TOP] = dict[colors[0]];
    surface[FRONT] = dict[colors[3]];
    surface[BOTTOM] = dict[colors[5]];
    surface[REAR] = dict[colors[2]];
    surface[RIGHT] = dict[colors[1]];
    surface[LEFT] = dict[colors[4]];
  }

  bool is_visited(set<string>& visited){
    bool res = true;
    for(int i=0;i<6;i++){
      for(int j=0;j<6;j++){
	for(int k=0;k<6;k++){
	  int tmp[6];
	  memcpy(tmp,surface,sizeof(int)*6);
	  
	  pitch(i);
	  yaw(j);
	  roll(k);
	  if(visited.count(getkey()) == 0){
	    res = false;
	    visited.insert(getkey());
	  }
	  memcpy(surface,tmp,sizeof(int)*6);
	}
      }
    }

    return res;
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

  string getkey(){
    string res = "";
    res.push_back('0' + surface[TOP]);
    res.push_back('0' + surface[FRONT]);
    res.push_back('0' + surface[BOTTOM]);
    res.push_back('0' + surface[REAR]);
    res.push_back('0' + surface[RIGHT]);
    res.push_back('0' + surface[LEFT]);

    return res;
  }
};

int main(){
  int n;
  dict["Red"] = 1;
  dict["Yellow"] = 2;
  dict["Blue"] = 3;
  dict["Magenta"] = 4;
  dict["Green"] = 5;
  dict["Cyan"] = 6;

  while(~scanf("%d",&n)){
    if(n == 0) break;
    set<string> visited;

    int count = 0;
    for(int i=0;i<n;i++){
      vector<string> colors;
      for(int j=0;j<6;j++){
	string color;
	cin >> color;
	colors.push_back(color);
      }
      Dice d(colors);
      if(!d.is_visited(visited)){
	count++;
      }
    }

    printf("%d\n",n - count);
  }
}
  
