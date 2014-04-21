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
  for(int y=r;y<r+size;y++){
    for(int x=c;x<c+size;x++){
      printf("%d ",tmp[y-r][x-c]);
    }
    printf("\n");
  }
  
  int offset_y = (angle == 90 || angle == 180) ? size - 1 : 0;
  int offset_x = (angle == 180 || angle == 270) ? size - 1 : 0;
  
  int next[size+1][size+1];
  for(int y=0;y<size;y++){
    for(int x=0;x<size;x++){
      double dx = x * cos((double)angle * M_PI/180.0) + y * sin((double)angle * M_PI/180.0) + offset_x;
      double dy = - x * sin((double)angle * M_PI/180.0) + y * cos((double)angle * M_PI/180.0) + offset_y;
      printf("x:%d y:%d\n",x,y);
      printf("dx:%d dy:%d\n",(int)(dx + (dx < 0 ? - EPS : EPS)),(int)(dy + (dy < 0 ? - EPS : EPS)));
      next[(int)(dy + (dy < 0 ? - EPS : EPS))][(int)(dx + (dx < 0 ? - EPS : EPS))] = tmp[y][x];
    }
  }

  for(int y=r;y<r+size;y++){
    for(int x=c;x<c+size;x++){
      printf("%d ",next[y-r][x-c]);
    }
    printf("\n");
  }

  for(int y=r;y<r+size;y++){
    for(int x=c;x<c+size;x++){
      matrix[y][x] = next[y-r][x-c];
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
	rotate(r-1,c-1,angle,size);
	break;
      case 1:
	scanf("%d %d %d %d",&r,&c,&size);
	reversal(r-1,c-1,size);
	break;
      case 2:
	scanf("%d",&r);
	left_shift(r-1);
	break;
      case 3:
	scanf("%d",&r);
	right_shift(r-1);
	break;
      case 4:
	scanf("%d %d",&r,&c);
	island_reversal(r-1,c-1);
	break;
      default:
	break;
      }
    }

    for(int y=0;y<matrix_size;y++){
      for(int x=0;x<matrix_size;x++){
	printf("%s%d",x == 0 ? "" : " ",matrix[y][x]);
      }
      printf("\n");
    }
  }
}
