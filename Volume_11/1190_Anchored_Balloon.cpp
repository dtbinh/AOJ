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

struct Anchor{
  int x,y,l;
  Anchor(int _x,int _y,int _l)
    : x(_x), y(_y), l(_l) {}
};

bool check(const vector<Anchor>& anchors,
	   double x,double y,double virtical_line){
  
  for(int anchor_idx=0;anchor_idx<anchors.size();anchor_idx++){
    double bottom_line
      = sqrt((double)(anchors[anchor_idx].x - x) * (double)(anchors[anchor_idx].x - x)
	     + (double)(anchors[anchor_idx].y - y) * (double)(anchors[anchor_idx].y - y));
    double diagonal_line
      = sqrt(bottom_line * bottom_line
	     + virtical_line * virtical_line); 
    if((double)anchors[anchor_idx].l < diagonal_line){
      return false;
    }
  }
  return true;
}

double compute_height(const vector<Anchor>& anchors,
		      double x,double y){
  double max_height = 1000000.0;
  double min_height = 0.0;
  for(int round = 0;round < 50;round++){
    double mid = (max_height + min_height) / 2.0;
    if(check(anchors,x,y,mid)){
      min_height = mid;
    }
    else{
      max_height = mid;
    }
  }
  return min_height;
}

double search_x(const vector<Anchor>& anchors,
		const double y,double left, double right)
{
  for (int round = 0; round < 50; round++){
    if (compute_height(anchors,(left * 2 + right) / 3,y)
	> compute_height(anchors,(left + right * 2) / 3,y)){
      right = (left + right * 2) / 3;
    } else {
      left = (left * 2 + right) / 3;
    }
  }
  return (right + left) * 0.5;
}

double search_y(const vector<Anchor>& anchors,
		const double x,double left, double right)
{
  for (int round = 0; round < 50; round++){
    if (compute_height(anchors,x,(left * 2 + right) / 3)
	> compute_height(anchors,x,(left + right * 2) / 3)){
      right = (left + right * 2) / 3;
    } else {
      left = (left * 2 + right) / 3;
    }
  }
  return (right + left) * 0.5;
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

    double last_x = search_x(anchors,0,-200.0,200.0);
    double last_y = search_y(anchors,last_x,-200.0,200.0);
    printf("%.7lf\n",compute_height(anchors,last_x,last_y));
  }
}
