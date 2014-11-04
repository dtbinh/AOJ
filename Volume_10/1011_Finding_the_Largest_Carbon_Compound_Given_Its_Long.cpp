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

int main(){
  int n;
  int idx = 1;
  int ans[30000];
  memset(ans,0x3f,sizeof(ans));
  for(int i = 1,len=1; i <= 30; i += 2){
    for(int j = 0; j < i; j++){
      ans[idx] = len;
      idx++;
    }
    len++;
    for(int j = 0; j < i; j++){
      ans[idx] = len;
      idx++;
    }
    len++;
  }

  while(~scanf("%d",&n)){
    int res = 0;
    for(int i = 1; i<=30000;i++){
      if(ans[i] <= n){
	res = i;
      }
      else{
	break;
      }
    }
    printf("%d\n",res);
  }
}
