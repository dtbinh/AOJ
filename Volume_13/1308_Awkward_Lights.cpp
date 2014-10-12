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

int main(){
  int cols;
  int rows;
  int proper_distance;
  while(~scanf("%d %d %d",&cols,&rows,&proper_distance)){
    int stage[32][32];
    int idx[32][32];
    int current_idx = 0;
    for(int y = 0; y < rows; y++){
      for(int x = 0; x < cols; x++){
	int status;
	scanf("%d",&status);
	stage[y][x] = status;
	if(status == 1){
	  idx[y][x] = current_idx++;
	}
      }
    }

    vector<int> edges[32];
    for(int sy = 0; sy < rows; sy++){
      for(int sx = 0; sx < cols; sx++){
	if(stage[sy][sx] == 0) continue;
	for(int dy = 0; dy < rows; dy++){
	  for(int dx = 0; dx < cols; dx++){
	    if(abs(dy-sy) + abs(dx-sx) != proper_distance) continue;
	    if(stage[dy][dx] == 0) continue;
	    edges[idx[sy][sx]].push_back(idx[dy][dx]);
	  }
	}
      }
    }

    
  }
}
