#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
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
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;
 
const static int tx[] = {0,1,1,1,0,-1,-1,-1};
const static int ty[] = {-1,-1,0,1,1,1,0,-1};
 
static const double EPS = 1e-8;

int main(){
  int N;
  while(~scanf("%d",&N)){
    int currency[21];
    for(int i=0;i<N;i++){
      scanf("%d",&currency[i]);
    }

    double res = numeric_limits<double>::max();
    for(int start=1;start<=100000;start++){
      double tmp_ratio = 0.0;
      int prev = start;

      for(int i=0;i<N;i++){
	int lhs = 0; int rhs = 1000000;
	for(int round = 0; round < 30; round++){
	  int mid = lhs + (rhs - lhs) / 2;
	  if(prev * mid - currency[i] >= 0){
	    rhs = mid;
	  }
	  else{
	    lhs = mid;
	  }
	}
	  
	int next1 = prev * rhs;
	int next2 = prev * lhs;
	  
	double ratio1 = abs((double)(next1 - currency[i])) / (double)currency[i];
	double ratio2 = abs((double)(next2 - currency[i])) / (double)currency[i];
	
	tmp_ratio
	  = max(tmp_ratio,min(ratio1,ratio2));

	prev = (ratio1 < ratio2 ? next1 : next2);
      }
      res = min(res,tmp_ratio);
    }
    printf("%.12lf\n",res);
  }
}
