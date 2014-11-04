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

static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};

int sum[50];

int main(){
  for(int i = 1,len=1; len <= 30; i *= 3){
    sum[len] = sum[len-1] + i;
    sum[len+1] = sum[len] + i;
    len+=2;
  }

  int n;
  while(~scanf("%d",&n)){
    int res = 0;
    printf("%d\n",sum[n]);
  }
}
