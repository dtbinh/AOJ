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
#include <complex>
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;
 

static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-10;

int total_players;
int total_messages;
int dp[21][21];
bool visited[21];

bool check(vector<int>& logs){
  for(int i=0;i<logs.size();i++){
    for(int j=0;j<i;j++){
      //logs[i] entered the room earlier than logs[j]
      if(dp[logs[j]][logs[i]] == -1){
	return false;
      }
    }
  }
  return true;
}

void dfs(int player,vector<int>& logs){
  if(!check(logs)) return;
  
  if(logs.size() == total_players){
    for(int i=0;i<logs.size();i++){
      printf("%d\n",logs[i]);
    }
    exit(0);
  }

  for(int next = 1; next <= total_players; next++){
    if(visited[next]) continue;
    visited[next] = true;
    logs.push_back(next);
    dfs(next,logs);
    logs.pop_back();
    visited[next] = false;
  }
}

int main(){
  while(~scanf("%d %d",&total_players,&total_messages)){

    memset(dp,0,sizeof(dp));

    for(int message_idx = 0; message_idx < total_messages; message_idx++){
      int x,y;
      //x entered the room earlier than y
      scanf("%d %d",&x,&y);
      if(dp[x][y] == 0){
	dp[x][y] = 1;
	dp[y][x] = -1;
      }
    }

    bool is_top[21];
    memset(is_top,true,sizeof(is_top));
    for(int i=1;i<=total_players;i++){
      for(int j=1;j<=total_players;j++){
	if(dp[i][j] == -1) is_top[i] = false;
      }
    }

    int start = 1;
    for(int i=1;i<=total_players;i++){
      if(is_top[i]){
	start = i;
	break;
      }
    }
    memset(visited,false,sizeof(visited));
    vector<int> logs;
    visited[start] = true;
    logs.push_back(start);
    dfs(start,logs);
  }
}
