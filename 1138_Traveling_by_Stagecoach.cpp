
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
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
int path[31][31];
float cost[31][1<<8];
 
class Data{
public:
    float cost;
    int now;
    int used;
    Data(int _n,float _c,int _u){       
        now = _n;
        cost = _c;
        used = _u;
    }
 
    bool operator>(const Data& d) const{
        return cost > d.cost;
    }
};
 
int main(){
    int n,m,p,a,b;
    while(~scanf("%d %d %d %d %d",&n,&m,&p,&a,&b)){
        if(n==0 && m==0 && p==0 && a==0 && b==0) break;
        //m : number of cities
        memset(path,-1,sizeof(path));
        fill((float*)cost,(float*)cost+(1<<8)*31,100000000.0);
        int *t = new int[n]();
 
        for(int i=0;i<n;i++){
            scanf("%d",t+i);
        }
 
        for(int i=0;i<p;i++){
            int x,y,z;
            scanf("%d %d %d",&x,&y,&z);
            path[x][y] = path[y][x] = z;
        }
 
        cost[a][0] = 0;
 
        priority_queue<Data,vector<Data>,greater<Data> > que;
 
        que.push(Data(a,0,0));
 
        while(!que.empty()){
            float c = que.top().cost;
            int now = que.top().now;
            int used = que.top().used;
 
            que.pop();
            for(int to=1;to<=m;to++){
                if(to==now) continue;
                if(path[now][to] == -1) continue;
 
                for(int j=0;j<n;j++){
                    if(used & (1<<j)) continue;               
                    if(cost[to][used | (1<<j)] <= c + (float)path[now][to]/(float)t[j]) continue;
 
                    cost[to][used | (1<<j)] = c + (float)path[now][to]/(float)t[j];
                    que.push(Data(to,c + (float)path[now][to]/(float)t[j],used | (1<<j)));
                }
            }
        }
 
        float res = numeric_limits<float>::max();
 
        for(int S=0;S<=(1<<n)-1;S++){
            res = min(cost[b][S],res);
        }
 
        if(100000000.0 <= res) printf("Impossible\n");
        else printf("%f\n",res);
 
        delete[] t;
    }
}

