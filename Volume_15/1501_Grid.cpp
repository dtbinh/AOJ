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

int dp[1001][1001];

int ComputeDistance(int x1,int x2,int w){
  // ..x1....x2.. dist = min(x2-x1,(col-x2)+x1);
  // ..x2....x1.. dist = min(x1-x2,(col-x1)+x2);
  return x1 < x2 ? min(x2-x1,(w-x2)+x1) : min(x1-x2,(w-x1)+x2);
}

int ComputeCandidateNum(int x1,int x2,int w){
  if(x1 < x2){
    if(x2-x1 != (w-x2)+x1){
      return 1;
    }
    else{
      return 2;
    }
  }
  else{
    if(x1-x2 != (w-x1)+x2){
      return 1;
    }
    else{
      return 2;
    }
  }
}

int main(){
  int row,col;
  int x1,y1,x2,y2;

  while(~scanf("%d %d %d %d %d %d",&row,&col,&x1,&y1,&x2,&y2)){
    memset(dp,0,sizeof(dp));
    int x_dist=ComputeDistance(x1,x2,row);
    int x_candidate_num = ComputeCandidateNum(x1,x2,row);
    int y_dist=ComputeDistance(y1,y2,col);
    int y_candidate_num = ComputeCandidateNum(y1,y2,col);

    for(int x=0;x<=x_dist;x++) dp[0][x] = 1;
    for(int y=0;y<=y_dist;y++) dp[y][0] = 1;

    for(int y=0;y<y_dist;y++){
      for(int x=0;x<x_dist;x++){
	dp[y+1][x+1] 
	  = max((dp[y][x+1] + dp[y+1][x]) % 100000007,dp[y+1][x+1]);
      }
    }

    printf("%d\n",
	   dp[y_dist][x_dist]*x_candidate_num*y_candidate_num % 100000007);
  }
}
