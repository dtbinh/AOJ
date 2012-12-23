
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
typedef pair <int,int > P;
typedef pair <int,P > PP;
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;
 
static const char RGB[]={'R','G','B'};
 
class Data{
public:
    int cost;
    int pos;
    int used;
    int m1;
    int m2;
    Data(int _cost,int _pos,int _used,int _m1,int _m2) 
        : cost(_cost), pos(_pos), used(_used),m1(_m1),m2(_m2){
    }
 
    Data(int _cost,int _pos,int _used) : cost(_cost), pos(_pos), used(_used),m1(-1),m2(-1){} 
    bool operator<(const Data& d) const{
        return cost < d.cost;
    }
 
    bool operator>(const Data& d) const{
        return cost > d.cost;
    }
};
 
int path[101][101];
int idx[101][101];
 
 
int main(){
    int n,m;
    while(~scanf("%d %d",&n,&m)){
        if(n==m && m==0) break;
 
        map<PP,int> cost;
        memset(path,0x3f,sizeof(path));
        vector<int> edge[101];
 
        for(int i=0;i<m;i++){
            int a,b,c;
            scanf("%d %d %d",&a,&b,&c);
            if(path[a][b] > c){
                edge[a].push_back(b);
                edge[b].push_back(a);
                path[b][a] = path[a][b] = c;
                idx[b][a] = idx[a][b] = i;
            }
        }
 
        priority_queue<Data,vector<Data>,greater<Data> > que;
        cost[PP(1,P(-1,-1))] = 0;
 
        que.push(Data(0,1,0,-1,-1));
 
        int minv;
        while(!que.empty()){
            Data d = que.top();
            que.pop();
 
            if(d.used !=1 && d.pos==n){
                minv = d.cost;
                break;
            }
 
            for(int i=0;i<edge[d.pos].size();i++){
                int to = edge[d.pos][i];
                if(to == d.pos) continue;
                if(path[d.pos][to] >= INF) continue;
                if(idx[d.pos][to] == d.m1) continue;
 
                if(d.used==0){
                    //cost pos used path1 path2
                    que.push(Data(d.cost,to,d.used+1,idx[d.pos][to],-1));
                     
                    map<PP,int>::iterator it = cost.find(PP(to,P(-1,-1)));
                    if(it != cost.end() && it->second > d.cost + path[d.pos][to]){
                        it->second = d.cost+path[d.pos][to];
 
                        //cost pos used
                        que.push(Data(d.cost+path[d.pos][to],to,d.used));
                    }
                    else if(it == cost.end()){
                        cost[PP(to,P(-1,-1))] = d.cost+path[d.pos][to];
 
                        //cost pos used
                        que.push(Data(d.cost+path[d.pos][to],to,d.used));
                    }
                     
                }
 
                else if(0< d.used && d.used < 2){
                    map<PP,int>::iterator it = cost.find(PP(to,P(min(d.m1,idx[d.pos][to]),max(d.m1,idx[d.pos][to]))));
                    if(it != cost.end() && it->second > d.cost){
                        it->second = d.cost;
 
                        //cost pos used path1 path2
                        que.push(Data(d.cost,to,d.used+1,min(d.m1,idx[d.pos][to]),max(d.m1,idx[d.pos][to])));
                    }
                    else if(it == cost.end()){
                        cost[PP(to,P(min(d.m1,idx[d.pos][to]),max(d.m1,idx[d.pos][to])))] = d.cost;
                        que.push(Data(d.cost,to,d.used+1,min(d.m1,idx[d.pos][to]),max(d.m1,idx[d.pos][to])));
                    }
                }
                else{
                    map<PP,int>::iterator it = cost.find(PP(to,P(d.m1,d.m2)));
                    if(it != cost.end() && it->second > d.cost + path[d.pos][to]){
                        it->second = d.cost + path[d.pos][to];
                        que.push(Data(d.cost + path[d.pos][to],to,d.used,d.m1,d.m2));
                    }
                    else if(it == cost.end()){
                        cost[PP(to,P(d.m1,d.m2))] = d.cost + path[d.pos][to];
                        que.push(Data(d.cost + path[d.pos][to],to,d.used,d.m1,d.m2));
                    }
                }
            }
        }
        printf("%d\n",minv);
    }
}

