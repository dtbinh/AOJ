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
#include <complex>
#include <assert.h>
  
using namespace std;
  
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P> PP;
  
static const double EPS = 1e-8;

typedef complex<double> Point;

double cross(const Point& a, const Point& b) {
  return imag(conj(a)*b);
}

double dot(const Point& a, const Point& b) {
  return real(conj(a)*b);
}

struct Line : public vector<Point> {
  Line(const Point &a, const Point &b) {
    push_back(a); push_back(b);
  }
};

Point crosspoint(const Line &l, const Line &m) {
  double A = cross(l[1] - l[0], m[1] - m[0]);
  double B = cross(l[1] - l[0], l[1] - m[0]);
  if (abs(A) < EPS && abs(B) < EPS) return m[0]; // same line
  if (abs(A) < EPS) assert(false); // !!!PRECONDITION NOT SATISFIED!!!
  return m[0] + B / A * (m[1] - m[0]);
}

double compute_area(const Point& a,const Point& b,
		    const Point& c,const Point& d){
  return 1.0/2.0 * ((a.real() - b.real())*(a.imag() + b.imag())
		    + (b.real() - c.real())*(b.imag() + c.imag())
		    + (c.real() - d.real())*(c.imag() + d.imag())
		    + (d.real() - a.real())*(d.imag() + a.imag()));
}

int main(){
  const double frame_x[] = {0.0, 0.0, 0.0, 1.0};
  const double frame_y[] = {0.0, 1.0, 0.0, 0.0};
  int num_of_pegs;

  while(~scanf("%d",&num_of_pegs)){
    if(num_of_pegs == 0) break;

    vector<Point> bottom;
    vector<Point> top;
    vector<Point> left;
    vector<Point> right;

    Point points[50][50];  
    points[0][0] = Point(0,0);
    points[0][num_of_pegs + 1] = Point(0,1);
    points[num_of_pegs + 1][0] = Point(1,0);
    points[num_of_pegs + 1][num_of_pegs + 1] = Point(1,1);

    for(int type = 0; type < 4; type++){
      for(int peg_i = 0; peg_i < num_of_pegs; peg_i++){
	double pos;
	scanf("%lf",&pos);
	double x,y;
	if(type == 0){
	  //bottom
	  x = frame_x[type] + pos;
	  y = frame_y[type];
	  bottom.push_back(Point(x,y));
	  points[peg_i+1][0] = Point(x,y);
	}
	else if(type == 1){
	  //top
	  x = frame_x[type] + pos;
	  y = frame_y[type];
	  top.push_back(Point(x,y));
	  points[peg_i+1][num_of_pegs + 1] = Point(x,y);
	}
	else if(type == 2){
	  //left
	  x = frame_x[type];
	  y = frame_y[type] + pos;
	  left.push_back(Point(x,y));
	  points[0][peg_i + 1] = Point(x,y);
	}
	else{
	  //right
	  x = frame_x[type];
	  y = frame_y[type] + pos;
	  right.push_back(Point(x,y));
	  points[num_of_pegs + 1][peg_i + 1] = Point(x,y);
	}
      }
    }

    vector<Line> vertical;
    vector<Line> horizontal;

    for(int i = 0; i < top.size(); i++){
      Line line(top[i],bottom[i]);
      vertical.push_back(line);
    } 
    for(int i = 0; i < left.size(); i++){
      Line line(left[i],right[i]);
      horizontal.push_back(line);
    } 

    for(int i = 0; i < vertical.size(); i++){
      for(int j = 0; j < horizontal.size(); j++){
	Point p = crosspoint(vertical[i],horizontal[j]);
	points[i+1][j+1] = p;
      }
    }

    double max_area = 0.0;
    for(int x = 0; x+1 < num_of_pegs + 2; x++){
      for(int y = 0; y+1 < num_of_pegs + 2; y++){
	
	Point left_bottom = points[x][y];
	Point right_bottom = points[x+1][y];
	Point left_top = points[x][y+1];
	Point right_top = points[x+1][y+1];
	max_area = max(max_area,
		       compute_area(left_bottom,right_bottom,right_top,left_top));
      }
    }
    printf("%.7lf\n",max_area);
  }
}
