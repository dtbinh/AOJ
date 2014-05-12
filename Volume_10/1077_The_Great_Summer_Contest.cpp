#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdio>
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
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
 
static const double EPS = 1e-8;
 
int main(){
  int math,greedy,geometry,DP,graph,other;
  while(~scanf("%d %d %d %d %d %d",
	       &math,&greedy,&geometry,&DP,&graph,&other)){
    if(math + greedy + geometry + DP + graph + other == 0) break;
    int math_game = 0;
    if(math + DP >= 3){
      math_game = (math + DP) * (math + DP - 1) * (math + DP - 2) / (3 * 2 * 1);
    }

    int algorithm_game = 0;
    if(greedy + graph >= 3){
      algorithm_game = (greedy + graph) * (greedy + graph - 1) * (greedy + graph - 2) / (3 * 2 * 1);
    }

    int implement_game = 0;
    if(geometry + other >= 3){
      implement_game = (geometry + other) * (geometry + other - 1) * (geometry + other - 2) / (3 * 2 * 1);
    }
    
    int balance_game = 0;
    if(math + DP >= 1 && greedy + graph >= 1 && geometry + other >= 1){
      balance_game = (math + DP) * (greedy + graph) * (geometry + other) / (3 * 2 * 1);
    }

    printf("%d\n",math_game + algorithm_game + implement_game + balance_game);
  }
}
