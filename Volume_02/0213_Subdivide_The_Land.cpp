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
  int W,H,total_buyer;
  while(~scanf("%d %d %d",&W,&H,&total_buyers)){
    int stage[50][50];
    for(int buyer_i = 0; buyer_i < total_buyers; buyer_i++){
      int id;
      int area;
      scanf("%d %d",&id,&area);
    }

    for(int y = 0; y < H; y++){
      for(int x = 0; x < W; x++){
	scanf("%d",&stage[y][x]);
      }
    }
  }
}
