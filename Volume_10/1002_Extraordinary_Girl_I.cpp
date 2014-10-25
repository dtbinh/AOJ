#define _USE_MATH_DEFINES
#define INF 100000000
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
#include <cstdio>

using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P> PP;
 
static const double EPS = 1e-8;
 
const int tx[] = {+0,+0};
const int ty[] = {-1,+1};

int nodes[1001][1001];
int dp[1<<2][100001][3]; //dp[book_state][x][y];

int compute_book_state(int x){
  int res = 0;
  for(int y = 1,i=0; y < 5; y+=2,i++){
    if(nodes[y][x] == 1){
      res |= (1<<i);
    }
  }
  return res;
}

int dfs(int sx,int sy,int cost){
  if(sx > 100000) return 0;
  bool has_book = false;
  for(int y = 0; y < 5; y++){
    if(nodes[y][sx] == 1){
      has_book = true;
    }
  }
  
  if(!has_book){
    for(int y = 0; y < 5; y++){
      if(y % 2 != 0) continue;
      int book_state = compute_book_state(sx+1);
      if(dp[book_state][sx+1][y] > cost + abs(y - sy) + 2){
	dp[book_state][sx+1][y] = cost + abs(y - sy) + 2;
	dfs(sx+1,y,cost + abs(y - sy) + 2);
      }
    }
  }

  else{
    
    for(int i=0;i<2;i++){
      int dy = sy + ty[i];
      if(dy < 0 || dy >= 5) continue;

      if(nodes[dy][sx] == 1){
	nodes[dy][sx] = 0;
	int book_state = compute_book_state(sx);
	if(dp[book_state][sx][dy] <= cost + abs(sy - dy)){
	  nodes[dy][sx] = 1;
	  continue;
	}
	
	dp[book_state][sx][dy] = cost + abs(sy - dy);
	dfs(sx,dy,cost + abs(sy - dy));
	nodes[dy][sx] = 1;
      }

      else{
	int book_state = compute_book_state(sx);
	if(dp[book_state][sx][dy] > cost + abs(sy - dy)){
	  dp[book_state][sx][dy] = cost + abs(sy - dy);
	  dfs(sx,dy,cost + abs(sy - dy));
	}
      }
    }
  }
}

int main(){
  int num_of_test_cases;
  while(~scanf("%d",&num_of_test_cases)){
    for(int case_i = 0; case_i < num_of_test_cases; case_i++){
      int shelves_per_line;
      scanf("%d",&shelves_per_line);
      string shelves;
      cin >> shelves;

      memset(nodes,0,sizeof(nodes));
      for(int y = 1,i=0; y <= 4; y+=2,i++){
	for(int x = 0; x <= shelves_per_line; x++){
	  if(x == 0){
	    if(shelves[(i * shelves_per_line * 2)] == 'Y'){
	      nodes[y][x] = 1;
	    }
	  }
	  if(x == shelves_per_line){
	    if(shelves[(i * shelves_per_line * 2) + (shelves_per_line * 2 - 1)] == 'Y'){
	      nodes[y][x] = 1;
	    }
	  }
	  else{
	    if(shelves[(i * shelves_per_line * 2) + 2 * x - 1] == 'Y' 
	       || shelves[(i * shelves_per_line * 2) + 2 * x] == 'Y'){
	      nodes[y][x] = 1;
	    }
	  }
	}
      }

      memset(dp,0x3f,sizeof(dp));
      for(int y = 0; y < 5; y++){
	for(int x = 0; x < 10; x++){
	  printf("%d ",nodes[y][x]);
	}
	printf("\n");
      }
      printf("\n");
      int book_state = compute_book_state(0);
      dp[book_state][0][0] = 0;
      dfs(0,0,0);

      cout << dp[0][shelves_per_line][0] << endl;
    }
  }
}
