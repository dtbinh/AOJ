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
int gRes = INF;

void dfs(int col_num,int row_num,
	 int max_h,int pos,
	 int col[32],int row[32],int total){
  if(pos == col_num * row_num){
    gRes = min(gRes,total);
    return;
  }

  int x = pos % col_num;
  int y = pos / col_num;

  stage[y][x] = 0;
  dfs(col_num,row_num,max_h,pos+1,col,row,total+0);

  stage[y][x] = col[x];
  dfs(col_num,row_num,max_h,pos+1,col,row,total+col[x]);

  stage[y][x] = row[y];
  dfs(col_num,row_num,max_h,pos+1,col,row,total+row[y]);
}

int main(){
  int col_num,row_num;
  int col[32],row[32];
  
  while(~scanf("%d %d",&col_num,&row_num)){
    memset(stage,0,sizeof(stage));
    gRes = INF;
    memset(col,0,sizeof(col));
    memset(row,0,sizeof(row));

    int max_h = 0;
    for(int i=0;i<col_num;i++){
      scanf("%d",col+i);
      max_h = max(col[i],max_h);
    }
    for(int i=0;i<row_num;i++){
      scanf("%d",row+i);
      max_h = max(row[i],max_h);
    }
    
    dfs(col_num,row_num,max_h,0,col,row,0);
    printf("%d\n",gRes);
  }
}

