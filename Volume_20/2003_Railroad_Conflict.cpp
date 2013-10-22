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

typedef complex<double> Point;

double dot(const Point& p,const Point& q){
  return real(conj(p)*q);
}

double det(const Point& p,const Point& q){
  return imag(conj(p)*q);
}

bool on_seg(const Point& p1,const Point&p2,
	    const Point& q){
  return abs(det(p1-q,p2-q)) <= EPS && dot(p1-q,p2-q) <= 0;
}

double compute_scale(const Point& p1,const Point& p2,
	     const Point& q1,const Point& q2) {
  return det(q2-q1,q1-p1) / det(q2-q1,p2-p1);
}

Point compute_intersection(const Point& p1,const Point& p2,
			   const Point& q1,const Point& q2) {
  return p1 + (p2-p1) * det(q2-q1,q1-p1) / det(q2-q1,p2-p1);
}

int compute_location(int owner,int location){
  //owner 1:me 0:other
  //location 1:high way 0:under ground
  if(owner == 1){
    return location;
  }
  else if(owner == 0){
    return !location;
  }
}

int main(){
  int total_dataset = 0;
  while(~scanf("%d",&total_dataset)){
    for(int dataset_idx=0;dataset_idx<total_dataset;dataset_idx++){
      int xa,ya,xb,yb;
      scanf("%d %d %d %d",&xa,&ya,&xb,&yb);
      Point p1(xa,ya);
      Point p2(xb,yb);

      int n;
      scanf("%d",&n);
	
      vector<pair<double,int> > intersections;
      for(int i=0;i<n;i++){
	int xs,ys,xt,yt,owner,location;
	scanf("%d %d %d %d %d %d",&xs,&ys,&xt,&yt,&owner,&location);
	Point p3(xs,ys);
	Point p4(xt,yt);
	Point intersection = compute_intersection(p1,p2,p3,p4);
	
	if(!on_seg(p1,p2,intersection)) continue;
	double scale = compute_scale(p1,p2,p3,p4);
	int next_location = compute_location(owner,location);

	pair<double,int> tmp(scale,next_location);
	intersections.push_back(tmp);
      }

      sort(intersections.begin(),intersections.end());
      int prev = -1;
      int res = -1;
      for(int i=0;i<intersections.size();i++){
	if(prev != intersections[i].second) res++;
	prev = intersections[i].second;
      }
      printf("%d\n",res);

    }
  }
}
