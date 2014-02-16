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
 
const static int tx[] = {0,1,1,1,0,-1,-1,-1};
const static int ty[] = {-1,-1,0,1,1,1,0,-1};
 
static const double EPS = 1e-12;

class Point{
public:
  int x;
  int y;
  Point(int _x,int _y) : x(_x),y(_y){}
  bool operator<(const Point& p) const{
    if(x==p.x) return y < p.y;
    else return x < p.x;
  }
  bool operator>(const Point& p) const{
    if(x==p.x) return y > p.y;
    else return x > p.x;
  }
  bool operator==(const Point& p) const{
    return (x == p.x && y == p.y);
  }
};

int dfs(int x,int y,
	map<int,vector<int> >& x2y,
	map<int,vector<int> >& y2x,
	map<Point,bool>& visited){
  
  map<Point,bool>::iterator it;
  if((it = visited.find(Point(x,y))) != visited.end()){
    return 0;
  }

  visited[Point(x,y)] = true;
  int res = 1;

  for(int i=0;i<x2y[x].size();i++){
    int next_y = x2y[x][i];
    res += dfs(x,next_y,x2y,y2x,visited);
  }
  
  for(int i=0;i<y2x[y].size();i++){
    int next_x = y2x[y][i];
    res += dfs(next_x,y,x2y,y2x,visited);
  }
  return res;
}

int main(){
  int total_slimes;
  int W,H;
  while(~scanf("%d %d %d",&total_slimes,&W,&H)){
    vector<Point> points;
    map<int,vector<int> >x2y;
    map<int,vector<int> >y2x;
    map<Point,bool> visited;
    bool has_corner = false;
    
    for(int slime_idx=0; slime_idx < total_slimes; slime_idx++){
      int x,y;
      scanf("%d %d",&x,&y);
      x--;
      y--;
      x2y[x].push_back(y);
      y2x[y].push_back(x);
      if(x == 0 || y == 0 || x == W-1 || y == H-1){
	has_corner = true;
      }
    }

    int group_count = 0;
    for(map<int,vector<int> >::iterator it = x2y.begin();
	it != x2y.end();
	it++){
      int x = it->first;
      for(int i=0; i < it->second.size(); i++){
	int y = it->second[i];
	map<Point,bool>::iterator it;
	if((it = visited.find(Point(x,y))) != visited.end()) continue;
	dfs(x,y,x2y,y2x,visited);
	group_count++;
      }
    }

    //(cost for initial grouping)
    //+ (cost for moving to the corner) + (cost for grouping remainings)

    int init_grouping_cost = total_slimes - group_count;
    printf("%d\n",init_grouping_cost
	   + (group_count > 1 ?
	      (group_count + (has_corner ? -1 : 0)) + (group_count - 1)
	      : 0));
  }
}
