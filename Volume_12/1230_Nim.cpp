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

int dp[1<<14][21];

int dfs(int total_players,int upto[21],
	int current_stones,int player_idx){
  if(dp[current_stones][player_idx] != -1){
    return dp[current_stones][player_idx];
  }
  if(current_stones == 0){
    return 1;
  }

  int res = 0;

  for(int use = 1; 
      use <= upto[player_idx] 
	&& current_stones - use >= 0; 
      use++){
    if(dfs(total_players,upto,
	   current_stones - use,
	   (player_idx + 1) % total_players) == 0){
      res = 1;
      break;
    }
  }
  return (dp[current_stones][player_idx] = res);
}

int main(){
  int total_players;
  while(~scanf("%d",&total_players)){
    if(total_players == 0) break;

    int initial_stones;
    scanf("%d",&initial_stones);

    int upto[21];
    memset(upto,0,sizeof(upto));
    for(int player_idx=0;player_idx < total_players * 2;player_idx++){
      scanf("%d",upto + player_idx);
    }

    memset(dp,-1,sizeof(dp));
    printf("%d\n",dfs(total_players * 2,upto,initial_stones,0));
  }
}
