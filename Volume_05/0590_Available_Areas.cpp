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

bool is_valid(int area){
  for(int x=1;2*x*x+2*x<=area;x++){
    if((area - x) % (2*x + 1) == 0) return true;
  }
  return false;
}

int main(){
  int n;
  while(~scanf("%d",&n)){
    int res = 0;
    for(int i=0;i<n;i++){
      int area;
      scanf("%d",&area);
      if(!is_valid(area)) res++;
    }
    printf("%d\n",res);
  }
}
