
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
 
int dp[100000];
 
//Square Coins
int main(){
    int n;
 
    while(~scanf("%d",&n)){
        if(n==0) break;
 
        memset(dp,0,sizeof(dp));
 
        dp[0] = 1;
 
        for(int i=1;i<=17;i++){
            for(int k=1;k<=n;k++){
                if(k-i*i<0) continue;
                dp[k] += dp[k-i*i];
            }
        }
 
        printf("%d\n",dp[n]);
    }
}

