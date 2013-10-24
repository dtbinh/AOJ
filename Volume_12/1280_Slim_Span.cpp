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
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-10;

struct Edge{
  int start,end;
  int cost;
  Edge(int _s,int _e,int _c) : start(_s),end(_e),cost(_c){}
  bool operator<(const Edge& e) const{
    return cost < e.cost;
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
  int total_nodes,total_edges;
  int nodes[100][100];
  memset(nodes,0x3f,sizeof(nodes));

  while(~scanf("%d %d",&total_nodes,&total_edges)){
    if(total_nodes == 0) break;

    vector<Edge> edges;
    for(int edge_idx = 0; edge_idx < total_edges; edge_idx++){
      int from,to,cost;
      scanf("%d %d %d",&from,&to,&cost);
      nodes[from-1][to-1] = cost;
      nodes[to-1][from-1] = cost;
      edges.push_back(Edge(from-1,to-1,cost));
    }
   
    sort(edges.begin(),edges.end());

    int opt_cost = INF;
    for(int i=0;i<total_edges;i++){
      UnionFindTree union_find(total_nodes);

      for(int j=i;j<total_edges;j++){
	union_find.unite(edges[j].start,edges[j].end);
	if(union_find.count(edges[j].start) == total_nodes){
	  opt_cost = min(opt_cost,edges[j].cost-edges[i].cost);
	  break;
	}
      }
    }
    printf("%d\n",opt_cost == INF ? -1 : opt_cost);
  }
}
