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

      for(int start_pos = 0;start_pos<old_board.size();start_pos++){
	for(int distance = 1;distance<=old_board.size();distance++){
	  string new_board="";
	  new_board.push_back(old_board[start_pos]);
	  int next_pos = start_pos+distance;
	  
	  while(next_pos < old_board.size()){
	    new_board.push_back(old_board[next_pos]);
	    next_pos += distance;
	    if(target_board == new_board){
	      res++;
	      goto found;
	    }
	  }
	}
      }
    found:;
    }
    printf("%d\n",res);
  }
}
