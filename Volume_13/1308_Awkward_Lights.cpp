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
#include <complex>
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;

typedef complex<double> Point;
const static double EPS = 1e-12;

vector<P> edges[25][25][25*25+1];
bool stage[25][25];

bool check(int cols,int rows){
  for(int y = 0; y < rows; y++){
    for(int x = 0; x < cols; x++){
      if(stage[y][x]) return false;
    }
  }
  return true;
}

bool dfs(int pos,int proper_distance,int cols,int rows){
  if(pos >= cols * rows){
    if(check(cols,rows)) return true;
    return false;
  }
  int x = pos % rows;
  int y = pos / rows;

  bool res = false;
  res |= dfs(pos+1,proper_distance,cols,rows);

  if(stage[y][x]){
    bool tmp[25][25];
    memcpy(tmp,stage,sizeof(tmp));
    stage[y][x] = false;
    for(int i = 0; i < edges[y][x][proper_distance].size();i++){
      int dx = edges[y][x][proper_distance][i].first;
      int dy = edges[y][x][proper_distance][i].second;
      if(dx < 0 || dx >= cols || dy < 0 || dy >= rows) continue;
      stage[dy][dx] = !stage[dy][dx];
    }
    res |= dfs(pos+1,proper_distance,cols,rows);

    for(int i = 0; i < edges[y][x][proper_distance].size();i++){
      int dx = edges[y][x][proper_distance][i].first;
      int dy = edges[y][x][proper_distance][i].second;

      if(dx < 0 || dx >= cols || dy < 0 || dy >= rows) continue;
      memcpy(stage,tmp,sizeof(bool)*25*25);

      stage[dy][dx] = !stage[dy][dx];
      stage[y][x] = false;
      for(int j = 0; j < edges[dy][dx][proper_distance].size();j++){
	int nx = edges[dy][dx][proper_distance][j].first;
	int ny = edges[dy][dx][proper_distance][j].second;
	if(nx < 0 || nx >= cols || ny < 0 || ny >= rows) continue;
	if(nx == x && ny == y) continue;
	stage[ny][nx] = !stage[ny][nx];
      }

      res |= dfs(pos+1,proper_distance,cols,rows);
    }
  }
  return res;
}

int main(){
  for(int sy = 0; sy < 25; sy++){
    for(int sx = 0; sx < 25; sx++){
      for(int dy = 0; dy < 25; dy++){
	for(int dx = 0; dx < 25; dx++){
	  edges[sy][sx][abs(dy-sy) + abs(dx-sx)].push_back(P(dx,dy));
	}
      }
    }
  }

  int cols;
  int rows;
  int proper_distance;
  while(~scanf("%d %d %d",&cols,&rows,&proper_distance)){
    if(cols == 0 && rows == 0 && proper_distance == 0) break;

    for(int y = 0; y < rows; y++){
      for(int x = 0; x < cols; x++){
	int status;
	scanf("%d",&status);
	stage[y][x] = (status == 1 ? true : false);
      }
    }
    printf("%d\n",dfs(0,proper_distance,cols,rows) ? 1 : 0);
  }
}
