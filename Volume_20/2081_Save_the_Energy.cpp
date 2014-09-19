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
 
static const double EPS = 1e-10;

class Point {
public:
  double _x;
  double _y;
  double _z;
  Point (double x,double y,double z) :
    _x(x), _y(y), _z(z) {}
  Point operator-(const Point& p) const {
    return Point(_x - p._x,
		 _y - p._y,
		 _z - p._z);
  }
  Point operator+(const Point& p) const {
    return Point(_x + p._x,
		 _y + p._y,
		 _z + p._z);
  }
  Point operator*(const double t) const {
    return Point(_x * t,
		 _y * t,
		 _z * t);
  }
  Point operator*(const Point&p) const {
    return Point(_x * p._x,
		 _y * p._y,
		 _z * p._z);
  }
  Point operator/(const double t) const {
    return Point(_x / t,
		 _y / t,
		 _z / t);
  }
  void print_vec() const{
    printf("(%lf,%lf,%lf)\n",_x,_y,_z);
  }
};

class Line : public vector<Point> {
public:
  Line(const Point& p1,const Point& p2) {
    push_back(p1);
    push_back(p2);
  }
};

double norm(const Point& p){
  return sqrt(p._x * p._x + p._y * p._y + p._z * p._z);
}

Point unit(const Point& p){
  return p/norm(p);
}

double dot(const Point& p1,const Point& p2){
  return p1._x * p2._x + p1._y * p2._y + p1._z * p2._z;
}

Point cross(const Point& p1,const Point& p2){
  return Point(p1._y * p2._z - p1._z * p2._y,
	       p1._z * p2._x - p1._x * p2._z,
	       p1._x * p2._y - p1._y * p2._x);
}

Point projection(const Line& l,const Point& p){
  double t = dot(p - l[0],l[0]-l[1]) / norm(l[0] - l[1]);
  return l[0] + unit(l[0] - l[1]) * t;
}

bool EQ(const Point& s,const Point& t) {
  if((t._x - EPS <= s._x && s._x <= t._x + EPS)
     && (t._y - EPS <= s._y && s._y <= t._y + EPS)
     && (t._z - EPS <= s._z && s._z <= t._z + EPS)) return true;
  return false;
}

bool parallelLL(const Line &l, const Line &m) {
  return EQ(cross(l[1]-l[0], m[1]-m[0]),Point(0,0,0));
}

bool intersectLP(const Line &l, const Point &p) {
  return (norm(cross(l[1]-p, l[0]-p)) < EPS);
}

double distanceLP(const Line& l,const Point& p){
  if(intersectLP(l,p)) return 0;
  return norm(p - projection(l,p));
}

double distanceLL(const Line& l,const Line& m){
  if(parallelLL(l,m)) return distanceLP(l,m[0]);

  Point V1 = l[1] - l[0];
  Point V2 = m[1] - m[0];
  Point V3 = m[0]-l[0];
  double dist = abs(dot(cross(V1,V2),V3)/norm(cross(V1,V2)));
  return dist;
}

double dp[105][105];

int main(){
  int num_of_straight_paths;
  while(~scanf("%d",&num_of_straight_paths)){
    if(num_of_straight_paths == 0) break;

    double sx,sy,sz;
    double gx,gy,gz;
    scanf("%lf %lf %lf",&sx,&sy,&sz);
    scanf("%lf %lf %lf",&gx,&gy,&gz);
    
    vector<Line> lines;
    for(int path_i = 0; path_i < num_of_straight_paths; path_i++){
      double x[2],y[2],z[2];
      for(int i = 0; i < 2; i++){
	scanf("%lf %lf %lf",&x[i],&y[i],&z[i]);
      }
      lines.push_back(Line(Point(x[0],y[0],z[0]),
			   Point(x[1],y[1],z[1])));

    }

    memset(dp,0,sizeof(dp));

    dp[0][num_of_straight_paths+1] 
      = dp[num_of_straight_paths+1][0]
      = norm(Point(sx,sy,sz) - Point(gx,gy,gz));

    for(int path_i = 0; path_i < num_of_straight_paths; path_i++){
      dp[0][path_i + 1]
	= dp[path_i + 1][0]
	= distanceLP(lines[path_i],Point(sx,sy,sz));
      // printf("s to... %d %lf\n",path_i + 1,dp[0][path_i+1]);
    }

    for(int path_i = 0; path_i < num_of_straight_paths; path_i++){
      dp[num_of_straight_paths + 1][path_i + 1]
	= dp[path_i + 1][num_of_straight_paths + 1]
	= distanceLP(lines[path_i],Point(gx,gy,gz));
      // printf("g to... %d %lf\n",path_i + 1,dp[path_i + 1][num_of_straight_paths + 1]);
    }

    for(int path_i = 0; path_i < num_of_straight_paths; path_i++){
      for(int path_j = path_i + 1; path_j < num_of_straight_paths; path_j++){
	dp[path_i + 1][path_j + 1]
	  = dp[path_j + 1][path_i + 1]
	  = distanceLL(lines[path_i],lines[path_j]);
	// printf("LL %d %d %lf\n",path_i + 1,path_j + 1,distanceLL(lines[path_i],lines[path_j]));
      }
    }

    for(int k=0;k<=num_of_straight_paths+1;k++){
      for(int i=0;i<=num_of_straight_paths+1;i++){
	for(int j=0;j<=num_of_straight_paths+1;j++){
	  dp[i][j] = min(dp[i][k] + dp[k][j],dp[i][j]);
	}
      }
    }

    // for(int i=0;i<=num_of_straight_paths+1;i++){
    //   for(int j=i+1;j<=num_of_straight_paths+1;j++){
    // 	printf("%d %d %lf\n",i,j,dp[i][j]);
    //   }
    // }

    printf("%lf\n",dp[0][num_of_straight_paths+1]);
  }
}
