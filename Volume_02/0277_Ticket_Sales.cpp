#define _USE_MATH_DEFINES
#define INF 10000000
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

static const double eps = 1e-8;

const int tickets[5] = {0,6000,4000,3000,2000};

int main(){
  int t,n;
  while(~scanf("%d %d",&t,&n)){
    printf("%d\n",tickets[t]*n);
  }
}
