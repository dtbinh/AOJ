
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
 
const int tx[] = {0,1,0,-1};
const int ty[] = {1,0,-1,0};
 
char stage[20][20];
 
int main(){
    int W,H;
    while(~scanf("%d %d",&W,&H)){
        if(W==H && H==0) break;
        for(int y=0;y<H;y++){
            char buf[32];
            scanf("%s",buf);
            for(int x=0;x<W;x++){
                stage[y][x] = buf[x];
            }
        }
 
        int sx=0;
        int sy=0;
        for(int y=0;y<H;y++){
            for(int x=0;x<W;x++){
                if(stage[y][x] == '@'){
                    sx = x;
                    sy = y;
                    goto found;
                }
            }
        }
found:;
        queue<P> que;
        que.push(P(sx,sy));
 
        int res = 0;
        bool visited[20][20];
        memset(visited,0,sizeof(visited));
 
        visited[sy][sx] = true;
        while(!que.empty()){
            int sx = que.front().first;
            int sy = que.front().second;
            res++;
            que.pop();
             
            for(int i=0;i<4;i++){
                int dx = sx + tx[i];
                int dy = sy + ty[i];
 
                if(dx < 0 || dx >= W || dy < 0 || dy >= H) continue;
                if(stage[dy][dx]=='#') continue;
                if(visited[dy][dx]) continue;
 
                visited[dy][dx] = true;
                 
                que.push(P(dx,dy));
            }
        }
 
        printf("%d\n",res);
 
    }
}

