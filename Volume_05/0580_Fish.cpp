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
  
static const double EPS = 1e-8;
  
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};

class Cuboid{
public:
  int x[8];
  int y[8];
  int d[8];
  Cuboid(int x1,int y1,int d1,
	 int x2,int y2,int d2){
    x[0] = x1;
    y[0] = y1;
    d[0] = d1;

    x[1] = x1;
    y[1] = y2;
    d[1] = d1;

    x[2] = x2;
    y[2] = y2;
    d[2] = d1;

    x[3] = x2;
    y[3] = y1;
    d[3] = d1;

    x[4] = x1;
    y[4] = y1;
    d[4] = d2;

    x[5] = x1;
    y[5] = y2;
    d[5] = d2;

    x[6] = x2;
    y[6] = y2;
    d[6] = d2;

    x[7] = x2;
    y[7] = y1;
    d[7] = d2;
  }    

  int compute_volume(int _x[8],int _y[8],int _d[8]){
    int top_area = (_x[1] - _x[2]) * (_y[1] - _y[0]);
    int height = _d[4] - _d[0];
    return (top_area * height < 0 ? 0 : top_area * height);
  }

  int operator&(const Cuboid& c) const{
    int next_x[8];
    int next_y[8];
    int next_d[8];

    next_x[0] = max(x[0],c.x[0]);
    next_y[0] = max(y[0],c.y[0]);
    next_d[0] = max(d[0],c.d[0]);

    next_x[1] = max(x[1],c.x[1]);
    next_y[1] = min(y[1],c.y[1]);
    next_d[1] = max(d[1],c.d[1]);

    next_x[2] = min(x[2],c.x[2]);
    next_y[2] = min(y[2],c.y[2]);
    next_d[2] = max(d[2],c.d[2]);

    next_x[3] = min(x[3],c.x[3]);
    next_y[3] = max(y[3],c.y[3]);
    next_d[3] = max(d[3],c.d[3]);

    next_x[4] = max(x[4],c.x[4]);
    next_y[4] = max(y[4],c.y[4]);
    next_d[4] = min(d[4],c.d[4]);

    next_x[5] = max(x[5],c.x[5]);
    next_y[5] = min(y[5],c.y[5]);
    next_d[5] = min(d[5],c.d[5]);

    next_x[6] = min(x[6],c.x[6]);
    next_y[6] = min(y[6],c.y[6]);
    next_d[6] = min(d[6],c.d[6]);

    next_x[7] = min(x[7],c.x[7]);
    next_y[7] = max(y[7],c.y[7]);
    next_d[7] = min(d[7],c.d[7]);

    return 0;
  }

};

int main(){
  
}
