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
  
static const int tx[] = {+0,+1,+1,+1,+0,-1,-1};
static const int ty[] = {-1,+1,+0,-1,+1,-1,+0};

class Point {
public:
  double x;
  double y;
  Point() : x(0), y(0) {}
  Point(double _x,double _y) : x(_x), y(_y) {}
};


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

int main(){
  int total_homes;
  double R;
  vector<Point> homes;

  while(~scanf("%d %lf",&total_homes,&R)){
    map<P,int> cell;
    map<P,int> cell_idx;
    int idx = 0;

    for(int home_idx = 0; home_idx < total_homes; home_idx++){
      double x,y;
      scanf("%lf %lf",&x,&y);
      homes.push_back(Point(x,y));
      int cell_x = (int)(x / R);
      int cell_y = (int)(y / R);
      cell[P(cell_x,cell_y)]++;
      if(cell_idx.find(P(cell_x,cell_y)) == cell_idx.end()){
	cell_idx[P(cell_x,cell_y)] = idx++;
      }
    }

    int total_cells = idx;
    UnionFindTree uft(total_cells);
    
    for(map<P,int>::iterator it = cell.begin();
	it != cell.end();
	it++){
      for(int i=0;i<8;i++){
	int sx = it->first.first;
	int sy = it->first.second;

	int dx = sx + tx[i];
	int dy = sy + ty[i];
	if(cell.find(P(dx,dy)) != cell.end()){
	  int from = cell_idx[P(sx,sy)];
	  int to = cell_idx[P(dx,dy)];
	  uft.unite(from,to);
	}
      }
    }

    bool visited[200001];
    memset(visited,false,sizeof(visited));
    int res = 0;
    for(int i=0;i<total_cells;i++){
      if(!visited[uft.find(i)]){
	visited[uft.find(i)] = true;
	res++;
      }
    }
    printf("%d\n",res);
  }
}
