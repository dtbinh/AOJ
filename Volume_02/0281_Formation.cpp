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

static const double EPS = 1e-8;

int dfs(int c,int a,int n,int count){
  if(c < 0 || a < 0 || n < 0) return 0;

  int res = count;
  //cca
  res = max(res,dfs(c-2,a-1,n,count+1));

  //ccc
  res = max(res,dfs(c-3,a,n,count+1));

  //can
  res = max(res,dfs(c-1,a-1,n-1,count+1));
  
  return res;
}

int main(){
  int N;
  while(~scanf("%d",&N)){
    if(N == 0) break;
    for(int i=0;i<N;i++){
      int c,a,n;
      scanf("%d %d %d",&c,&a,&n);
      printf("%d\n",dfs(c,a,n,0));
    }
  }
}
