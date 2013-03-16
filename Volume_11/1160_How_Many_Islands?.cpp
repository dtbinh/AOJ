
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
 
int stage[50][50];
 
void dfs(int x,int y,int w,int h){
    stage[y][x] = 0;
    for(int tx=-1;tx<=1;tx++){
        for(int ty=-1;ty<=1;ty++){
            int dx = x + tx;
            int dy = y + ty;
            if(dx < 0 || dx >=w || dy < 0 || dy >= h) continue;
 
            if(stage[dy][dx]==1){
                dfs(x+tx,y+ty,w,h);
            }
        }
    }
}
 
int main(){
    int w,h;
    while(~scanf("%d %d",&w,&h)){
        if(w==h && h==0) break;
        for(int y=0;y<h;y++){
            for(int x=0;x<w;x++){
                scanf("%d",(*(stage+y)+x));
            }
        }
 
        int res=0;
        for(int y=0;y<h;y++){
            for(int x=0;x<w;x++){
                if(stage[y][x]==1){
                    dfs(x,y,w,h);
                    res++;
                }
            }
        }
 
        printf("%d\n",res);
    }
}

