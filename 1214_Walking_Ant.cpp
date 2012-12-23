
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
 
int stage[8][8];
int cost[8][8][6];
 
class Ant{
public:
    int cost;
    int life;
    int x;
    int y;
    Ant(int _x,int _y,int _l,int _c) : x(_x),y(_y),life(_l),cost(_c) {}
    bool operator>(const Ant& a) const{
        return cost > a.cost;
    }
};
 
int main(){
    int w,h;
    while(~scanf("%d %d",&w,&h)){
        if(w==0 && h==0) break;
        int ax,ay;
        for(int y=0;y<h;y++){
            for(int x=0;x<w;x++){
                scanf("%d",&stage[y][x]);
                if(stage[y][x] == 2){
                    ax = x;
                    ay = y;
                }
            }
        }
 
        memset(cost,0x3f,sizeof(cost));
        priority_queue<Ant,vector<Ant>,greater<Ant> > que;
 
        que.push(Ant(ax,ay,6,0));
        cost[ax][ay][6] = 0;
         
 
        int res = -1;
        while(!que.empty()){
            Ant ant = que.top();
            que.pop();
 
            for(int i=0;i<4;i++){
                int dx = ant.x + tx[i];
                int dy = ant.y + ty[i];
                if(dx < 0 || dx >= w || dy < 0 || dy >= h) continue;
                if(stage[dy][dx] == 0) continue;
 
                //food
                if(stage[dy][dx] == 4){
                    if(ant.life - 1 <= 0) continue;
                    if(cost[dx][dy][6] < ant.cost + 1) continue;
                    que.push(Ant(dx,dy,6,ant.cost + 1));
                    cost[dx][dy][6] = ant.cost + 1;
                }
 
                //nest
                if(stage[dy][dx] == 3){
                    if(ant.life - 1 <= 0) continue;
                    res = ant.cost + 1;
                    goto found;
                }
 
                //nothing
                if(stage[dy][dx] == 1
                    || stage[dy][dx] == 2){
                    if(ant.life - 1 <= 0) continue;
                    if(cost[dx][dy][ant.life - 1] < ant.cost + 1) continue;
                    que.push(Ant(dx,dy,ant.life - 1,ant.cost + 1));
                    cost[dx][dy][ant.life - 1] = ant.cost + 1;
                }
            }
        }
found:;
 
        printf("%d\n",res);
    }
}

