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

int main(){
  int total_nodes;
  int total_queries;
  while(~scanf("%d %d",&total_nodes,&total_queries)){
    if(total_nodes == 0 && total_queries == 0) break;

    for(int node_idx = 1;node_idx<total_nodes;node_idx++){
      int parent;
      scanf("%d",&parent);
    }
    for(int query_idx=0;query_idx < total_queries; query_idx++){
      char operation[2];
      int node_val;
      scanf("%s %d",operation,&node_val);
    }
  }
}
