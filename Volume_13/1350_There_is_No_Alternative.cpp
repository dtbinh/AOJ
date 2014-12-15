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
  int* par;
  int* rank;
public:
  UnionFindTree(int N){
    par = new int[N];
    rank = new int[N];
    for(int i = 0; i < N; i++){
      par[i] = i;
      rank[i] = 0;
    }
  }
  ~UnionFindTree(){
    delete[] par;
    delete[] rank;
  }

  int find(int u){
    if(par[u] == u) return u;
    return find(par[u]);
  }

  bool unite(int u,int v){
    u = find(u);
    v = find(v);
    if(u == v) return false;

    if(rank[u] >= rank[v]){
      par[u] = v;
      rank[v] = rank[u] + 1;
    }
    else{
      par[v] = u;
      rank[u] = rank[v] + 1;
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
bool candidate[501][501];
int idx[501][501];
bool used[501][501];
vector<int> graph[501];

bool bfs(int from,int to){
  bool visited[501];
  memset(visited,false,sizeof(visited));
  queue<int> que;
  que.push(0);
  while(!que.empty()){
    int current = que.front();
    visited[current] = true;
    que.pop();
    for(int i = 0; i < graph[current].size(); i++){
      if(visited[graph[current][i]]) continue;
      if((current == from && graph[current][i] == to)
	 || (current == to && graph[current][i] == from)) continue;
      que.push(graph[current][i]);
    }
  }

  for(int i = 0; i < num_of_islands; i++){
    if(!visited[i]) return true;
  }
  return false;
}

int main(){
  while(~scanf("%d %d",&num_of_islands,&num_of_pairs)){
    priority_queue<Edge,vector<Edge>, greater<Edge> > que;
    vector<Edge> orig;
    for(int i = 0; i <= 500; i++){
      graph[i].clear();
    }

    memset(idx,-1,sizeof(idx));
    for(int i = 0; i < num_of_pairs; i++){
      int from,to;
      int cost;
      scanf("%d %d %d",&from,&to,&cost);
      from--; to--;
      que.push(Edge(from,to,cost));
      orig.push_back(Edge(from,to,cost));
      idx[from][to] = i;
      idx[to][from] = i;
      graph[from].push_back(to);
      graph[to].push_back(from);
    }

    UnionFindTree uft(num_of_islands);
    memset(candidate,false,sizeof(candidate));

    int sum = 0;
    while(!que.empty()){
      Edge e = que.top();
      que.pop();
      if(uft.unite(e.from,e.to)){
	candidate[e.from][e.to] = true;
	candidate[e.to][e.from] = true;
	sum += e.cost;
      }
    }

    int res_cost = 0;
    int res_count = 0;
    for(int from = 0; from < num_of_islands; from++){
      for(int to = from + 1; to < num_of_islands; to++){
	if(idx[from][to] == -1) continue;
	if(!candidate[from][to]) continue;
	for(int i = 0; i < orig.size(); i++){
	  if(idx[from][to] == i) continue;
	  que.push(orig[i]);
	}
	UnionFindTree uft2(num_of_islands);
	int sum2 = 0;
	while(!que.empty()){
	  Edge e = que.top();
	  que.pop();
	  if(uft2.unite(e.from,e.to)){
	    sum2 += e.cost;
	  }
	}
	if(sum2 > sum || (bfs(from,to))){
	  res_cost += orig[idx[from][to]].cost;
	  res_count++;
	}
      }
    }
    printf("%d %d\n",res_count,res_cost);
  }
}
