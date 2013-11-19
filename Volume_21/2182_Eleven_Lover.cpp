#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f

#include <iostream>
#include <cstdio>
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
typedef pair <int,P> PP;
  
static const double EPS = 1e-8;
  
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};

int main(){
  string str;
  while(cin >> str){
    if(str == "0") break;

    int dp[80001][11];
    memset(dp,0,sizeof(dp));

    int res = 0;
    for(int i=0;i<str.size();i++){
      int num = str[i] - '0';
      for(int j=0;j<=10;j++){
	dp[i+1][(j*10+num)%11] = dp[i][j];
      }
      if(num > 0) dp[i+1][num]++;
      res += dp[i+1][0];
    }
    printf("%d\n",res);
  }
}
