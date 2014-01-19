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

class BipartiteGraph {
private:
  int V;
  vector<int>* G;
  int* match;
  bool* used;
public:
  BipartiteGraph(int n){
    V = n;
    match = new int[n];
    used = new bool[n];
    G = new vector<int>[n];
  }

  ~BipartiteGraph(){
    delete[] match;
    delete[] used;
    delete[] G;
  }

  void add_edge(int u,int v){
    G[u].push_back(v);
    G[v].push_back(u);
  }

  bool dfs(int v){
    used[v] = true;
    for(int i=0;i<G[v].size();i++){
      int u = G[v][i];
      int w = match[u];
      if(w < 0 || (!used[w] && dfs(w))){
	match[v] = u;
	match[u] = v;
	return true;
      }
    }
    return false;
  }

  int bipartite_matching() {
    int res = 0;
    fill(match,match+V,-1);
    for(int v=0; v < V;v++){
      if(match[v] < 0){
	fill(used,used+V,false);
	if(dfs(v)){
	  res++;
	}
      }
    }
    return res;
  }
};

class Point{
public:
  int x;
  int y;
  Point() : x(0),y(0) {}
  Point(int _x,int _y) : x(_x),y(_y) {}
};

class Troop{
public:
  Point point;
  int velocity;
  Troop() : point(),velocity(0){}
  Troop(const Point& _p,int _v) : point(_p),velocity(_v){}
};

double compute_distance(const Point& p1,const Point& p2){
  return sqrt((p1.x - p2.x) * (p1.x - p2.x)
	      + (p1.y - p2.y) * (p1.y - p2.y));
}

double compute_time(double distance,double velocity){
  return distance / velocity;
}

bool check(double time,int total_troops,int total_bases,
	   double times[101][101]){
  BipartiteGraph bg(total_troops + total_bases);

  for(int troop_idx = 0; troop_idx < total_troops; troop_idx++){
    for(int base_idx = 0; base_idx < total_bases; base_idx++){
      if(time >= times[troop_idx][base_idx] - EPS){
	bg.add_edge(troop_idx,total_troops + base_idx);
      }
    }
  }

  return (bg.bipartite_matching() == total_bases);
}

int main(){
  int total_troops;
  int total_bases;
  while(~scanf("%d %d",&total_troops,&total_bases)){
    if(total_troops == 0 && total_bases == 0) break;

    vector<Troop> troops;
    vector<Point> bases;
    for(int troop_idx = 0; troop_idx < total_troops; troop_idx++){
      int x,y,v;
      scanf("%d %d %d",&x,&y,&v);
      troops.push_back(Troop(Point(x,y),v));
    }
    for(int base_idx = 0; base_idx < total_bases; base_idx++){
      int x,y;
      scanf("%d %d",&x,&y);
      bases.push_back(Point(x,y));
    }

    double times[101][101];
    for(int troop_idx = 0; troop_idx < total_troops; troop_idx++){
      for(int base_idx = 0; base_idx < total_bases; base_idx++){
	times[troop_idx][base_idx]
	  = compute_time(
	    compute_distance(bases[base_idx],troops[troop_idx].point),
	    troops[troop_idx].velocity);
      }
    }

    double upper_time = 100000000000000.0;
    double lower_time = 0;
    for(int round=0;round<100;round++){
      double mid = (upper_time + lower_time) / 2.0;
      if(check(mid,total_troops,total_bases,times)){
	upper_time = mid;
      }
      else{
	lower_time = mid;
      }
    }

    printf("%.10f\n",upper_time);
  }
}
