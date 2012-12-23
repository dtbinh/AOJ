
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
 
bool visited[1<<24];
 
class Data{
public:
    int x;
    int y;
    int r;
    int c;
    Data(int _x,int _y,int _r,int _c){
        x = _x;
        y = _y;
        r = _r;
        c = _c;
    }
};
 
 
 
bool check(const vector<Data>& d,int a,int b,int visited){
    //true then erase
    if(d[a].c != d[b].c) return false;
    for(int i=0;i<a;i++){
        if(visited & (1<<i)) continue;
        if((d[a].x-d[i].x)*(d[a].x-d[i].x)+(d[a].y-d[i].y)*(d[a].y-d[i].y) < (d[a].r + d[i].r)*(d[a].r + d[i].r)) return false;
    }
    for(int i=0;i<b;i++){
        if(visited & (1<<i)) continue;
        if((d[b].x-d[i].x)*(d[b].x-d[i].x)+(d[b].y-d[i].y)*(d[b].y-d[i].y) < (d[b].r + d[i].r)*(d[b].r + d[i].r)) return false;
    }
 
    return true;
}
 
void dfs(const vector<Data>& nodes,int got){
    visited[got] = true;
 
    for(int i=0;i<nodes.size();i++){
        for(int j=i+1;j<nodes.size();j++){
            if(got & (1<<i) || got & (1<<j)) continue;
            if(check(nodes,i,j,got)){
                int tmp = got;
                tmp |= (1<<i);
                tmp |= (1<<j);
 
                if(visited[tmp]) continue;
                dfs(nodes,tmp);
            }
        }
    }
}
 
int main(){
    int n;
    while(~scanf("%d",&n)){
        if(n==0) break;
        memset(visited,0,sizeof(visited));
 
        int x,y,r,c;
        vector<Data> nodes; 
        for(int i=0;i<n;i++){
            scanf("%d %d %d %d",&x,&y,&r,&c);
            nodes.push_back(Data(x,y,r,c));
        }
 
        dfs(nodes,0);
 
        int res = 0;
        for(int S=(1<<n)-1;S>=0;S--){
            if(visited[S]){
                int tmp=0;
                for(int i=0;i<n;i++) tmp += (bool)((1<<i) & S);
                res = max(tmp,res);
            }
        }
        printf("%d\n",res);
    }
}

