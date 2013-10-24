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

int main(){
  int total_nodes,total_edges;
  int nodes[101][101];
  memset(nodes,0x3f,sizeof(nodes));

  while(~scanf("%d %d",&total_nodes,&total_edges)){
    if(total_nodes == 0) break;

    for(int edge_idx = 0; edge_idx < total_edges; edge_idx++){
      int from,to,cost;
      scanf("%d %d %d",&from,&to,&cost);
      nodes[from][to] = cost;
      nodes[to][from] = cost;
    }

    bool used[101];
    memset(used,false,sizeof(used));

    used[1] = true;
    int max_weight = -1;
    int min_weight = INF;
    bool isok = true;
    for(int round = 1;round <= total_nodes-1; round++){
      int cost = INF;
      int next = -1;
      for(int from_idx = 1; from_idx <= total_nodes; from_idx++){
	if(used[from_idx]) continue;
	for(int to_idx = 1; to_idx <= total_nodes; to_idx++){
	  if((from_idx == to_idx) || !used[to_idx]) continue;

	  if(cost > nodes[from_idx][to_idx]){
	    cost = nodes[from_idx][to_idx];
	    next = from_idx;
	  }
	}
      }

      if(next == -1){
	isok = false;
	break;
      }

      max_weight = max(cost,max_weight);
      min_weight = min(cost,min_weight);
      used[next] = true;
    }

    printf("%d\n",isok ? max_weight - min_weight : -1);
  }
}
