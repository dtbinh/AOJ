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
 
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

int main(){
  int e;
  while(~scanf("%d",&e)){
    if(e==0) break;
    int res = INF;

    for(int y=0;y*y<=e;y++){
      for(int z=0;y*y+z*z*z<=e;z++){
	res = min(res,y+z+(e-y*y-z*z*z));
      }
    }
    printf("%d\n",res);
  }
}
