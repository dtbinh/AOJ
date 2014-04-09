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

class UnionFindTree {
private:
  int* par;
  int* rank;
  int* weight;
public:
  UnionFindTree(int n){
    par = new int[n]();
    rank = new int[n]();
    weight = new int[n]();
    for(int i=0;i<n;i++){
      par[i] = i;
      rank[i] = 0;
      weight[i] = 1;
    }
  }

  ~UnionFindTree(){
    delete[] rank;
    delete[] par;
    delete[] weight;
  }

  int find(int x){
    if(par[x] == x){
      return x;
    } else {
      return par[x] = find(par[x]);
    }
  }

  void unite(int x,int y){
    x = find(x);
    y = find(y);
    if (x == y) return;

    if(rank[x] < rank[y]){
      par[x] = y;
      weight[y] += weight[x];
    } else {
      par[y] = x;
      weight[x] += weight[y];
      if (rank[x] == rank[y]) rank[x]++;
    }
  }

  int count(int x){
    return weight[find(x)];
  }
  bool same(int x,int y){
    return find(x) == find(y);
  }
};

class Home{
public:
  int home_idx;
  double coordinate;
  Home() : home_idx(0),coordinate(0){}
  Home(int _h,double _c) : home_idx(_h),coordinate(_c){}
};

class Point {
public:
  double x;
  double y;
  Point() : x(0), y(0) {}
  Point(double _x,double _y) : x(_x), y(_y) {}
};

int main(){
  int total_homes;
  double R;
  map<double,vector<Home> > x2y;
  map<double,vector<Home> > y2x;
  vector<double> xs;
  vector<double> ys;
  vector<Point> homes;

  while(~scanf("%d %lf",&total_homes,&R)){
    for(int home_idx = 0; home_idx < total_homes; home_idx++){
      double x,y;
      scanf("%lf %lf",&x,&y);
      x2y[x].push_back(Home(home_idx,y));
      y2x[y].push_back(Home(home_idx,x));
      homes.push_back(Point(x,y));
      xs.push_back(x);
      ys.push_back(y);
    }
    
    sort(xs.begin(),xs.end());
    sort(ys.begin(),ys.end());

    UnionFindTree uft(total_homes);
    for(int home_idx = 0; home_idx < total_homes; home_idx++){
      double hx = homes[home_idx].x;
      double hy = homes[home_idx].y;
      int cx_idx = lower_bound(xs.begin(),xs.end(),hx) - xs.begin();
      int cy_idx = lower_bound(ys.begin(),ys.end(),hy) - ys.begin();
      for(int y_idx=cy_idx-1; y_idx <= cy_idx+1; y_idx++){
	if(y_idx < 0 || y_idx >= ys.size()) continue;

	for(int i=0;i<y2x[ys[y_idx]].size();i++){
	  int dst_idx = y2x[ys[y_idx]][i].home_idx;
	  
	  if(dst_idx == home_idx) continue;
	  double dx = y2x[ys[y_idx]][i].coordinate;
	  double dy = ys[y_idx];
	  if(9 * R * R <= (hx - dx) * (hx - dx) + (hy - dy) * (hy - dy)){
	    continue;
	  }
	  else if(R * R >= (hx - dx) * (hx - dx) + (hy - dy) * (hy - dy)){
	    // printf("%lf %lf\n",homes[home_idx].x,homes[home_idx].y);
	    // printf("%lf %lf\n\n",homes[dst_idx].x,homes[dst_idx].y);
	    uft.unite(home_idx,dst_idx);
	  }
	}
      }
      for(int x_idx=cx_idx-1; x_idx <= cx_idx+1; x_idx++){
	if(x_idx < 0 || x_idx >= xs.size()) continue;

	for(int i=0;i<x2y[xs[x_idx]].size();i++){
	  int dst_idx = x2y[xs[x_idx]][i].home_idx;
	  if(dst_idx == home_idx) continue;
	  // printf("%lf %lf\n",homes[home_idx].x,homes[home_idx].y);
	  // printf("%lf %lf\n\n",homes[dst_idx].x,homes[dst_idx].y);

	  double dx = xs[x_idx];
	  double dy = x2y[xs[x_idx]][i].coordinate;
	  if(9 * R * R <= (hx - dx) * (hx - dx) + (hy - dy) * (hy - dy)){
	    continue;
	  }
	  else if(R * R >= (hx - dx) * (hx - dx) + (hy - dy) * (hy - dy)){
	    uft.unite(home_idx,dst_idx);
	  }
	}
      }
    }

    int res = 0;
    bool visited[200001];
    memset(visited,false,sizeof(visited));
    for(int home_idx = 0; home_idx < total_homes; home_idx++){
      if(!visited[uft.find(home_idx)]){
	res++;
	visited[uft.find(home_idx)] = true;
      }
    }
    printf("%d\n",res);
  }
}
