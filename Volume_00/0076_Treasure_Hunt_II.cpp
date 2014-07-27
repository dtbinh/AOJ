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
#include <complex>
#include <assert.h>
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;
 
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};

static const double EPS = 1e-10;

typedef complex<double> Point;

int main(){
  int n;
  while(~scanf("%d",&n)){
    if(n == -1) break;
    Point player = Point(1.0, 0.0);
    
    //looking at ido
    while(--n > 0){
      Point next = -player;
      next *= exp( complex< double >( .0, -90.0*M_PI/180.0 ) );
      player += next / abs(next);
    }
    printf("%.2lf\n%.2lf\n",player.real(),player.imag());
  }
}
