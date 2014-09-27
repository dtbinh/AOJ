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

// bool intersectSS(const Line &s, const Line &t) {
//   return ccw(s[0],s[1],t[0]) * ccw(s[0],s[1],t[1]) <= 0 &&
//     ccw(t[0],t[1],s[0]) * ccw(t[0],t[1],s[1]) <= 0;
// }

Point crosspoint(const Line &l, const Line &m) {
  double A = cross(l[1] - l[0], m[1] - m[0]);
  double B = cross(l[1] - l[0], l[1] - m[0]);
  if (abs(A) < EPS && abs(B) < EPS) return m[0]; // same line
  if (abs(A) < EPS) assert(false); // !!!PRECONDITION NOT SATISFIED!!!
  return m[0] + B / A * (m[1] - m[0]);
}

int main(){
  const double frame_x[] = {0.0, 0.0, 0.0, 1.0};
  const double frame_y[] = {0.0, 1.0, 0.0, 0.0};
  int num_of_pegs;

  while(~scanf("%d",&num_of_pegs)){
    vector<Point> bottom;
    vector<Point> top;
    vector<Point> left;
    vector<Point> right;
    
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
	}
	else if(type == 1){
	  //top
	  x = frame_x[type] + pos;
	  y = frame_y[type];
	  top.push_back(Point(x,y));
	}
	else if(type == 2){
	  //left
	  x = frame_x[type];
	  y = frame_y[type] + pos;
	  left.push_back(Point(x,y));
	}
	else{
	  //right
	  x = frame_x[type];
	  y = frame_y[type] + pos;
	  right.push_back(Point(x,y));
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

    for(int i = 0; i < top.size(); i++){
      Point p = crosspoint(vertical[i],horizontal[i]);
      cout << p.real() << " " << p.imag() << endl;
    }
  }
}
