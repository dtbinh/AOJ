
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
 
 
void printStage(char stage[20][20],int W,int H,int i,int n){
    for(int y=0;y<H;y++){
        for(int x=0;x<W;x++){
            printf("%c",stage[y][x]);
        }
        printf("\n");
    }
    if(i != n-1) printf("\n");
}
int main(){
    int n;
    while(~scanf("%d",&n)){
        for(int i=0;i<n;i++){
            int W,H;
            char stage[20][20];
 
            scanf("%d %d",&H,&W);
 
            int px,py;
            for(int y=0;y<H;y++){
                char buf[32];
                scanf("%s",buf);
                for(int x=0;x<W;x++){
                    stage[y][x] = buf[x];
                    if(buf[x]=='>'
                        || buf[x]=='<'
                        || buf[x]=='^'
                        || buf[x]=='v'){
                            px = x;
                            py = y;
                    }
                }
            }
 
            int com;
            char buf[128];
            scanf("%d",&com);
            scanf("%s",buf);
            for(int j=0;j<com;j++){
                switch(buf[j]){
                case 'U':
                    stage[py][px] = '^';
                    if(py -1 >= 0 && stage[py-1][px] == '.'){
                        stage[py][px] = '.';
                        stage[py-1][px] = '^';
                        py--;
                    }
                    break;
                case 'D':
                    stage[py][px] = 'v';
                    if(py +1 < H && stage[py+1][px] == '.'){
                        stage[py][px] = '.';
                        stage[py+1][px] = 'v';
                        py++;
                    }
                    break;
                case 'L':
                    stage[py][px] = '<';
                    if(px -1 >= 0 && stage[py][px-1] == '.'){
                        stage[py][px] = '.';
                        stage[py][px-1] = '<';
                        px--;
                    }
                    break;
                case 'R':
                    stage[py][px] = '>';
                    if(px +1 < W && stage[py][px+1] == '.'){
                        stage[py][px] = '.';
                        stage[py][px+1] = '>';
                        px++;
                    }
                    break;
 
                case 'S':
                    switch(stage[py][px]){
                    case '^':
                        for(int y=py;y>=0;y--){
                            if(stage[y][px] == '#'){
                                break;
                            }
                            if(stage[y][px] == '*'){
                                stage[y][px] = '.';
                                break;
                            }
                        }
                        break;
                    case 'v':
                        for(int y=py;y<H;y++){
                            if(stage[y][px] == '#'){
                                break;
                            }
                            if(stage[y][px] == '*'){
                                stage[y][px] = '.';
                                break;
                            }
                        }
                        break;
                    case '<':
                        for(int x=px;x>=0;x--){
                            if(stage[py][x] == '#'){
                                break;
                            }
                            if(stage[py][x] == '*'){
                                stage[py][x] = '.';
                                break;
                            }
                        }
                        break;
                    case '>':
                        for(int x=px;x<W;x++){
                            if(stage[py][x] == '#'){
                                break;
                            }
                            if(stage[py][x] == '*'){
                                stage[py][x] = '.';
                                break;
                            }
                        }
                        break;
                    default:
                        break;
                    }
 
                default:
                    break;
                }
            }
 
            printStage(stage,W,H,i,n);
        }
    }
}

