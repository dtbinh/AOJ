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

int main(){
  int num_of_houses;
  int num_of_paths;
  while(~scanf("%d %d",&num_of_houses,&num_of_paths)){
    if(num_of_houses == 0 && num_of_paths == 0) break;

    int block_cost[101] = {};
    bool used[101];
    memset(used,false,sizeof(used));
    for(int path_i = 0; path_i < num_of_paths; path_i++){
      int from,to,cost;
      scanf("%d %d %d",&from,&to,&cost);
      block_cost[to] += cost;
      used[to] = true;
    }

    int res = numeric_limits<int>::max();
    for(int house_i = 0; house_i < num_of_houses; house_i++){
      if(!used[house_i]) continue;
      res = min(block_cost[house_i],res);
    }

    printf("%d\n",res);
  }
}
