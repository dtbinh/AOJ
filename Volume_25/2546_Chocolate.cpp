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
  
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};

void print_stage(deque<bool> deq[101],int W,int H){
  for(int y=H-1;y>=0;y--){
    for(int x=0;x<W;x++){
      if(deq[x].size()-1 < y){
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

int dfs(deque<bool> deq[101],int W,int H){
  
  int res = 0;
  for(int x=0;x<W;x++){
    int y = deq[x].size()-1;
    if(y < 0) continue;

    bool is_erased = false;
    deque<bool> next[101];
    int count = 0;
    for(int i=0;i<W;i++) next[i] = deq[i];
    if(x-1 < 0) count++;
    if(x+1 >= W) count++;
    if(x-1 >= 0 && (deq[x-1].size()-1) < y) count++;
    if(x+1 < W && (deq[x+1].size()-1) < y) count++;

    bool is_sweet = false;
    if(count >= 1 && next[x].size() > 0){
      if(deq[x][deq[x].size()-1]) is_sweet = true;
      next[x].pop_back();
      is_erased = true;
    }
    
    for(int i=1;i<4;i++){
      int dx = x + tx[i];
      int dy = y + ty[i];
      if(dx < 0 || dx >= W || dy < 0 || dy >= H) continue;
      if(dy <= deq[dx].size()-1){
	next[dx][dy] = !deq[dx][dy];
      }
    }
    res = max(res,(is_sweet ? 1 : 0) + (is_erased ? dfs(next,W,H) : 0));
  }
  return res;
}

int main(){
  int H,W;
  while(~scanf("%d %d",&H,&W)){
    deque<bool> deq[101];
    for(int y=0;y<H;y++){
      for(int x=0;x<W;x++){
	int is_sweet;
	scanf("%d",&is_sweet);
	deq[x].push_front((bool)is_sweet);
      }
    }

    printf("%d\n",dfs(deq,W,H));
  }
}
