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

int block[12][12];
bool dp[1<<6][12][12][12*12 + 1];
int heart2idx[12][12];
bool used[12][12];
int H,W;
int idx;

void dfs(int hearts,int sx,int sy,int count){
  for(int i = 0; i < 4; i++){
    int dx = sx + tx[i];
    int dy = sy + ty[i];
    if(dx < 0 || dy < 0 || dx >= W || dy >= H) continue;

    int next_hearts = hearts;
    if(block[dy][dx] == 1){
      next_hearts |= (1<<heart2idx[dy][dx]);
    }
    int next_count = count;
    if(!used[dy][dx]) next_count++;
    if(dp[next_hearts][dy][dx][next_count]) continue;
    cout << next_count << endl;
    used[dy][dx] = true;
    dp[next_hearts][dy][dx][next_count] = true;
    if(next_count == 0){
      cout << "ha" << endl;
    }
    dfs(next_hearts,dx,dy,next_count);
    used[dy][dx] = false;
  }
}

void fill_dp(){
  for(int S = 0; S < (1<<6); S++){
    for(int y = 0; y < H; y++){
      for(int x = 0; x < W; x++){
	for(int count = 0; count <= W * H; count++){
	  dp[S][y][x][count] = false;
	}
      }
    }
  }
}

int main(){
  while(~scanf("%d %d",&H,&W)){
    if(H == 0 && W == 0) break;
    vector<P> start;

    idx = 0;
    memset(heart2idx,0,sizeof(heart2idx));
    for(int y = 0; y < H; y++){
      for(int x = 0; x < W; x++){
	scanf("%d",&block[y][x]);
	if(block[y][x] == 1){
	  start.push_back(P(x,y));
	  heart2idx[y][x] = idx++;
	}
      }
    }

    int res = 0;
    for(int i = 0; i < start.size(); i++){
      
      fill_dp();
      memset(used,false,sizeof(used));
      used[start[i].second][start[i].first] = true;
      dp[1<<i][start[i].second][start[i].first][1] = true;

      dfs(0,start[i].first,start[i].second,1);

      int S = ((1<<idx) - 1);
      for(int y = 0; y < H; y++){
	for(int x = 0; x < W; x++){
	  for(int count = 0; count <= H*W; count++){
	    if(dp[S][y][x][count]){
	      if(count == 0){
		cout << count << endl;
	      }
	      res = max(res,H * W - count);
	    }
	  }
	}
      }
    }

    printf("%d\n",res);
  }
}
