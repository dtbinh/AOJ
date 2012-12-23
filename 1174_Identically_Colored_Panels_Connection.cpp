
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
 
int gSum = 0;
int w,h,c;
 
class Data{
public:
    int stage[8][8];
    int count;
    Data() : count(0), stage(){}
    Data(int _stage[8][8],int _count){
        memcpy(this->stage,_stage,sizeof(int)*8*8);
        this->count = _count;
    }
    bool operator>(const Data& d) const{
        return this->count > d.count;
    }
 
    bool operator<(const Data& d) const{
        return this->count < d.count;
    }
};
 
void dfs(int stage[8][8],int x,int y,int from,int to,bool visited[8][8]){
    stage[y][x] = to;
    visited[y][x] = true;
 
    for(int i=0;i<4;i++){
        int dx = x + tx[i];
        int dy = y + ty[i];
        if(dx < 0 || dx >= w || dy < 0 || dy >= h) continue;
        if(stage[dy][dx] != from ) continue;
        if(visited[dy][dx]) continue;
 
        dfs(stage,dx,dy,from,to,visited);
    }
}
 
void dfs2 (int stage[8][8],int x,int y,bool visited[8][8]){
    visited[y][x] = true;
    gSum++;
    for(int i=0;i<4;i++){
        int dx = x + tx[i];
        int dy = y + ty[i];
        if(dx < 0 || dx >= w || dy < 0 || dy >= h) continue;
        if(stage[dy][dx] != c) continue;
        if(visited[dy][dx]) continue;
 
        dfs2(stage,dx,dy,visited);
    }
}
 
string stg2str(int stage[8][8]){
    string res = "";
    for(int y=0;y<h;y++){
        for(int x=0;x<w;x++){
            res += stage[y][x] + '0';
        }
    }
 
    return res;
}
 
int main()
{
    while(~scanf("%d %d %d",&h,&w,&c)){
        if(h==w && w==c && c==0) break;
 
        int stage[8][8];
        for(int y=0;y<h;y++){
            for(int x=0;x<w;x++){
                scanf("%d",&stage[y][x]);
            }
        }
 
        priority_queue<Data,vector<Data>,greater<Data> > que;
        que.push(Data(stage,0));
 
        int maxv = 0;
        map<string,int> cost;
 
        while(!que.empty()){
            Data d = que.top();
            que.pop();
 
            if(d.count >= 5) continue;
            for(int i=1;i<=6;i++){
                int next[8][8];
                memcpy(next,d.stage,sizeof(int)*8*8);
 
                 
                bool visited[8][8];
                memset(visited,0,sizeof(visited));
                dfs(next,0,0,d.stage[0][0],i,visited);
 
 
                string str = stg2str(next);
                if(cost.find(str) != cost.end() && cost[str] <= d.count + 1) continue;
 
                cost[str] = d.count + 1;
 
                gSum = 0;
                memset(visited,0,sizeof(visited));
                dfs2(next,0,0,visited);
                maxv = max(maxv,gSum);
 
                que.push(Data(next,d.count+1));
            }
        }
 
        printf("%d\n",maxv);
    }
}

