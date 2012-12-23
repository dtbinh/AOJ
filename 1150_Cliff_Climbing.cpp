
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
 
static const float EPS = 1e-8;
 
int txr[] = {1,1,1,1,1,2,2,2,3};
int tyr[] = {-2,-1,0,1,2,-1,0,1,0};
 
 
int txl[] = {-1,-1,-1,-1,-1,-2,-2,-2,-3};
int tyl[] = {-2,-1,0,1,2,-1,0,1,0};
 
char stage[60][30];
int cost[1800][1800];
 
class Data{
public:
    int cost;
    int rhs;
    int lhs;
    bool turn;
    Data(int _cost,int _lhs,int _rhs,bool _turn){
        cost = _cost;
        lhs = _lhs;
        rhs = _rhs;
        turn = _turn;
    }
 
    bool operator>(const Data& d) const{
        return cost > d.cost;
    }
};
 
int main(){
    int w,h;
    while(~scanf("%d %d",&w,&h)){
        if(w==0 && h==0) break;
        memset(cost,0x3f,sizeof(cost));
        vector<P> S;
        vector<P> T;
        for(int y=0;y<h;y++){
            for(int x=0;x<w;x++){
                scanf("%s",&stage[y][x]);
                if(stage[y][x]=='S') S.push_back(P(x,y));
                if(stage[y][x]=='T') T.push_back(P(x,y));
            }
        }
 
        priority_queue<Data,vector<Data>,greater<Data> > que;
 
        for(int i=0;i<S.size();i++){
            int x = S[i].first;
            int y = S[i].second;
            que.push(Data(0,y*w+x,y*w+x,false));
            que.push(Data(0,y*w+x,y*w+x,true));
        }
 
        int res = numeric_limits<int>::max();
        while(!que.empty()){
            Data d = que.top();
 
            int srx = d.rhs % w;
            int sry = d.rhs / w;
 
            int slx = d.lhs % w;
            int sly = d.lhs / w;
            que.pop();
 
            if(d.cost >= res) continue;
 
            if(d.turn){
                for(int i=0;i<9;i++){
                    int dx = txl[i] + srx;
                    int dy = tyl[i] + sry;
 
                    if(dx < 0 || dx >= w || dy < 0 || dy >= h) continue;
                    if(dx>=srx) continue;
                    if(abs(dx - srx) + abs(dy - sry) > 3) continue;
                    if(stage[dy][dx] == 'X') continue;
                    if(stage[dy][dx] == 'T'){
                        res = cost[dy*w+dx][d.rhs] = min(cost[dy*w+dx][d.rhs],d.cost);
                        continue;
                    }
 
                    if(cost[dy*w+dx][d.rhs] <= d.cost + stage[dy][dx]-'0') continue;
                    cost[dy*w+dx][d.rhs] = d.cost + stage[dy][dx]-'0';
 
                    que.push(Data(d.cost + stage[dy][dx]-'0',dy*w+dx,d.rhs,false));
                    //dfs(dy*w+dx,d.rhs,0,d.cost + stage[dy][dx]-'0');
                }
            }
            else{
                for(int i=0;i<9;i++){
                    int dx = txr[i] + slx;
                    int dy = tyr[i] + sly;
 
                    if(dx < 0 || dx >= w || dy < 0 || dy >= h) continue;
                    if(slx>=dx) continue;
                    if(abs(dx - slx) + abs(dy - sly) > 3) continue;
                    if(stage[dy][dx] == 'X') continue;
                    if(stage[dy][dx] == 'T'){
                        res = cost[d.lhs][dy*w+dx] = min(cost[d.lhs][dy*w+dx],d.cost);
                        continue;
                    }
                    if(cost[d.lhs][dy*w+dx] <= d.cost + stage[dy][dx]-'0') continue;
                    cost[d.lhs][dy*w+dx] = d.cost + stage[dy][dx]-'0';
                    que.push(Data(d.cost + stage[dy][dx]-'0',d.lhs,dy*w+dx,true));
                    //dfs(d.lhs,dy*w+dx,1,d.cost + stage[dy][dx]-'0');
                }
            }
        }
 
        printf("%d\n",res >= 0x3f3f3f3f ? -1 : res);
    }
}

