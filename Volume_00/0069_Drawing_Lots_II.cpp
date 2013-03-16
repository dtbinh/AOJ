
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
 
char path[100][100];
int m,hit,d,n;
int gFrom;
 
void dfs(int y,int from){
    if(y>=d+1){
        //cout << from << endl;
        gFrom = from;
        return;
    }
 
    bool isMove = false;
 
    for(int to=from-1;to<=from+1;to++){
        if(to == from) continue;
 
        if(to < 1 || to > n) continue;
        if(to > from && path[y][to-1] == '1'){
            dfs(y+1,to);
            isMove = true;
            break;
        }
        else if(to < from && path[y][to] == '1'){
            dfs(y+1,to);
            isMove = true;
            break;
        }
    }
 
    if(!isMove) dfs(y+1,from);
}
 
int main(){
 
    while(~scanf("%d",&n)){
        if(n==0) break;
        scanf("%d %d %d",&m,&hit,&d);
        for(int y=1;y<=d;y++){
            char buf[32];
            scanf("%s",buf);
            for(int x=1;x<=n-1;x++){
                path[y][x] = buf[x-1];
            }
        }
 
        gFrom = 0;
        dfs(1,m);
        if(gFrom == hit){
            printf("%d\n",0);
            continue;
        }
 
        for(int y=1;y<=d;y++){
            for(int x=1;x<n;x++){
                if(x==1){
                    if(path[y][x] == '0'){
                        if(path[y][x+1] == '1') continue;
                        path[y][x] = '1';
                        gFrom = 0;
                        dfs(1,m);
                        if(gFrom == hit){
                            printf("%d %d\n",y,x);
                            goto last;
                        }
                        path[y][x] = '0';
                    }
                }
                else if(x==n-1){
                    if(x-1 < 1) continue;
                    if(path[y][x-1] == '0'){
 
                        if(path[y][x] == '1') continue;
                        path[y][x] = '1';
                        gFrom = 0;
                        dfs(1,m);
                        if(gFrom == hit){
                            printf("%d %d\n",y,x);
                            goto last;
                        }
                        path[y][x] = '0';
                    }
                }
                else{
                    if(x-1 < 1 || x+1 > n-1) continue;
                    if(path[y][x-1] != '1'
                        && path[y][x+1] != '1'){
                            if(path[y][x] == '1') continue;
                            path[y][x] = '1';
                            gFrom = 0;
                            dfs(1,m);
                            if(gFrom == hit){
                                printf("%d %d\n",y,x);
                                goto last;
                            }
                            path[y][x] = '0';
                    }
                }
            }
        }
 
        printf("%d\n",1);
last:;
        //cout << dfs(1,m) << endl;
        //cout << dfs(1,m) << " " <<"\n";
    }
}

