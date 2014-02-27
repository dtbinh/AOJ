#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f

#include <iostream>
#include <cstdio>
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
  
static const double EPS = 1e-8;
  
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};

bool is_path[10][10][10][10];
bool visited[10][10];

void dfs(int sx,int sy){
  if(visited[sx][sy]) return;

  visited[sx][sy] = true;

  for(int i=0;i<4;i++){
    int dx = tx[i] + sx;
    int dy = ty[i] + sy;
    if(dx < 0 || dx > 4 || dy < 0 || dy > 4) continue;
    if(!is_path[sx][sy][dx][dy]) continue;

    is_path[sx][sy][dx][dy] = false;
    const char ch_dir[] = {'U','R','D','L'};
    printf("%c\n",ch_dir[i]);

    dfs(dx,dy);
  }
}

int main(){
  memset(visited,false,sizeof(visited));
  memset(is_path,false,sizeof(is_path));
  for(int i=0;i<9;i++){
    char buf[8];
    scanf("%s",buf);
    int y = i / 2;
    
    if(i % 2 == 0){
      for(int x=0;x<4;x++){
	if(buf[x] == '1'){
	  is_path[x][y][x+1][y] = true;
	  is_path[x+1][y][x][y] = true;
	}
      }
    }
    else if(i % 2 != 0){
      for(int x=0;x<5;x++){
	if(buf[x] == '1'){
	  is_path[x][y][x][y+1] = true;
	  is_path[x][y+1][x][y] = true;
	}
      }
    }
  }

  dfs(0,0);
}
