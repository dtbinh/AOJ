
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
 
char stage[20][20];
 
class Data{
public:
    int cost;
    int x;
    int y;
    int visited;
    Data() : cost(0),x(0),visited(0){}
    Data(int _cost,int _x,int _y,int _visited){
        this->cost = _cost;
        this->x = _x;
        this->y = _y;
        this->visited = _visited;
    }
 
    bool operator>(const Data& d) const{
        return this->cost > d.cost;
    }
};
 
int cost[500][1<<10];
 
int main()
{
    int W,H;
    while(~scanf("%d %d",&W,&H)){
        if(W==H && H==0) break;
        int sx, sy;
        int idx = 0;
        map<P,int> id;
        for(int y=0;y<H;y++){
            char buf[32];
            scanf("%s",buf);
             
            for(int x=0;x<W;x++){
                stage[y][x] = buf[x];
                if(buf[x] == 'o'){
                    sx = x;
                    sy = y;
                }
                else if(buf[x] == '*'){
                    id[P(x,y)]=idx++;
                }
            }
        }
         
        priority_queue<Data,vector<Data>,greater<Data> > que;
        que.push(Data(0,sx,sy,0));
 
         
        memset(cost,0x3f,sizeof(cost));
 
        cost[sy*W+sx][0] = 0;
        while(!que.empty()){
            Data d = que.top();
            que.pop();
 
            for(int i=0;i<4;i++){
                int dx = d.x + tx[i];
                int dy = d.y + ty[i];
                if(dx < 0 || dx >= W || dy < 0 || dy >= H) continue;
                if(stage[dy][dx] == 'x') continue;
 
                int next = d.visited;
                if(id.find(P(dx,dy)) != id.end()){
                    next |= (1<<id[P(dx,dy)]);
                }
 
                if(cost[dy*W+dx][next] <= d.cost + 1) continue;
                cost[dy*W+dx][next] = d.cost + 1;
                que.push(Data(d.cost+1,dx,dy,next));
            }
        }
 
        int flag = 0;
        for(map<P,int>::iterator it = id.begin(); it != id.end(); it++){
            flag |= (1<<it->second);
        }
 
        int minv = 0x3f3f3f3f;
        for(int i=0;i<=W*H;i++){
            minv = min(cost[i][flag],minv);
        }
 
        printf("%d\n",minv == 0x3f3f3f3f ? -1 : minv);
    }
}

