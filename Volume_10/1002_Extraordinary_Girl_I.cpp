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
 
const int tx[] = {+0,+0,+1};
const int ty[] = {-1,+1,+0};

int nodes[5][20001];
int dp[1<<2][20001][5]; //dp[book_state][x][y];

int compute_book_state(int x){
  int res = 0;
  for(int y = 1,i=0; y < 5; y+=2,i++){
    if(nodes[y][x] == 1){
      res |= (1<<i);
    }
  }
  return res;
}

int shelves_per_line;

int dfs(int sx,int sy,int cost){
  for(int i=0;i<3;i++){
    int dx = sx + tx[i];
    int dy = sy + ty[i];
    if(dy < 0 || dy >= 5 || dx > shelves_per_line * 2) continue;

    if(i < 2){
      if(nodes[dy][dx] == 1){
	nodes[dy][dx] = 0;
	int book_state = compute_book_state(dx);
	if(dp[book_state][dx][dy] <= cost + abs(sy - dy)){
	  nodes[dy][dx] = 1;
	  continue;
	}
	
	dp[book_state][dx][dy] = cost + abs(sy - dy);
	dfs(dx,dy,cost + abs(sy - dy));
	nodes[dy][dx] = 1;
      }
      else{
	int book_state = compute_book_state(dx);
	if(dp[book_state][dx][dy] > cost + abs(sy - dy)){
	  dp[book_state][dx][dy] = cost + abs(sy - dy);
	  dfs(dx,dy,cost + abs(sy - dy));
	}
      }
    }

    else{
      int current_book_state = compute_book_state(sx);
      if(sy % 2 == 1) continue;
      if(current_book_state != 0) continue;

      int next_book_state = compute_book_state(dx);
      if(dp[next_book_state][dx][dy] > cost + 2){
	dp[next_book_state][dx][dy] = cost + 2;
	dfs(dx,dy,cost + 2);
      }
    }
  }
}

int main(){
  int num_of_test_cases;
  while(~scanf("%d",&num_of_test_cases)){
    for(int case_i = 0; case_i < num_of_test_cases; case_i++){
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
      int book_state = compute_book_state(0);
      dp[book_state][0][0] = 0;
      dfs(0,0,0);

      cout << dp[0][shelves_per_line][0] / 2<< endl;
    }
  }
}
