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

vector<P> edges[25][25][25*25];
int A[25*25][25*25];
int B[25*25];

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

    memset(A,0,sizeof(A));
    memset(B,0,sizeof(B));

    for(int y = 0; y < rows; y++){
      for(int x = 0; x < cols; x++){
	int status;
	scanf("%d",&status);
	B[y * cols + x] = status;
      }
    }

    for(int sy = 0; sy < rows; sy++){
      for(int sx = 0; sx < cols; sx++){
	A[sy * cols + sx][sy * cols + sx] = 1;
	for(int i = 0; i < edges[sy][sx][proper_distance].size(); i++){
	  int dx = edges[sy][sx][proper_distance][i].first;
	  int dy = edges[sy][sx][proper_distance][i].second;
	  if(dx < 0 || dx >= cols || dy < 0 || dy >= rows) continue;
	  A[sy * cols + sx][dy * cols + dx] = 1;
	}
      }
    }

    for(int round = 0; round < rows * cols; round++){

      int pivot = round;
      bool has_pivot= false;
      for(int row = round; row < rows * cols; row++){
	if(A[row][round] == 1){
	  has_pivot = true;
	  pivot = row;
	  break;
	}
      }
      if(!has_pivot) continue;

      swap(A[pivot],A[round]);
      swap(B[pivot],B[round]);
      for(int row = 0; row < rows * cols; row++){
	if(round == row) continue;
	if(A[row][round] == 0) continue;

	B[row] ^= B[round];
	for(int col = round; col < rows * cols; col++){
	  A[row][col] ^= A[round][col];
	}
      }
    }

    bool isok = true;

    for(int pos = 0; pos < cols * rows; pos++){
      if(A[pos][pos] == 0 && B[pos] == 1){
      	isok = false;
      	break;
      }
    }
    printf("%d\n",isok ? 1 : 0);
  }
}
