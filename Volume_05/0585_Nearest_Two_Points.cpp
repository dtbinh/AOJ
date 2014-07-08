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
typedef pair <int,P> PP;
  
static const double EPS = 1e-8;
  
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};

class Point{
public:
  int x;
  int y;
  Point(int _x,int _y) : x(_x),y(_y) {}
  bool operator<(const int h) const{
    return y < h;
  }

  bool operator==(const Point& p) const {
    return (x == p.x && y == p.y);
  }
};

bool comp_x(const Point& p1,const Point& p2) {
  if(p1.x != p2.x){
    return p1.x < p2.x;
  }else{
    return p1.y < p2.y;
  }
}

bool comp_y(const Point& p1,const Point& p2) {
  if(p1.y != p2.y){
    return p1.y < p2.y;
  }else{
    return p1.x < p2.x;
  }
}

int compute_distance(const Point& p1,const Point& p2) {
  return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

int main(){
  int total_points;
  while(~scanf("%d",&total_points)){

    vector<Point> points_sort_by_x;
    vector<Point> points_sort_by_y;
    
    for(int i=0;i<total_points;i++){
      int x;
      int y;
      cin >> x >> y;
      points_sort_by_x.push_back(Point(x,y));
      points_sort_by_y.push_back(Point(x,y));
    }
    
    int res = INF;
    sort(points_sort_by_x.begin(),points_sort_by_x.end(),comp_x);
    sort(points_sort_by_y.begin(),points_sort_by_y.end(),comp_y);
    
    for(int i=0;i+1<points_sort_by_x.size();i++){
      res = min(compute_distance(points_sort_by_x[i],points_sort_by_x[i+1]),res);
      int y_idx = lower_bound(points_sort_by_y.begin(),points_sort_by_y.end(),points_sort_by_x[i].y) - points_sort_by_y.begin();

      for(int j=y_idx;j<points_sort_by_y.size();j++){
	if(points_sort_by_y[j] == points_sort_by_x[i]){
	  if(j > 0) {
	    res = min(compute_distance(points_sort_by_x[i],points_sort_by_y[j-1]),res);
	  }
	  if(j < points_sort_by_y.size() - 1){
	    res = min(compute_distance(points_sort_by_x[i],points_sort_by_y[j+1]),res);
	  }

	  break;
	}
      }
    }
    printf("%d\n",res);
  }
}
