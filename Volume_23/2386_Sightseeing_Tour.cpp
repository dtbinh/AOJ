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
  int N;
  while(~scanf("%d",&N)){
    ll road_cost[100][100];

    for(int y=0;y<N;y++){
      for(int x=0;x<N;x++){
	ll cost;
	scanf("%ld",&cost);
	road_cost[y][x] = cost;
      }
    }

    bool visited[100][100];
    memset(visited,false,sizeof(visited));

    ll cost = 0;
    for(int y=0;y<N;y++){
      for(int x=0;x<N;x++){
	if(y==x) continue;
	if(visited[x][y]) continue;

	cost += min(road_cost[x][y],road_cost[y][x]);
	visited[x][y] = true;
	visited[y][x] = true;
      }
    }
    printf("%ld\n",cost);
  }
}
