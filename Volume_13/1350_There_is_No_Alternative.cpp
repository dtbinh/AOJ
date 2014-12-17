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
    for(int i = 0; i < N; i++){
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
  int id;
  Edge(int from,int to,int cost,int id) 
    : from(from), to(to), cost(cost), id(id) {}
  bool operator<(const Edge& e) const {
    return cost < e.cost;
  }
  bool operator>(const Edge& e) const {
    return cost > e.cost;
  }
};

int num_of_islands;
int num_of_pairs;
vector<int> graph[501];

bool bfs(int from,int to){
  bool visited[501];
  memset(visited,false,sizeof(visited));
  queue<int> que;
  que.push(from);
  while(!que.empty()){
    int current = que.front();
    visited[current] = true;
    if(visited[to]) return false;

    que.pop();
    for(int i = 0; i < graph[current].size(); i++){
      if(visited[graph[current][i]]) continue;
      if((current == from && graph[current][i] == to)
	 || (current == to && graph[current][i] == from)) continue;
      visited[graph[current][i]] = true;
      que.push(graph[current][i]);
    }
  }

  return true;
}

int main(){
  while(~scanf("%d %d",&num_of_islands,&num_of_pairs)){
    priority_queue<Edge,vector<Edge>, greater<Edge> > que;
    vector<Edge> orig;
    int par[501];
    for(int i = 0; i <= 500; i++){
      graph[i].clear();
      par[i] = i;
    }

    for(int i = 0; i < num_of_pairs; i++){
      int from,to;
      int cost;
      scanf("%d %d %d",&from,&to,&cost);
      from--; to--;
      que.push(Edge(from,to,cost,i));
      orig.push_back(Edge(from,to,cost,i));
      graph[from].push_back(to);
      graph[to].push_back(from);
    }

    UnionFindTree uft(par);

    vector<Edge> candidates;
    int sum = 0;
    while(!que.empty()){
      Edge e = que.top();
      que.pop();
      if(uft.unite(e.from,e.to)){
	sum += e.cost;
	candidates.push_back(e);
      }
    }
    int res_cost = 0;
    int res_count = 0;
    sort(orig.begin(),orig.end());

    for(int candidate_i = 0; candidate_i < candidates.size(); candidate_i++){
      int from = candidates[candidate_i].from;
      int to = candidates[candidate_i].to;
      int id = candidates[candidate_i].id;

      UnionFindTree uft2(par);
      int sum2 = 0;
      for(int i = 0; i < orig.size(); i++){
	if(id == orig[i].id) continue;
	if(uft2.unite(orig[i].from,orig[i].to)){
	  sum2 += orig[i].cost;
	}
      }
      if(sum2 != sum || bfs(from,to)){
	res_cost += candidates[candidate_i].cost;
	res_count++;
      }
    }
    printf("%d %d\n",res_count,res_cost);
  }
}
