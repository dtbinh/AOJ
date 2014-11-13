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
 
const static int tx[] = {0,1,0,-1};
const static int ty[] = {-1,0,1,0};

const static double EPS = 1e-8;

struct Face {
  int diff_x;
  int diff_y;
  int num;
  Face(int x,int y,int n)
    : diff_x(x),diff_y(y),num(n) {}
};

int stage[5][5];

void bfs(int start_x,int start_y,vector<Face>& face){
  queue<P> que;
  bool visited[5][5] = {};
  while(!que.empty()){
    P p = que.front();
    que.pop();
    visited[p.first][p.second] = true;
    for(int i = 0; i < 4; i++){
      int dx = p.first + tx[i];
      int dy = p.second + ty[i];
      if(dx >= 5 || dx < 0 || dy >= 5 || dy < 0) continue;
      if(visited[dx][dy]) continue;
      if(stage[dy][dx] != 0){
	face.push_back(Face(start_x - dx,start_y - dy,stage[dy][dx]));
      }
    }
  }
}

int main(){
  int N;
  while(~scanf("%d",&N)){
    for(int i = 0; i < N; i++){

      int start_x = -1;
      int start_y = -1;
      int start_num = -1;
      for(int y = 0; y < 5; y++){
	for(int x = 0; x < 5; x++){
	  scanf("%d",&stage[y][x]);
	  if(stage[y][x] != 0){
	    start_x = x;
	    start_y = y;
	    start_num = stage[y][x];
	  }
	}
      }
      vector<Face> face;
      face.push_back(Face(0,0,start_num));
    }
  }
}
