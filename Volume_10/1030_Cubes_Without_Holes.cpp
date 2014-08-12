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

bool dp[501][501][501];

int main(){
  int n,total_queries;
  while(~scanf("%d %d",&n,&total_queries)){
    if(n == 0 && total_queries == 0) break;

    memset(dp,false,sizeof(dp));
    int res = n * n * n;
    for(int i=0; i < total_queries; i++){
      string axis;
      int pos[2];
      cin >> axis >> pos[0] >> pos[1];
      
      char other = (axis[0] != 'x' && axis[1] != 'x') ? 'x'
	: (axis[0] != 'y' && axis[1] != 'y') ? 'y' : 'z';

      for(int i=1;i<=n;i++){
	if(other == 'x'){
	  if(!dp[i][pos[0]][pos[1]]) res--;
	  dp[i][pos[0]][pos[1]] = true;
	}
	else if(other == 'y'){
	  if(!dp[pos[0]][i][pos[1]]) res--;
	  dp[pos[0]][i][pos[1]] = true;
	}
	else if(other == 'z'){
	  if(!dp[pos[0]][pos[1]][i]) res--;
	  dp[pos[0]][pos[1]][i] = true;
	}
      }
    }
    
    printf("%d\n",res);
  }
}
