
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
 
class Goods{
public:
    int w;
    int p;
    Goods(int _w,int _p) : w(_w), p(_p) {}
};
 
int dp[101][301];
 
int main(){
    int s,d,m;
 
    while(~scanf("%d %d %d",&s,&d,&m)){
 
        map<int,vector<Goods> > data;
 
        for(int i=0;i<s;i++){
            int k;
            scanf("%d",&k);
 
            for(int j=0;j<k;j++){
                int w,p;
                scanf("%d %d",&w,&p);
                data[i].push_back(Goods(w,p));
            }
        }
 
        vector<int> days;
 
        for(int i=0;i<d;i++){
            int f;
            scanf("%d",&f);
            days.push_back(f);
        }
 
 
        memset(dp,0,sizeof(dp));
 
        for(int idx=0;idx<days.size();idx++){
            vector<Goods>& it = data[days[idx]];
 
            int cost[301]; 
            memset(cost,0,sizeof(cost));
 
            for(int i=0;i < it.size();i++){
                    int w = it[i].w;
                    int p = it[i].p;
                    for(int used=m-p;used>=0;used--){
                        cost[used+p] = max(cost[used]+w,cost[used+p]);
                    }
            }
 
            for(int j=0;j<=300;j++){
                for(int used=0;used<=j;used++){
                    dp[idx+1][j] = max(dp[idx+1][j],dp[idx][j-used]+cost[used]);
                }
            }
        }
 
        int resw=0;
        int resm=0;
        for(int i=0;i<=m;i++){
            if(resw < dp[d][i]){
                resm = i;
                resw = dp[d][i];
            }
        }
 
        printf("%d %d\n",resw,resm);
    }
}

