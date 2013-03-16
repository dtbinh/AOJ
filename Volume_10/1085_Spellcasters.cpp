
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
 
ll dp[20000][3];
 
ll nCr(int n,int r){
    return dp[n][r] != -1 ? dp[n][r] : 
        dp[n][r] = (r==0|| n==r) ? 1 : nCr(n-1,r) + nCr(n-1,r-1);
}
 
 
int main(){
    int n,S;
    memset(dp,-1,sizeof(dp));
 
    while(~scanf("%d %d",&n,&S)){
        if(n==0) break;
        vector<int> witch;
        for(int i=0;i<n;i++){
            int m;
            scanf("%d",&m);
            witch.push_back(m);
        }
 
        sort(witch.begin(),witch.end());
 
        ll res = 0;
        for(int m1=0;m1<=100;m1++){
            for(int m2=m1;m2<=100;m2++){
                if(m1+m2 <= S) continue;
                int num1 = upper_bound(witch.begin(),witch.end(),m1) - lower_bound(witch.begin(),witch.end(),m1);
                int num2 = upper_bound(witch.begin(),witch.end(),m2) - lower_bound(witch.begin(),witch.end(),m2);
 
                if(m1==m2 && num1 != 0) res += nCr(num1,2);
                else res += num1 * num2;
            }
        }
 
 
        printf("%lld\n",res);
    }
}

