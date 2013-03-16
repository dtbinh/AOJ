
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
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;
 
int dp[40000][5];
 
int main(){
    int n;
    while(~scanf("%d",&n)){
        if(n==0) break;
 
        memset(dp,0,sizeof(dp));
 
        dp[0][0] = 1;
        for(int i=1;i*i<=n;i++){
            for(int k=1;k<=4;k++){
                for(int j=i*i;j<=n;j++){
                    dp[j][k] += dp[j-i*i][k-1];
                }
            }
        }
 
        printf("%d\n",dp[n][4] + dp[n][3] + dp[n][2] + dp[n][1]);
    }
}

