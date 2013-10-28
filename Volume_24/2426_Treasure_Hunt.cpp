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

struct Point {
  int x;
  int y;
  Point(int _x,int _y) : x(_x),y(_y) {}
  bool operator<(const Point& p) const{
    return x < p.x;
  }
};

int main(){
  int total_treasure,total_region;
  
  while(~scanf("%d %d",&total_treasure,&total_region)){
    vector<Point> treasures;
    vector<int> treasures_x;

    for(int i=0;i<total_treasure;i++){
      int x,y;
      scanf("%d %d",&x,&y);
      treasures.push_back(Point(x,y));
      treasures_x.push_back(x);
    }
    sort(treasures.begin(),treasures.end());
    sort(treasures_x.begin(),treasures_x.end());

    for(int i=0;i<total_region;i++){
      int x[2],y[2];
      scanf("%d %d %d %d",x,y,x+1,y+1);
      int left_idx = lower_bound(treasures_x.begin(),treasures_x.end(),x[0]) - treasures_x.begin();
      int right_idx = upper_bound(treasures_x.begin(),treasures_x.end(),x[1]) - treasures_x.begin() - 1;

      int count = 0;
      for(int j=left_idx;j<=right_idx;j++){
      	if(treasures[j].y < y[0] || y[1] < treasures[j].y) continue;
      	count++;
      }
      printf("%d\n",count);
    }
  }
}
