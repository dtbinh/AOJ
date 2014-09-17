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

class Point {
public:
  int _x;
  int _y;
  int _z;
  Point(int x,int y,int z) :
    _x(x), _y(y), _z(z) {}
};

class Line {
public:
  vector<Point> l;
  Line(const Point& p1,const Point& p2) {
    l.push_back(p1);
    l.push_back(p2);
  }
};

int main(){
  int num_of_straight_paths;
  while(~scanf("%d",&num_of_straight_paths)){
    int sx,sy,sz;
    int gx,gy,gz;
    scanf("%d %d %d",&sx,&sy,&sz);
    scanf("%d %d %d",&gx,&gy,&gz);

    vector<Line> lines;
    for(int path_i = 0; path_i < num_of_straight_paths; path_i++){
      int x[2],y[2],z[2];
      for(int i = 0; i < 2; i++){
	scanf("%d %d %d",&x[i],&y[i],&z[i]);
      }
      lines.push_back(Line(Point(x[0],y[0],z[0]),
			   Point(x[1],y[1],z[1])));
    }
  }
}
