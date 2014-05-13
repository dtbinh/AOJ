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

    int A = math+DP;
    int B = greedy + graph;
    int C = geometry + other;
    
    int res = 0;

    int max_game = min(min(A,B),C);
    for(int balance_game = 0; balance_game <= min(2,max_game); balance_game++){
      int tmpA = A;
      int tmpB = B;
      int tmpC = C;
      tmpA -= balance_game;
      tmpB -= balance_game;
      tmpC -= balance_game;
      int math_game = tmpA / 3;
      int algorithm_game = tmpB / 3;
      int implement_game = tmpC / 3;

      res = max(balance_game + math_game + algorithm_game + implement_game,res);
    }
    printf("%d\n",res);
  }
}
