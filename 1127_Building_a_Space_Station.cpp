
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
 
double path[100][100];
double mincost[100];
bool used[100];
 
class Data{
public:
    double x;
    double y;
    double z;
    double r;
    Data(double _x,double _y,double _z,double _r){
        x = _x;
        y = _y;
        z = _z;
        r = _r;
    }
};
 
int main(){
    int n;
    while(~scanf("%d",&n)){
        if(n==0) break;
        vector<Data> nodes;
 
        fill((bool*)used,(bool*)used + 100,false);
        fill((double*)mincost,(double*)mincost + 100,numeric_limits<double>::max());
 
        for(int i=0;i<n;i++){
            double x,y,z,r;
            scanf("%lf %lf %lf %lf",&x,&y,&z,&r);
            nodes.push_back(Data(x,y,z,r));
        }
 
         
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                double diff = sqrt((nodes[i].x-nodes[j].x) * (nodes[i].x-nodes[j].x)
                    + (nodes[i].y-nodes[j].y) * (nodes[i].y-nodes[j].y)
                    + (nodes[i].z-nodes[j].z) * (nodes[i].z-nodes[j].z));
                double cost = (diff - (nodes[i].r + nodes[j].r) >= 0 ? diff - (nodes[i].r + nodes[j].r) : 0);
                path[i][j] = path[j][i] = cost;
            }
        }
 
 
        mincost[0]=0;
 
        double res=0;
        while(1){
            int v=-1;
            for(int u=0;u<n;u++){
                if(!used[u] && (v==-1 || mincost[u] < mincost[v])){
                    v = u;
                }
            }
 
            if(v==-1) break;
            used[v] = true;     
            res+=mincost[v];
             
            for(int u=0;u<n;u++){
                mincost[u] = min(mincost[u],path[v][u]);
            }
             
        }
 
        printf("%.3lf\n",res);
    }
}

