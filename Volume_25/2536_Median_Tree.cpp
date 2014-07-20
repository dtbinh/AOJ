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

int main(){
  int num_of_nodes;
  int num_of_edges;
  while(~scanf("%d",&num_of_nodes,&num_of_edges)){
    if(num_of_nodes == 0 && num_of_edges == 0) break;

    for(int edge_idx = 0; edge_idx < num_of_edges; edge_idx++){
      int from,to,cost;
      scanf("%d %d %d",&from,&to,&cost);
    }
  }
}

