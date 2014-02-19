#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f

#include <iostream>
#include <cstdio>
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
typedef pair <int,P> PP;
  
static const double EPS = 1e-8;
  
int tx[] = {+0,+1,+0,-1};
int ty[] = {-1,+0,+1,+0};

void print_stage(deque<int> deq[101],int W,int H){
  for(int y=H-1;y>=0;y--){
    for(int x=0;x<W;x++){
      if(deq[x][y] == -1){
	printf(" ");
      }
      else{
	printf("%s",deq[x][y] ? "1" : "0");
      }
    }
    printf("\n");
  }
  printf("\n");
}

int solve(deque<int> deq[101],int W,int H){
  
  int res = 0;
  for(int y=H-1;y>=0;y--){
    for(int round = 0; round < W; round++){
      int next_x = -1;
      for(int x=0;x<W;x++){
	if(deq[x][y+1] != -1) continue;

	int count = 0;
	if(x-1 < 0) count++;
	if(x+1 >= W) count++;
	if(x-1 >= 0 && (deq[x-1][y] == -1)) count++;
	if(x+1 < W && (deq[x+1][y] == -1)) count++;
	
	if(count >= 1 && deq[x][y] == 1){
	  next_x = x;
	  break;
	}
	if(count >= 1 && deq[x][y] == 0 && next_x == -1){
	  next_x = x;
	}
      }
      if(next_x == -1) break;

      for(int i=0;i<4;i++){
	if(i == 2) continue;

	int dx = next_x + tx[i];
	int dy = y + ty[i];
	if(dx < 0 || dx >= W || dy < 0 || dy >= H) continue;
	if(deq[dx][dy] == -1) continue;
	    
	deq[dx][dy] = (deq[dx][dy] == 0 ? 1 : 0);
      }

      if(deq[next_x][y] == 1) res++;
      deq[next_x][y] = -1;

    }
  }
  return res;
}

int main(){
  int H,W;
  while(~scanf("%d %d",&H,&W)){
    deque<int> deq[101];
    for(int y=0;y<=H;y++){
      for(int x=0;x<W;x++){
	deq[x][y] = -1;
      }
    }

    for(int y=H-1;y >= 0;y--){
      for(int x=0;x<W;x++){
	int is_sweet;
	scanf("%d",&is_sweet);
	deq[x][y] = is_sweet;
      }
    }

    printf("%d\n",solve(deq,W,H));
  }
}
