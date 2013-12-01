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
  
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};

int main(){
  int total_signboards;
  while(~scanf("%d",&total_signboards)){
    string target_board;
    cin >> target_board;

    int dp[102][102];
    memset(dp,0,sizeof(dp));

    int res = 0;
    for(int i=0;i<total_signboards;i++){
      string old_board;
      cin >> old_board;
      for(int y=0;y<old_board.size();y++){
	for(int x=0;x<target_board.size();x++){
	  dp[y+1][x+1] = max(dp[y][x] + (old_board[y] == target_board[x]),
			     max(dp[y+1][x],dp[y][x+1]));
	}
      }
      if(dp[old_board.size()][target_board.size()] == target_board.size()){
	res++;
      }
    }
    printf("%d\n",res);
  }
}
