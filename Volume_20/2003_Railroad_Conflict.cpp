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

struct Point {
  double x;
  double y;
};

bool compute_intersection(const Point& p1,
	       const Point& p2,
	       const Point& p3,
	       const Point& p4,
	       Point& intersection){
  double ksi, eta, delta;
  double ramda, mu;

  ksi = ( p4.y-p3.y )*( p4.x-p1.x ) - 
    ( p4.x-p3.x )*( p4.y-p1.y );

  eta = ( p2.x-p1.x )*( p4.y-p1.y ) -
    ( p2.y-p1.y )*( p4.x-p1.x );

  delta = ( p2.x-p1.x )*( p4.y-p3.y ) -
    ( p2.y-p1.y )*( p4.x-p3.x );

  ramda = ksi / delta;
  mu = eta / delta;

  if ( ( ramda >= 0 && ramda <= 1 ) && ( mu >= 0 && mu <= 1 ) )
    {
      intersection.x = p1.x + ramda*( p2.x-p1.x );
      intersection.y = p1.y + ramda*( p2.y-p1.y );
      return true;
    }

  return false;
}

int main(){
  int total_dataset = 0;
  while(~scanf("%d",&total_dataset)){
    for(int dataset_idx=0;dataset_idx<total_dataset;dataset_idx++){
      int xa,ya,xb,yb;
      scanf("%d %d %d %d",&xa,&ya,&xb,&yb);
      Point p1 = {xa,ya};
      Point p2 = {xb,yb};

      int n;
      scanf("%d",&n);
      for(int i=0;i<n;i++){
	int xs,ys,xt,yt,owner,location;
	scanf("%d %d %d %d %d %d",&xs,&ys,&xt,&yt,&owner,&location);
	Point p3 = {xs,ys};
	Point p4 = {xt,yt};
	Point intersection;
	compute_intersection(p1,p2,p3,p4,intersection);
	printf("%lf %lf\n",intersection.x,intersection.y);
      }
    }
  }
}
