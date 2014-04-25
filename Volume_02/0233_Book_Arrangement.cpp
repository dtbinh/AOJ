#define _USE_MATH_DEFINES
#define INF 10000000

#include <cstdio>
#include <iostream>
#include <sstream>
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
typedef pair<int,int> P;

static const double eps = 1e-8;

int main(){
  int N;
  while(~scanf("%d",&N)){
    if(N==0) break;

    int divisor = -10;
    stack<int> stk;
    while(abs(N)>0){
      int rem = (N % 10 < 0 ? N % 10 + 10 : N % 10);
      stk.push(rem);
      N = (N-rem) / divisor;
    }
    while(!stk.empty()){
      printf("%d",stk.top());
      stk.pop();
    }
    printf("\n");
  }
}
