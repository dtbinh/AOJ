
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
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
 
static const double EPS = 1e-8;
 
int tx[] = {-1,0,1,1};
int ty[] = {1,1,0,-1};
 
int stage[10][10];
 
void printStage(int N){
    for(int y=0;y<N;y++){
        for(int x=0;x<N;x++){
            printf("%3d",stage[y][x]);
        }
        printf("n");
    }
}
 
int main(){
    int N;
    int idx=1;
    while(~scanf("%d",&N)){
        if(N==0) break;
        int x = 0;
        int y = 0;
        int dx=0,dy=0;
        int dir = 2;
        int prev = 2;
 
        stage[0][0] = 1;
        for(int num=2;num<=N*N;num++){
            dy = y + ty[dir];
            dx = x + tx[dir];
            stage[dy][dx] = num;
            //printf("dir:%dn",dir);
            //printStage(N);
 
            //0:lower left 1:lower 2:right 3:upper right
 
            x = dx;
            y = dy;
 
            if(prev == 0){
                dx = x + tx[prev];
                dy = y + ty[prev];
                if(dx<0 || dx>=N || dy<0 || dy>=N){
                    dir = 1;
                    dx = x + tx[dir];
                    dy = y + ty[dir];
                }
 
                if(dx<0 || dx>=N || dy<0 || dy>=N){
                    dir = 2;
                    dx = x + tx[dir];
                    dy = y + ty[dir];
                }
            }
 
            else if(prev==1){
                if(x==0) dir = 3;
                else dir = 0;
            }
 
            else if(prev==2){
                if(y==0) dir = 0;
                else dir = 3;
            }
 
            else if(prev==3){
                dx = x + tx[prev];
                dy = y + ty[prev];
                if(dx<0 || dx>=N || dy<0 || dy>=N){
                    dir = 2;
                    dx = x + tx[dir];
                    dy = y + ty[dir];
                }
 
                if(dx<0 || dx>=N || dy<0 || dy>=N){
                    dir = 1;
                    dx = x + tx[dir];
                    dy = y + ty[dir];
                }
            }
 
 
            prev = dir;
 
             
        }
        printf("Case %d:n",idx++);
        printStage(N);
    }
}

