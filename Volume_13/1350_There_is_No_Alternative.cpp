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
#include <complex>
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;

typedef complex<double> Point;
const static double EPS = 1e-12;
const static int MAX_V = 501;

class UnionFindTree {
  int _par[501];
  int _rank[501];
public:
  UnionFindTree(int N){
    for(int i = 0; i < N; ++i){
      _par[i] = i;
      _rank[i] = 0;
    }
  }

  UnionFindTree(int par[501]){
    memcpy(_par,par,sizeof(int)*501);
    memset(_rank,0,sizeof(_rank));
  }

  int find(int u){
    if(_par[u] == u) return u;
    return find(_par[u]);
  }
  bool same(int u,int v){
    u = find(u);
    v = find(v);
    return (u == v);
  }

  bool unite(int u,int v){
    u = find(u);
    v = find(v);
    if(u == v) return false;
    
    if(_rank[u] < _rank[v]){
      _par[u] = v;
    }
    else{
      _par[v] = u;
      if(_rank[u] == _rank[v]) _rank[u]++;
    }
    return true;
  }
};

class Edge {
public:
  int from;
  int to;
  int cost;
  Edge(int from,int to,int cost) 
    : from(from), to(to), cost(cost) {}
  bool operator<(const Edge& e) const {
    return cost < e.cost;
  }
  bool operator>(const Edge& e) const {
    return cost > e.cost;
  }
};

int num_of_islands;
int num_of_pairs;

bool check_connect(UnionFindTree& uft){
  for(int i = 1; i < num_of_islands; i++){
    if(!uft.same(0,i)) return false;
  }
  return true;
}

int main(){
  while(~scanf("%d %d",&num_of_islands,&num_of_pairs)){
    vector<Edge> orig;
    int par[501];
    for(int i = 0; i <= 500; ++i){
      par[i] = i;
    }

    for(int i = 0; i < num_of_pairs; ++i){
      int from,to;
      int cost;
      scanf("%d %d %d",&from,&to,&cost);
      from--; to--;
      orig.push_back(Edge(from,to,cost));
    }

    UnionFindTree uft(par);
    sort(orig.begin(),orig.end());

    int sum = 0;
    bool used[50001] = {};
    for(int i = 0; i < orig.size(); ++i){
      if(uft.unite(orig[i].from,orig[i].to)){
	sum += orig[i].cost;
	used[i] = true;
      }
    }
    int res_cost = 0;
    int res_count = 0;

    for(int i = 0; i < orig.size(); ++i){
      if(!used[i]) continue;

      UnionFindTree uft2(par);
      int sum2 = 0;
      int prev = orig[i].cost;
      orig[i].cost = INF;

      for(int j = 0; j < orig.size(); ++j){
	if(orig[j].cost >= INF) continue;
	if(uft2.unite(orig[j].from,orig[j].to)){
	  sum2 += orig[j].cost;
	}
      }
      orig[i].cost = prev;

      if(sum2 > sum || !check_connect(uft2)){
	res_cost += orig[i].cost;
	res_count++;
      }
    }
    printf("%d %d\n",res_count,res_cost);
  }
}
