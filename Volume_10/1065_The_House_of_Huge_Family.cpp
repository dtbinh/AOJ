#define _USE_MATH_DEFINES
#define INF 100000000
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
#include <cstdio>

using namespace std;

typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P> PP;

static const double EPS = 1e-8;

const int tx[] = {0,1,0,-1};
const int ty[] = {-1,0,1,0};

struct Node {
  int to;
  int idx;
  int flow;
  Node(int to,int idx,int flow) :
    to(to),idx(idx),flow(flow) {}
};

class FordFulkerson {
private:
  vector<Node>* _graph;
  bool* _used;
  int _size;

  int dfs(int src,int flow,int sink){
    if(src == sink) return flow;

    _used[src] = true;
    for(int i= 0;i < _graph[src].size();i++){
      Node& e = _graph[src][i];
      if(_used[e.to]) continue;
      if(e.flow <= 0) continue;
      int d = dfs(e.to,min(flow,e.flow),sink);
      if(d <= 0) continue;

      Node& rev_e = _graph[e.to][e.idx];
      e.flow -= d;
      rev_e.flow += d;
      return d;
    }
    return 0;
  }

public:  
  FordFulkerson(int n) {
    _size = n;
    _graph = new vector<Node>[_size];
    _used = new bool[_size];
  }
  FordFulkerson(const FordFulkerson& f){
    _size = f.size();
    _graph = new vector<Node>[_size];
    _used = new bool[_size];
    fill((bool*)_used,(bool*)_used + _size,false);

    for(int i = 0; i < f.size(); i++){
      for(int j = 0; j < f.graph()[i].size(); j++){
	_graph[i].push_back(f.graph()[i][j]);
      }
    }
  }

  void add_edge(int from,int to,int flow) {
    _graph[from].push_back(Node(to,_graph[to].size(),flow));
    _graph[to].push_back(Node(from,_graph[from].size()-1,flow));
  }

  int compute_maxflow(int src,int sink){
    int res = 0;

    while(true){
      fill((bool*)_used,(bool*)_used + _size,false);
      int tmp = dfs(src,numeric_limits<int>::max(),sink);
      if(tmp == 0) break;
      res += tmp;
    }
    return res;
  }

  int size() const{
    return _size;
  }
  vector<Node>* graph() const{
    return _graph;
  }
};

class UnionFindTree {
private:
  int* par;
  int* rank;
public:
  UnionFindTree(int n){
    par = new int[n]();
    rank = new int[n]();
    for(int i=0;i<n;i++){
      par[i] = i;
      rank[i] = 0;
    }
  }

  ~UnionFindTree(){
    delete[] rank;
    delete[] par;
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
    par[x] = y;
  }

  bool same(int x,int y){
    return find(x) == find(y);
  }
};

int main(){
  int num_of_houses;
  int num_of_paths;
  while(~scanf("%d %d",&num_of_houses,&num_of_paths)){
    if(num_of_houses == 0 && num_of_paths == 0) break;

    FordFulkerson ff(num_of_houses);
    UnionFindTree uft(num_of_houses);

    int bonus = 0;

    for(int path_i = 0; path_i < num_of_paths; path_i++){
      int from,to;
      int cost;
      scanf("%d %d %d",&from,&to,&cost);
      if(cost < 0) bonus += cost; 
      ff.add_edge(from,to,max(0,cost));
      uft.unite(from,to);
    }

    int tree_count = 0;
    bool visited[101];
    memset(visited,false,sizeof(visited));
    for(int house_i = 0; house_i< num_of_houses; house_i++){
      if(!visited[uft.find(house_i)]) tree_count++;
      visited[uft.find(house_i)] = true;
    }

    int res = numeric_limits<int>::max();

    if(tree_count >= 2){
      res = 0;
    }
    else{
      for(int house_i = 0; house_i< num_of_houses; house_i++){
	int house_j = uft.find(house_i);
	if(house_i == house_j) continue;
	FordFulkerson tmp(ff);
	res = min(res,tmp.compute_maxflow(house_i,house_j));
      }
    }
    printf("%d\n",bonus + res);
  }
}
