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

class Wifi {
public:
  int x;
  int y;
  int region;
  Wifi(int x,int y,int region) :
    x(x), y(y), region(region) {}
};

bool comp_x(const Wifi& s,const Wifi& t){
  return s.x < t.x;
}

bool comp_y(const Wifi& s,const Wifi& t){
  return s.y < t.y;
}

int main(){
  int N,W,H;

  while(~scanf("%d %d %d",&N,&W,&H)){
    vector<Wifi> points;
    for(int i = 0; i < N; i++){
      int x,y,region;
      scanf("%d %d %d",&x,&y,&region);
      points.push_back(Wifi(x,y,region));
    }
    
    sort(points.begin(),points.end(),comp_x);
    int max_x = 0;
    for(int i = 0; i < points.size(); i++){
      if(points[i].x - points[i].region <= max_x){
	max_x = max(points[i].x + points[i].region,max_x);
      }
    }
    
    sort(points.begin(),points.end(),comp_y);
    int max_y = 0;
    for(int i = 0; i < points.size(); i++){
      if(points[i].y - points[i].region <= max_y){
	max_y = max(points[i].y + points[i].region,max_y);
      }
    }
    
    printf("%s\n",(max_x >= W || max_y >= H) ? "Yes" : "No");
  }
}
