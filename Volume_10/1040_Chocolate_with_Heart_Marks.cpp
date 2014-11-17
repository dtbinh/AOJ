#define _USE_MATH_DEFINES
#define INF 0x1f1f1f1f
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

int block[12][12];
int idx2heart[12];
int dp[145][145];

class MinimumSteinerTree {
public:
  int solver(int total_chocolates,int H,int W){
    if(total_chocolates <= 1) return 0;

    for(int k = 0; k < H * W; k++){
      for(int i = 0; i < H * W; i++){
	for(int j = 0; j < H * W; j++){
	  dp[i][j] = min(dp[i][j],dp[i][k] + dp[k][j]);
	}
      }
    }

    int steiner_tree[1<<total_chocolates][H * W];
    memset(steiner_tree,0x1f,sizeof(steiner_tree));
    for(int i = 0; i < total_chocolates; i++){
      for(int to = 0; to < H * W; to++){
	steiner_tree[(1 << i)][to] = dp[idx2heart[i]][to];
      }
    }

    for(int S = 1; S < (1<<total_chocolates); S++){
      for(int from = 0; from < H * W; from++){
	
	int tmp = INF;
	for(int E = 0; E < S; E++){
	  for(int to = 0; to < H * W; to++){
	    if((E | S) != S) continue;
	    tmp 
	      = min(tmp,
		    dp[from][to]
		    + steiner_tree[E][to]
		    + steiner_tree[S - E][to]);
	  }
	}
	steiner_tree[S][from] = min(steiner_tree[S][from],tmp);
      }
    }

    int res = INF;
    for(int S = 0; S < (1 << total_chocolates); S++){
      for(int to = 0; to < H * W; to++){
	res = min(res,
		  steiner_tree[S][to]
		  + steiner_tree[((1<<total_chocolates) - 1) - S][to]);
      }
    }
    return res;
  }
};

int main(){
  int H,W;
  while(~scanf("%d %d",&H,&W)){
    if(H == 0 && W == 0) break;

    int idx = 0;
    for(int y = 0; y < H; y++){
      for(int x = 0; x < W; x++){
	scanf("%d",&block[y][x]);
	if(block[y][x] == 1){
	  idx2heart[idx] = y * W + x;
	  idx++;
	}
      }
    }
    int total_chocolates = idx;

    memset(dp,0x1f,sizeof(dp));
    for(int from = 0; from < H * W; from++){
      dp[from][from] = 0;
      for(int i = 0; i < 4; i++){
	int dx = from % W + tx[i];
	int dy = from / W + ty[i];
	if(dx < 0 || dx >= W || dy < 0 || dy >= H) continue;
	int to = dy * W + dx;
	dp[from][to] = dp[to][from] = 1;
      }
    }

    MinimumSteinerTree mst;
    printf("%d\n",H * W - (mst.solver(total_chocolates,H,W) + 1));
  }
}
