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

int main(){
  int N;
  while(~scanf("%d",&N)){

    for(int i=0;i<N;i++){
      int c,a,n;

      int count = 0;
      scanf("%d %d %d",&c,&a,&n);
      
      while(c >= 1 && a >= 1 && n >= 1){
	c--;
	a--;
	n--;
	count++;
      }

      while(a >= 1 && c >= 2){
	a--;
	c -= 2;
	count++;
      }

      while(c >= 3){
	  c -= 3;
	  count++;
      }
      printf("%d\n",count);
    }
  }
}
