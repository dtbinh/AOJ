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
const char ch_dir[] = {'U','R','D','L'};

void dfs(int sx,int sy,int dir){
  for(int i=0;i<4;i++){
    int next_dir = (dir + i + 3) % 4;
    int dx = tx[next_dir] + sx;
    int dy = ty[next_dir] + sy;
    if(dx < 0 || dx > 4 || dy < 0 || dy > 4) continue;
    if(!is_path[sx][sy][dx][dy]) continue;

    printf("%c",ch_dir[next_dir]);
    if(dx == 0 && dy == 0) return;

    dfs(dx,dy,next_dir);
    break;
  }
}

int main(){

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

  dfs(0,0,1);
  printf("\n");
}
