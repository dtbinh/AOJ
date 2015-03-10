#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
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
#include <complex>
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;
 
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-10;

int dp[2001][2001];

int main(){
  string str;
  memset(dp,0,sizeof(dp));
  while(cin >> str){
    string r_str = str;
    reverse(r_str.begin(),r_str.end());
    for(int i = 0; i < str.size(); i++){
      for(int j = 0; j< r_str.size(); j++){
	if(str[i] == r_str[j]){
	  dp[i+1][j+1] = dp[i][j] + 1;
	}
	else{
	  dp[i+1][j+1] = max(dp[i][j+1],dp[i+1][j]);
	}
      }
    }

    int sx = r_str.size();
    int sy = str.size();
    for(int y = 0; y <= str.size(); y++){
      for(int x = 0; x <= r_str.size(); x++){
	printf("%d ",dp[y][x]);
      }
      printf("\n");
    }
    printf("\n");
    printf("%d\n",dp[str.size()][r_str.size()]);
  }
}
