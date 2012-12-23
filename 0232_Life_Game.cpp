
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
 
int roulette[4];
int X,Y,Z;
double dp[51][5001];
 
struct Data{
    int ev;
    int val;
};
 
int main(){
    while(~scanf("%d %d %d",&X,&Y,&Z)){
        if(X==Y && Y==Z && Z==0) break;
 
        for(int i=0;i<X;i++){
            scanf("%d",roulette+i);
        }
        map<int,Data> stage;
        for(int i=0;i<Z;i++){
            int N,E,A;
            scanf("%d %d %d",&N,&E,&A);
            Data d = {E,A};
            stage[N] = d;
        }
 
 
        fill((double*)dp,(double*)dp+51*5001,0.0);
        dp[0][0] = 1.0;
 
        for(int pos = 0; pos < Y; pos++){
            for(int coin=0;coin <= Y*100; coin++){
                if(dp[pos][coin]==0) continue;
                for(int i=0;i<X;i++){
                    int next_pos = min(pos + roulette[i],Y);
                    int next_coin = coin;
 
                    if(next_pos < Y){
                        if(stage[next_pos].ev==1){
                            next_pos  = min(next_pos + stage[next_pos].val,Y);
                        }
                        else if(stage[next_pos].ev==2){
                            next_coin += stage[next_pos].val;
                        }
                        else if(stage[next_pos].ev==3){
                            next_coin -= stage[next_pos].val;
                            if(next_coin <= 0) next_coin = 0;
                        }
                    }
 
                    next_pos = min(next_pos,Y);
                    dp[next_pos][next_coin] += dp[pos][coin]/(double)X;
                }
            }
        }
 
        double exp = 0.0;
 
        for(int coin=0;coin<=5000;coin++){
            exp += coin*dp[Y][coin];
        }
 
        printf("%d\n",(int)(exp));
    }
}

