
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
 
static const char RGB[]={'R','G','B'};
int w,h;
 
class Data{
public:
    char stage[10][10];
    int count;
    Data() : count(0), stage(){}
    Data(char _stage[10][10],int _count){
        memcpy(this->stage,_stage,sizeof(char)*10*10);
        this->count = _count;
    }
    bool operator>(const Data& d) const{
        return this->count > d.count;
    }
 
    bool operator<(const Data& d) const{
        return this->count < d.count;
    }
};
 
void dfs(char stage[10][10],int x,int y,int from,int to,bool visited[10][10]){
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
 
string stg2str(char stage[10][10]){
    string res = "";
    for(int y=0;y<h;y++){
        for(int x=0;x<w;x++){
            res += stage[y][x];
        }
    }
 
    return res;
}
 
int main()
{
    while(~scanf("%d %d",&w,&h)){
        if(h==w && w==0) break;
 
        char stage[10][10];
        memset(stage,'\0',sizeof(stage));
        for(int y=0;y<h;y++){
            for(int x=0;x<w;x++){
                char ch;
                cin >> ch;
                stage[y][x] = ch;
            }
        }
 
        int minv = numeric_limits<int>::max();
        string init = stg2str(stage);
         
 
        priority_queue<Data,vector<Data>,greater<Data> > que;
        que.push(Data(stage,0));
 
        map<string,int> cost;
 
        cost[init] = 0;
 
        while(!que.empty()){
            Data d = que.top();
            que.pop();
 
            for(int i=0;i<3;i++){
                char next[10][10];
                memcpy(next,d.stage,sizeof(char)*10*10);
 
                bool visited[10][10];
                memset(visited,0,sizeof(visited));
                dfs(next,0,0,d.stage[0][0],RGB[i],visited);
 
 
                string str = stg2str(next);
                if(cost.find(str) != cost.end() && cost[str] <= d.count + 1) continue;
 
                cost[str] = d.count + 1;
 
                que.push(Data(next,d.count+1));
            }
        }
 
        for(int i=0;i<3;i++){
            string ans="";
            while(ans.size() < w*h) ans.push_back(RGB[i]);
            if(cost.find(ans) != cost.end()) minv = min(cost[ans],minv);
        }
 
        printf("%d\n",minv);
 
    }
}

