
#define _USE_MATH_DEFINES
#define INF 100000000
 
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
typedef pair <int,P> PP;
 
static const double EPS = 1e-8;
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
int dfs(double ans,int div,double sum,int a,int n){
    if(ans-EPS <= sum && sum <= ans+EPS){
        return 1;
    }
    else if(ans-EPS <= sum || a == 0 || n == 0){
        return 0;
    }
 
    int res = 0;
    for(int i=div;i<=a;i++){
        res += dfs(ans,i,sum+(1.0/i),a/i,n-1);
    }
 
    return res;
}
 
int main()
{
    int p,q,a,n;
    while(~scanf("%d %d %d %d",&p,&q,&a,&n)){
        if(p==q && q==a && a==n && n==0) break;
        int res = dfs((double)p/(double)q,1,0,a,n);
        printf("%d\n",res);
    }
}

