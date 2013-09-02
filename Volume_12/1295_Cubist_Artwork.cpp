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
 
static const double EPS = 1e-8;

int stage[20][20];
bool visited[20][20][20];
int gRes = INF;

bool check(int col_num,int row_num,int col[32],int row[32]){
  for(int x=0;x<col_num;x++){
    int max_h = 0;
    for(int y=0;y<row_num;y++){
      max_h = max(stage[y][x],max_h);
    }
    if(max_h != col[x]) return false;
  }
  for(int y=0;y<row_num;y++){
    int max_h = 0;
    for(int x=0;x<col_num;x++){
      max_h = max(stage[y][x],max_h);
    }
    if(max_h != row[y]) return false;
  }
  return true;
}

void dfs(int col_num,int row_num,
	 int pos,
	 int col[32],int row[32],int total){
  if(pos == col_num * row_num){
    // printf("%d\n",total);
    if(check(col_num,row_num,col,row)){
      gRes = min(gRes,total);
      printf("%d\n",gRes);
    }
    return;
  }

  int x = pos % col_num;
  int y = pos / col_num;

  stage[y][x] = 0;
  dfs(col_num,row_num,pos+1,col,row,total);
  
  if(total + col[x] < gRes){
    stage[y][x] = col[x];
    dfs(col_num,row_num,pos+1,col,row,total+col[x]);
  }
  
  if(total + row[y] < gRes){
    stage[y][x] = row[y];
    dfs(col_num,row_num,pos+1,col,row,total+row[y]);
  }
}

int main(){
  int col_num,row_num;
  int col[32],row[32];
  
  while(~scanf("%d %d",&col_num,&row_num)){
    memset(stage,0,sizeof(stage));
    memset(visited,false,sizeof(visited));
    gRes = INF;
    memset(col,0,sizeof(col));
    memset(row,0,sizeof(row));

    for(int i=0;i<col_num;i++){
      scanf("%d",col+i);
    }
    for(int i=0;i<row_num;i++){
      scanf("%d",row+i);
    }
    
    dfs(col_num,row_num,0,col,row,0);
    printf("%d\n",gRes);
  }
}

