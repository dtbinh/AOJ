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
 
class Data{
public:
  int mX;
  int mY;
  Data(int _x,int _y){
    mX = _x;
    mY = _y;
  }
  Data():mX(0),mY(0){}
};
 
Data path[100][100];
bool visited[100][100];
 
int main(){
 
  int W;
  while(~scanf("%d",&W)){
    if(W==0) break;
 
    memset(visited,0,sizeof(visited));
    for(int y=0;y<W;y++){
      for(int x=0;x<W;x++){
	int nx,ny;
	cin >> nx >> ny;
	path[y][x] = Data(nx,ny);
      }
    }
 
    int res = 0;
    for(int y=0;y<W;y++){
      for(int x=0;x<W;x++){
	if(visited[y][x]) continue;
 
	bool tmp[100][100];
	memcpy(tmp,visited,sizeof(bool)*100*100);
 
	int sx = x;
	int sy = y;
	tmp[sy][sx] = true;
 
	int nx = sx;
	int ny = sy;
	for(int i=0;i<=W*W;i++){
	  int prev_x = nx;
	  int prev_y = ny;
	  nx = path[prev_y][prev_x].mX;
	  ny = path[prev_y][prev_x].mY;
	  tmp[ny][nx] = true;
 
	  if(nx==sx && ny==sy){
	    res++;
	    memcpy(visited,tmp,sizeof(bool)*100*100);
	    break;
	  }
	}
      }
    }
 
    printf("%d\n",res);
  }
}
