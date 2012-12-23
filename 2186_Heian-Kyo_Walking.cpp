
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
 
int main(){
    int n;
    while(~scanf("%d",&n)){
        for(int i=0;i<n;i++){
            int gx,gy,p;
            bool stage[16][16][16][16];
            memset(stage,-1,sizeof(stage));
            scanf("%d %d",&gx,&gy);
            scanf("%d",&p);
            for(int j=0;j<p;j++){
                int x1,y1,x2,y2;
                scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
                stage[x1][y1][x2][y2] = false;
                stage[x2][y2][x1][y1] = false;
            }
 
            int dp[17][17];
             
            memset(dp,0,sizeof(dp));
 
            dp[0][0] = 1;
            dp[1][1] = 1;
 
            for(int y=0;y<=gy;y++){
                for(int x=0;x<=gx;x++){
                    if(x==0 && y==0) continue;
 
                    if(x > 0 && stage[x-1][y][x][y]){
                        dp[y+1][x+1] += dp[y+1][x];
                    }
 
                    if(y > 0 && stage[x][y-1][x][y]){
                        dp[y+1][x+1] += dp[y][x+1];
                    }
                }
            }
 
            if(dp[gy+1][gx+1]==0){
                printf("Miserable Hokusai!\n");
            }
            else{
                printf("%d\n",dp[gy+1][gx+1]);
            }
        }
    }
 
}

