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
 
static const int tx[] = {-1,+0,-1};
static const int ty[] = {-1,-1,+0};
 
static const double EPS = 1e-10;

int dp[2001][2001];
int prev[2001][2001];

int main(){
  string str;
  memset(dp,0,sizeof(dp));
  memset(prev,-1,sizeof(prev));
  while(cin >> str){
    string r_str = str;
    reverse(r_str.begin(),r_str.end());
    for(int y = 0; y < str.size(); y++){
      for(int x = 0; x < r_str.size(); x++){
	if(str[y] == r_str[x]){
	  dp[y+1][x+1] = dp[y][x] + 1;
	  prev[y+1][x+1] = 0;
	}
	else if(dp[y][x+1] < dp[y+1][x]){
	  dp[y+1][x+1] = dp[y+1][x];
	  prev[y+1][x+1] = 2;
	}
	else {
	  dp[y+1][x+1] = dp[y][x+1];
	  prev[y+1][x+1] = 1;
	}
      }
    }

    string res = "";
    queue<P> que;
    que.push(P(str.size(),r_str.size()));
    while(!que.empty()){
      P p = que.front();
      que.pop();
      int y = p.first;
      int x = p.second;
      int dir = prev[y][x];
      if(dir == 0){
	res.push_back(str[y-1]);
      }
      int dx = x + tx[dir];
      int dy = y + ty[dir];
      if(prev[dy][dx] == -1) break;
      P next(dy,dx);
      que.push(next);
    }
    cout << res << endl;
  }
}
