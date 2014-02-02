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
  int total_watches;
  while(~scanf("%d",&total_watches)){
    if(total_watches == 0) break;
    for(int watch_idx = 0; watch_idx < total_watches; watch_idx++){
      int hands[3];
      for(int hand_idx = 0; hand_idx < 3; hand_idx++){
	scanf("%d",hands + hand_idx);
      }
    }
  }
}
