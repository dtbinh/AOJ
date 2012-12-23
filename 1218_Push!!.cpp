
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
 
class Data{
public:
    int cost;
    int manX;
    int manY;
    int cargoX;
    int cargoY;
    Data(int _c,int _mX,int _mY,int _cX,int _cY){
        cost = _c;
        manX = _mX;
        manY = _mY;
        cargoX = _cX;
        cargoY = _cY;
    }
 
    bool operator>(const Data& d) const{
        return cost > d.cost;
    }
};
 
int stage[7][7];
int cost[7][7][7][7];
 
int main(){
 
    //0: nothing (simply a floor tile)
    //1: a pillar
    //2: the cargo
    //3: the goal
    //4: the warehouseman (Mr. Schwarz)
 
    int mX;
    int mY;
    int cX;
    int cY;
    int w,h;
    while(~scanf("%d %d",&w,&h)){
        if(w==0 && h==0) break;
        for(int y=0;y<h;y++){
            for(int x=0;x<w;x++){
                scanf("%d",&stage[y][x]);
                if(stage[y][x] == 2){
                    cX = x;
                    cY = y;
                    stage[y][x] = 0;
                }
                else if(stage[y][x] == 4){
                    mX = x;
                    mY = y;
                    stage[y][x] = 0;
                }
            }
        }
 
 
        memset(cost,INF,sizeof(cost));
        priority_queue<Data,vector<Data>,greater<Data> > que;
        que.push(Data(0,mX,mY,cX,cY));
        cost[mX][mY][cX][cY] = 0;
 
        int minval = INF;
        while(!que.empty()){
            Data d = que.top();
            que.pop();
            if(stage[d.cargoY][d.cargoX] == 3){
                minval = d.cost;
                break;
            }
 
            for(int i=0;i<4;i++){
                int dx = d.manX + tx[i];
                int dy = d.manY + ty[i];
                if(dx < 0 || dx >= w || dy < 0 || dy >= h) continue;
                if(stage[dy][dx] == 1) continue;
 
                if(dx == d.cargoX && dy == d.cargoY){
                    int dcx = d.cargoX + tx[i];
                    int dcy = d.cargoY + ty[i];
                    if(dcx < 0 || dcx >= w || dcy < 0 || dcy >= h) continue;
                    if(stage[dcy][dcx] == 1) continue;
                     
 
                    if(cost[dx][dy][dcx][dcy] <= d.cost + 1) continue;
 
                    cost[dx][dy][dcx][dcy] = d.cost + 1;
                    que.push(Data(d.cost+1,dx,dy,dcx,dcy));
                    continue;
                }
 
                if(cost[dx][dy][d.cargoX][d.cargoY] <= d.cost) continue;
                cost[dx][dy][d.cargoX][d.cargoY] = d.cost;
 
                que.push(Data(d.cost,dx,dy,d.cargoX,d.cargoY));
            }
        }
 
        printf("%d\n",minval == INF ? -1 : minval);
    }
}

