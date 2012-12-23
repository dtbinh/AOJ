
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
typedef pair <string,string> P;
typedef pair <int,P> PP;
 
static const double EPS = 1e-8;
 
int tx[4],ty[4];
 
int dfs(int stage,int c){   
    if(c==8) return 1;  
 
    int res = 0;
    int sx = -1;
    int sy = -1;
    for(int y=0;y<4;y++){
        for(int x=0;x<4;x++){
            if(~stage & (1<<(y*4+x))){    
                sx = x;
                sy = y;
                goto found;
            }
        }
    }
found:;
 
 
    if(sx == -1) return 0;
 
    for(int i=0;i<4;i++){
        int dx = sx + tx[i];
        int dy = sy + ty[i];
        if(dx < 0 || dx >= 4 || dy < 0 || dy >= 4) continue;
        if(stage & (1<<(dy*4+dx))) continue;
 
        stage |= (1<<(dy*4+dx));
        stage |= (1<<(sy*4+sx));
        res += dfs(stage,c+1);
        stage &= ~(1<<(dy*4+dx));
        stage &= ~(1<<(sy*4+sx));
    }
 
    return res;
}
 
int main(){
 
    while(~scanf("%d",tx+0)){
        if(tx[0] >= 5) break; 
        scanf("%d %d %d %d %d %d %d",ty+0,tx+1,ty+1,tx+2,ty+2,tx+3,ty+3);
        printf("%d\n",dfs(0,0));
    }
}

