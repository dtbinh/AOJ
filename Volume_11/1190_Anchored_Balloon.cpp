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
 
static const double EPS = 1e-12;

struct Anchor{
  int x,y,l;
  Anchor(int _x,int _y,int _l)
    : x(_x), y(_y), l(_l) {}
};

double check(const vector<Anchor>& anchors,
	     double x,double y){

  double res = 100000000.0;
  for(int anchor_idx=0;anchor_idx<anchors.size();anchor_idx++){
    double bottom_line
      = (double)(anchors[anchor_idx].x - x) * (double)(anchors[anchor_idx].x - x)
      + (double)(anchors[anchor_idx].y - y) * (double)(anchors[anchor_idx].y - y);
    double capacity = anchors[anchor_idx].l * anchors[anchor_idx].l;
    res = min(res,capacity - bottom_line);
  }
  return res;
}

double search(const vector<Anchor>& anchors,
	      const double x,double left, double right)
{
  for (int round = 0; round < 100; round++){
    if (check(anchors,x,(left * 2 + right) / 3)
	> check(anchors,x,(left + right * 2) / 3)){
      right = (left + right * 2) / 3;
    } else {
      left = (left * 2 + right) / 3;
    }
  }
  return check(anchors,x,(right + left) * 0.5);
}

int main(){
  int total_anchors;
  while(~scanf("%d",&total_anchors)){
    if(total_anchors == 0) break;

    vector<Anchor> anchors;
    for(int anchor_idx=0;anchor_idx<total_anchors;anchor_idx++){
      int x,y,l;
      scanf("%d %d %d",&x,&y,&l);
      anchors.push_back(Anchor(x,y,l));
    }

    double left = -100.0;
    double right = 100.0;
    for(int round = 0;round < 100; round++){
      if (search(anchors,(left * 2 + right) / 3,-100.0,100.0)
	  > search(anchors,(left + right * 2) / 3,-100.0,100.0)){
	right = (left + right * 2) / 3;
      } else {
	left = (left * 2 + right) / 3;
      }
    }
    double res = search(anchors,right,-100,100.0);
    printf("%.7lf\n",sqrt(res));
  }
}
