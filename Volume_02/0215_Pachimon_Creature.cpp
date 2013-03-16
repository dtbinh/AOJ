
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
typedef pair <int,P> PP;
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;
 
int cost[5002];
short pokpos[1002][1002];
char stage[1002][1002];
 
struct Pos{
    int x;
    int y;
};
 
class Data{
public:
    int cost;
    int got;
    int x;
    int y;
    Data() : got(0),cost(0),x(0),y(0){}
    Data(int _c,int _g,int _x,int _y){
        cost = _c;
        got = _g;
        x = _x;
        y = _y;
    }
    bool operator>(const Data& d) const{
        return cost > d.cost;
    }
    bool operator<(const Data& d) const{
        return cost < d.cost;
    }
};
 
void clear( priority_queue<Data,vector<Data>,greater<Data> > &q )
{
    priority_queue<Data,vector<Data>,greater<Data> > empty;
    swap( q, empty );
}
 
int main(){
    int w,h;
    while(~scanf("%d %d",&w,&h)){
        if(w==h && h==0) break;
        int sx,sy;
        int gx,gy;
        int count = 0;
        map<int,vector<P> > pokemon;
 
        Pos pos[5002];
        for(int y=0;y<h;y++){
            char buf[1024];
            scanf("%s",buf);
            for(int x=0;x<w;x++){
                stage[y][x] = buf[x];
                if(buf[x]=='S'){
                    sx = x;
                    sy = y;
                    pokpos[y][x]=count;
                    pos[count].x = x;
                    pos[count].y = y;
                    count++;
                }
 
                else if(buf[x]=='G'){
                    gx = x;
                    gy = y;
                    pokpos[y][x]=count;
                    pos[count].x = x;
                    pos[count].y = y;
                    count++;
                }
                else if(isdigit(buf[x])){
                    pokemon[buf[x]-'1'].push_back(P(x,y));
                    pokpos[y][x]=count;
                    pos[count].x = x;
                    pos[count].y = y;
                    count++;
                }
            }
        }
 
 
        int res_pk=-1;
        int res_step = INF;
 
 
        for(int pk=0;pk<=4;pk++){
            priority_queue<Data,vector<Data>,greater<Data> > que;
 
            que.push(Data(0,pk,sx,sy));
            memset(cost,0x3f,sizeof(cost));
            cost[pokpos[sy][sx]] = 0;
 
            while(!que.empty()){
                Data d = que.top();
                que.pop();
 
                int target = (d.got + 1) % 5;
 
                if(target == pk){
                    int c = abs(gx - d.x) + abs(gy - d.y);
                    if(res_step <= d.cost + c) continue;
                    res_step = d.cost + c;
                    res_pk = pk;
                }
 
                else{
 
                    int size = pokemon[target].size();
                    for(int i=0;i<size;i++){
                        int dx = pokemon[target][i].first;
                        int dy = pokemon[target][i].second;
 
                        int c = abs(dx - d.x) + abs(dy - d.y);              
 
                        if(cost[pokpos[dy][dx]] <= d.cost + c) continue;
 
                        cost[pokpos[dy][dx]] = d.cost + c;
 
                        que.push(Data(d.cost+c,target,dx,dy));
                    }
                }
            }
        }
 
        if(res_pk == -1) printf("NA\n");
        else printf("%d %d\n",res_pk+1,res_step);
    }
    return 0;
}

