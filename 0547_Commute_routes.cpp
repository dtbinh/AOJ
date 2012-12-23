
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
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
 
static const double EPS = 1e-8;
 
int tx[] = {1,0};
int ty[] = {0,1};
 
ll dp[101][101][2][2];

ll dfs(int x,int y,int isturn,int dir,int w,int h,bool isf){
    if(x==w-1 && y==h-1) return 1;
 
    ll res=0;
    for(int i=0;i<2;i++){
        int nextT;
        if(isturn && i != dir) continue;
        if(!isf && i!=dir) nextT = 1;
        else nextT = 0;
        int dx = x + tx[i];
        int dy = y + ty[i];
        if(dy < 0 || dx < 0 || dy >= h || dx >= w) continue;
        //printf("x:%d y:%dn",dx,dy);
		if(dp[dy][dx][dir][i]==-1) res += (dp[dy][dx][dir][i] = dfs(dx,dy,nextT,i,w,h,false) % 100000);
        else res += dp[dy][dx][dir][i];
    }
 
    return res;
}
int main(){
    int w,h;
    while(~scanf("%d %d",&w,&h)){
        if(w==h && h==0) break;
		memset(dp,-1,sizeof(dp));
        printf("%lld\n",dfs(0,0,0,0,w,h,true) % 100000);
    }
}

