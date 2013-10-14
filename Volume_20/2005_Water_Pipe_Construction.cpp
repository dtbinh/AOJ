#define _USE_MATH_DEFINES
#define INF 0x0f0f0f0f
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
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

int main(){
  int total_station;
  int total_road;
  int water_source_idx;
  int main_station1_idx;
  int main_station2_idx;
  while(~scanf("%d %d %d %d %d",
	       &total_station,
	       &total_road,
	       &water_source_idx,
	       &main_station1_idx,
	       &main_station2_idx)){
    if(total_station == 0) break;

    int nodes[101][101];
    memset(nodes,0x0f,sizeof(nodes));
    for(int i=1;i<=total_station;i++){
      nodes[i][i] = 0;
    }

    for(int i=0;i<total_road;i++){
      int from,to,cost;
      scanf("%d %d %d",&from,&to,&cost);
      nodes[from][to] = cost;
    }

    for(int k=1;k<=total_station;k++){
      for(int i=1;i<=total_station;i++){
	for(int j=1;j<=total_station;j++){
	  nodes[i][j] = min(nodes[i][k]+nodes[k][j],nodes[i][j]);
	}
      }
    }

    int res = INF;
    for(int i=1;i<=total_station;i++){
      res = min(nodes[water_source_idx][i]
		+ nodes[i][main_station1_idx]
		+ nodes[i][main_station2_idx],res);
    }

    printf("%d\n",res);
  }
	       
}
