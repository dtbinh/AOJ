#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
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
typedef pair<int,string> P;

static const double EPS = 1e-8;

int main(){
  int c1,c5,c10,c50,c100,c500;
  while(~scanf("%d %d %d %d %d %d",
	       &c1,&c5,&c10,&c50,&c100,&c500)){
    printf("%d\n",
	   (c1 + c5 * 5 + c10 * 10 + c50 * 50 + c100 * 100 + c500 * 500)
	   >= 1000 ? 1 : 0);
  }
}
