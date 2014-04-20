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

int matrix_size;
int matrix[16][16];

void rotate(int r,int c,int size,int angle){
  int tmp[size][size];
  for(int y=r;y<r+size;y++){
    for(int x=c;x<c+size;x++){
      tmp[y-r][x-c] = matrix[y][x];
    }
  }

  
}

void reversal(int r,int c,int size){
  for(int y=r;y<r+size;y++){
    for(int x=c;x<c+size;x++){
      matrix[y][x] = (matrix[y][x] ? 0 : 1);
    }
  }
}

void left_shift(int r){
  int tmp[16];
  for(int i=1;i<matrix_size;i++){
    tmp[i-1] = matrix[r][i];
  }
  tmp[matrix_size - 1] = matrix[r][0];
  for(int i=0;i<matrix_size;i++){
    matrix[r][i] = tmp[i];
  }
}

void right_shift(int r){
  int tmp[16];
  for(int i=0;i+1<matrix_size;i++){
    tmp[i+1] = matrix[r][i];
  }
  tmp[0] = matrix[r][matrix_size - 1];
  for(int i=0;i<matrix_size;i++){
    matrix[r][i] = tmp[i];
  }
}

void dfs(int base,int r,int c){
  matrix[r][c] = (base ? 0 : 1);
  for(int i=0;i<4;i++){
    int dr = r + ty[i];
    int dc = c + tx[i];
    if(dr < 0 || dc < 0
       || dr >= matrix_size || dc >= matrix_size) continue;
    if(matrix[dr][dc] == base){
      dfs(base,dr,dc);
    }
  }
}

void island_reversal(int r,int c){
  int base = matrix[r][c];
  dfs(base,r,c);
}

int main(){
  int total_operations;
  while(~scanf("%d %d",&matrix_size,&total_operations)){
    for(int y=0;y<matrix_size;y++){
      for(int x=0;x<matrix_size;x++){
	scanf("%d",&matrix[y][x]);
      }
    }
    for(int operation_idx = 0; operation_idx < total_operations; operation_idx++){
      int type;
      scanf("%d",&type);
      int r,c,angle,size;
      switch(type){
      case 0:
	scanf("%d %d %d %d",&r,&c,&angle,&size);
	rotate(r,c,angle,size);
	break;
      case 1:
	scanf("%d %d %d %d",&r,&c,&size);
	reversal(r,c,size);
	break;
      case 2:
	scanf("%d",&r);
	left_shift(r);
	break;
      case 3:
	scanf("%d",&r);
	right_shift(r);
	break;
      case 4:
	scanf("%d %d",&r,&c);
	island_reversal(r,c);
	break;
      default:
	break;
      }
    }
  }
}
