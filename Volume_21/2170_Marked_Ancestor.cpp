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
 
static const double EPS = 1e-8;

class UnionFindTree {
private:
  int* par;
public:
  UnionFindTree(int n){
    par = new int[n]();
    for(int i=0;i<n;i++){
      par[i] = i;
    }
  }

  ~UnionFindTree(){
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

vector<int> G[100001];
int marked_count[100001];
int prev_parent[100001];

void dfs(int current_node,int parent,int last_marked_node,UnionFindTree* uft){
  if(marked_count[current_node] > 0){
    last_marked_node = current_node;
  }

  prev_parent[current_node] = parent;
  uft->unite(current_node,last_marked_node);
  for(int to_idx=0;to_idx<G[current_node].size();to_idx++){
    int to = G[current_node][to_idx];
    dfs(to,current_node,last_marked_node,uft);
  }
}

int main(){
  int total_nodes;
  int total_queries;
  while(~scanf("%d %d",&total_nodes,&total_queries)){
    if(total_nodes == 0 && total_queries == 0) break;

    for(int i=0;i<=100000;i++) G[i].clear();

    memset(marked_count,0,sizeof(marked_count));
    for(int node_idx = 2;node_idx-1<total_nodes;node_idx++){
      int parent;
      scanf("%d",&parent);
      G[parent].push_back(node_idx);
    }

    int queries[100001];
    for(int query_idx=0;query_idx < total_queries; query_idx++){
      char operation[2];
      int target_node;
      scanf("%s %d",operation,&target_node);
      if(operation[0] == 'M'){
	marked_count[target_node]++;
	queries[query_idx] = target_node;
      }
      else if(operation[0] == 'Q'){
	queries[query_idx] = -target_node;
      }
    }

    UnionFindTree uft(total_nodes+1);
    dfs(1,1,1,&uft);

    ll sum = 0;
    for(int query_idx=total_queries-1;query_idx>=0;query_idx--){
      if(queries[query_idx] <= 0){
	int target_node = -queries[query_idx];
	sum += uft.find(target_node);
      }
      else if(queries[query_idx] > 0){
	int target_node = queries[query_idx];
	marked_count[target_node]--;
	if(marked_count[target_node] <= 0){
	  uft.unite(target_node,prev_parent[target_node]);
	}
      }
    }
    printf("%lld\n",sum);
  }
}
