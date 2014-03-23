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

bool check(const vector<Anchor>& anchors,
	   double x,double y,double virtical_line){
  
  for(int anchor_idx=0;anchor_idx<anchors.size();anchor_idx++){
    double bottom_line
      = sqrt((double)(anchors[anchor_idx].x - x) * (double)(anchors[anchor_idx].x - x)
	     + (double)(anchors[anchor_idx].y - y) * (double)(anchors[anchor_idx].y - y));
    double diagonal_line
      = sqrt(bottom_line * bottom_line
	     + virtical_line * virtical_line); 
    if((double)anchors[anchor_idx].l < diagonal_line + EPS){
      return false;
    }
  }
  return true;
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

    double res = 0.0;
    for(double y=-100;y<=100;y+=0.1){
      for(double x=-100;x<=100;x+=0.1){
	double max_height = 1000000.0;
	double min_height = 1.0;
	for(int round = 0;round < 50;round++){
	  double mid = (max_height + min_height) / 2.0;
	  if(check(anchors,x,y,mid)){
	    min_height = mid;
	  }
	  else{
	    max_height = mid;
	  }
	}

	res = max(min_height,res);
      }
    }
    printf("%lf\n",res);
  }
}
