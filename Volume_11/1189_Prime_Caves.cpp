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

struct Stage{
  int num;
  
};

int main(){
  map<P,int> stage; //key:x,y

  int x = 0;
  int y = 0;
  int dir = 1;
  for(int round = 1; round <= 50;round++){
    stage[P(y,x)] = round;

    int prev_dir = dir;
    if(round > 1) dir = (dir + 3) % 4;
    int dx = x + tx[dir];
    int dy = y + ty[dir];
    if(stage.find(P(dy,dx)) != stage.end()){
      dir = prev_dir;
    }
    dx = x + tx[dir];
    dy = y + ty[dir];
    x = dx;
    y = dy;

  }
  for(map<P,int>::iterator it = stage.begin();
      it != stage.end();
      it++){
    printf("x:%d y:%d num:%d\n",it->first.second,it->first.first,it->second);
  }
}
