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
#include <iterator>
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;
 
int tx[] = {0,1,0,-1};//URDL
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

class Edge{
public:
  int from;
  int to;
  int distance;
  int cost;
  Edge(int _f,int _t,int _d,int _c) : from(_f),to(_t),distance(_d),cost(_c) {}
  Edge() : from(0), to(0), distance(0), cost(0) {}
  bool operator<(const Edge& e) const{
    return distance < e.distance;
  }

  bool operator>(const Edge& e) const{
    return distance > e.distance;
  }
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
  int total_cities;
  int total_roads;
  while(~scanf("%d %d",&total_cities,&total_roads)){
    if(total_cities == 0 &&  total_roads == 0) break;

    UnionFindTree uft(20001);
    vector<Edge> edges;

    priority_queue<Edge> que;
    for(int road_idx = 0; road_idx < total_roads; road_idx++){
      int from,to,distance,cost;
      scanf("%d %d %d %d",&from,&to,&distance,&cost);
      que.push(Edge(from,to,distance,cost));
    }

    int res = 0;
    while(!que.empty()){
      Edge e = que.top();
      que.pop();
      if(!uft.same(e.from,e.to)){
	uft.unite(e.from,e.to);
	printf("unite %d %d\n",e.from,e.to);
	res += e.cost;
      }
    }

    printf("%d\n",res);
  }
}
