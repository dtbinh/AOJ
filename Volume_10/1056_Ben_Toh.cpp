
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
 
double dp[100001][21];
 
int main(){
    int n;
     
    while(~scanf("%d",&n)){
        if(n==0) break;
        memset(dp,0,sizeof(dp));
 
        double exp = 0;
        dp[1][1] = 1.0;
 
        for(int i=1;i<=n;i++){
            for(int j=1;j<=20;j++){
                //dp[i][j]
                //i:day
                //j:success time
                exp += dp[i][j] * pow(0.5,j-1);
 
                if(j==1){
                    dp[i+1][j+1] += dp[i][j];
                    continue;
                }
 
                dp[i+1][1] += dp[i][j] * (1.0 - pow(0.5,j-1));
                dp[i+1][j+1] += dp[i][j] * pow(0.5,j-1);
            }
        }
 
        printf("%.8lf\n",exp);
    }
}

