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
  int n;
  while(~scanf("%d",&n)){
    int dismiss_tile;
    scanf("%d",&dismiss_tile);
    for(int i=0;i<dismiss_tile;i++){
      int col,row;
      scanf("%d %d",&col,&row);
      int pos = min(
	min(col-1,n-col),
	min(row-1,n-row)
      );

      printf("%d\n",pos % 3 + 1);
    }
  }
}
