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
 
//int tx[] = {0,1,0,-1};
//int ty[] = {-1,0,1,0};
 
const int tx[] = {0,1,1,0};
const int ty[] = {0,0,1,1};
 
static const double EPS = 1e-8;
 
void flipStage(int px,int py,int stage[5][5],int _count=1){
    //px:0,1,2,3
    //py:0,1,2,3
    //px:0,py:0
    if(py < 0) return;
 
    for(int c=0;c<_count;c++){
        for(int i=0;i<4;i++){
            int dx = px + tx[i];
            int dy = py + ty[i];
            if(stage[dy][dx] == 0) continue;
 
            stage[dy][dx] %= 4;
            stage[dy][dx]++;
        }
    }
}
 
int calcStage(int stage[5][5]){
    const int point[] = {0,60,70,80};
 
    int sum = 0;
    for(int y=0;y<5;y++){
        for(int x=0;x<5;x++){
            if(stage[y][x] == 0) continue;
            sum += point[stage[y][x]-1];
        }
    }
    return sum;
}
 
int calcLine(int stage[5][5],int y){
    const int point[] = {0,60,70,80};
 
    int sum = 0;
    for(int x=0;x<5;x++){
        if(stage[y][x] == 0) continue;
        sum += point[stage[y][x]-1];
    }
    return sum;
}
 
int dp[6][256];
 
int main(){
    int N;
    while(~scanf("%d",&N)){
        if(N==0) break;
        for(int i=0;i<N;i++){
            int stage[5][5];
            memset(stage,0,sizeof(stage));
 
            for(int y=0;y<5;y++){
                for(int x=0;x<5;x++){
                    int num;
                    scanf("%d",&num);
                    stage[y][x] = num;
                }
            }
 
            memset(dp,0,sizeof(dp));
 
            for(int y=0;y<4;y++){
 
                for(int S1=0;S1<256;S1++){
                        int tmp1 = S1;
                        int pos1 = 0;
                        int tmp1_stage[5][5];
                        memcpy(tmp1_stage,stage,sizeof(stage));
 
                        while(tmp1 > 0){
                            int c = tmp1 % 4;
                            tmp1 /= 4;
                            int x = pos1++;
                            flipStage(x,y-1,stage,c);
                        }
 
                    for(int S2=0;S2<256;S2++){
                        int tmp2 = S2;
                        int pos2 = 0;
                        int tmp2_stage[5][5];
                        memcpy(tmp2_stage,stage,sizeof(stage));
 
                        while(tmp2 > 0){
                            int c = tmp2 % 4;
                            tmp2 /= 4;
 
                            int x = pos2++;
                            flipStage(x,y,stage,c);
                        }
 
                        int score = calcLine(stage,y);
                        if(y==3) score+=calcLine(stage,y+1);
 
                        dp[y+1][S2] = max(dp[y][S1]+score,dp[y+1][S2]);
 
                        memcpy(stage,tmp2_stage,sizeof(tmp2_stage));
                    }
                    memcpy(stage,tmp1_stage,sizeof(tmp1_stage));
                }
            }
 
            int res = 0;
            for(int S=0;S<256;S++){
                res = max(dp[4][S],res);
            }
 
            printf("%d\n",res);
        }
    }
}
