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


struct Edge{
  int to;
  int cost;
  Edge(int _to,int _cost) : 
    to(_to), cost(_cost) {}
  Edge() : to(0), cost(0) {}
};

vector<Edge> edges[20];
bool visited[20];
int sum;
int max_dist;

void dfs(int current,int prev_cost,int total_cost){
  if(visited[current]) return;

  if(current != 0 && edges[current].size() == 1){
    max_dist = max(max_dist,total_cost - prev_cost);
    return;
  }

  visited[current] = true;
  sum += prev_cost;

  for(int i=0;i<edges[current].size();i++){
    dfs(edges[current][i].to,
	edges[current][i].cost,
	total_cost + edges[current][i].cost);
  }
}

int main(){
  int N;
  while(~scanf("%d",&N)){
    if(N == 0) break;
    for(int i=0;i<20;i++){
      edges[i].clear();
    }

    memset(visited,false,sizeof(visited));
    sum = 0;
    max_dist = 0;

    int total_cost = 0;
    for(int i=0;i<N-1;i++){
      int from,to,cost;
      scanf("%d %d %d",&from,&to,&cost);

      from--; to--;
      edges[from].push_back(Edge(to,cost));
      edges[to].push_back(Edge(from,cost));
    }

    dfs(0,0,0);
    printf("%d\n",2 * sum - max_dist);
  }
}
