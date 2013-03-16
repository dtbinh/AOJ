
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
 
 
static const double EPS = 1e-8;
 
int tx[] = {-1,0,1,0};
int ty[] = {0,1,0,-1};
 
class Data{
public:
    int time;
    bool login;
    Data() : time(0),login(false){}
    Data(int t,int l){
        this->time = t;
        this->login = l;
    }
};
 
int main()
{
    int N,M;//N:pc M:student
    while(~scanf("%d %d",&N,&M)){
        if(N==M && M==0) break;
        map<P,vector<Data> > log;
        int r;
        scanf("%d",&r);
        for(int i=0;i<r;i++){
            //s:1 login s:0 logout
            //Pc n
            //student m
            //time t
            int t,n,m,s;
            scanf("%d %d %d %d",&t,&n,&m,&s);
            log[P(n,m)].push_back(Data(t,s));
        }
        int q;
        scanf("%d",&q);
 
        for(int i=0;i<q;i++){
            int ts,te,m;
            //student m
            scanf("%d %d %d",&ts,&te,&m);
 
            bool stay[1270];
            fill(stay,stay+1270,false);
            //memset(stay,0,sizeof(stay));
 
            for(int j=1;j<=N;j++){
                if(log.find(P(j,m)) == log.end()) continue;
                for(int k=0;k<log[P(j,m)].size();k+=2){
                    int s = max(log[P(j,m)][k].time,ts);
                    int e = min(log[P(j,m)][k+1].time,te);
                    if(e-s<=0) continue;
                    for(int l=s;l<=e;l++) stay[l] = true;
                }
            }
 
            int res = 0;
            for(int j=0;j<1270;j++){
                if(stay[j]){
                    int k=j;
                    for(;k<1270;k++){
                        if(!stay[k]) break;
                    }               
                    res += k-j-1;
                    j=k-1;
                }
            }
            printf("%d\n",res);
        }
 
 
    }
}

