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

double dp[21][140001];

int main(){
  int N;
  while(~scanf("%d",&N)){
    int currency[21];
    for(int i=0;i<N;i++){
      scanf("%d",&currency[i]);
    }
    
    fill((double*)dp,(double*)dp + 21 * 140001,1e12);

    dp[0][1] = 0.0;
    for(int i = 0; i < N; i++){
      for(int start = 1; start <= 140000; start++){
	if(dp[i][start] >= 1e12) continue;
	for(int next = start; next <= 140000; next += start){
	  dp[i+1][next] = min(dp[i+1][next],
			      max(dp[i][start],
				  (double)abs(next - currency[i])/(double)currency[i]));
	}
      }
    }

    double res = 1e12;
    for(int next = 1; next <= 140000; next++){
      res = min(dp[N][next],res);
    }
    printf("%.12lf\n",res);
  }
}
