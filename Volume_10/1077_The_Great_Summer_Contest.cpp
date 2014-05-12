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
    
    int balance_game = min(min(A,B),C);
    A -= balance_game;
    B -= balance_game;
    C -= balance_game;
    int math_game = A / 3;
    int algorithm_game = B / 3;
    int implement_game = C / 3;
    printf("%d\n",math_game + algorithm_game + implement_game + balance_game);
  }
}
