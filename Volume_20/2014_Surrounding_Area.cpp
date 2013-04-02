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

bool visited[51][51][1<<2];

void dfs(char stage[51][51],int occupy[51][51],int sx,int sy,int w,int h){
  if(visited[sx][sy][occupy[sy][sx]]) return;

  visited[sx][sy][occupy[sy][sx]] = true;
  for(int i=0;i<4;i++){
    int dx = tx[i] + sx;
    int dy = ty[i] + sy;
    if(dx < 0 || dx >= w || dy < 0 || dy >= h) continue;
    if(stage[dy][dx] == 'B' || stage[dy][dx] == 'W') continue;
    
       occupy[dy][dx] |= occupy[sy][sx];
       dfs(stage,occupy,dx,dy,w,h);
  }
}



int main(){
  int w,h;
  while(~scanf("%d %d",&w,&h)){
    if(w==0 && h==0) break;
    char stage[51][51];
    int occupy[51][51];
    memset(stage,'\0',sizeof(stage));
    memset(occupy,0,sizeof(occupy));
    memset(visited,0,sizeof(visited));
    for(int y=0;y<h;y++){
      char buf[51];
      scanf("%s",buf);
      for(int x=0;x<w;x++){
	stage[y][x] = buf[x];
	if(buf[x] == 'B') occupy[y][x] = 1;
	if(buf[x] == 'W') occupy[y][x] = (1<<1);
      }
    }
    for(int y=0;y<h;y++){
      for(int x=0;x<w;x++){
	if(stage[y][x] == '.') continue;
	dfs(stage,occupy,x,y,w,h);
      }
    }

    int B_num = 0;
    int W_num = 0;
    for(int y=0;y<h;y++){
      for(int x=0;x<w;x++){
	if(occupy[y][x] != (1<<2) - 1){
	  if((occupy[y][x] & 1) && stage[y][x] != 'B') B_num++;
	  if((occupy[y][x] & (1<<1)) && stage[y][x] != 'W') W_num++;
	}
      }
    }

    printf("%d %d\n",B_num,W_num);
  }
}
