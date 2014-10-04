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
  
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};

typedef complex<double> Point;

bool EQ(const Point& p,const Point& q){
  if(abs(p.imag() - q.imag()) <= EPS
     && abs(p.real() - q.real()) <= EPS) return true;
  return false;
}

int main(){
  int N;
  while(~scanf("%d",&N)){
    vector<Point> points;

    Point center_of_gravity(0,0);
    for(int point_i = 0; point_i < N; point_i++){
      double x,y;
      scanf("%lf %lf",&x,&y);
      points.push_back(Point(x,y));
      center_of_gravity += Point(x,y);
    }
    center_of_gravity /= N;

    bool isok = true;
    for(int point_i = 0; point_i < N; point_i++){
      Point g = (points[point_i] + points[(point_i + N/2) % N]) / 2.0;
      if(!EQ(center_of_gravity,g)){
	isok = false;
	break;
      }
    }
    if(isok){
      printf("%.7lf %.7lf\n",
	     center_of_gravity.real(),
	     center_of_gravity.imag());
    }
    else{
      printf("NA\n");
    }
  }
}
