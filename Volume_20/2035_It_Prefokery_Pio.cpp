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

int dp[2001][2001];
P prev[2001][2001];

int main(){
  string str;
  memset(dp,0,sizeof(dp));
  while(cin >> str){
    string r_str = str;
    reverse(r_str.begin(),r_str.end());
    for(int i = 0; i < str.size(); i++){
      for(int j = 0; j< r_str.size(); j++){
	if(str[i] == r_str[j]){
	  dp[i+1][j+1] = dp[i][j] + 1;
	  prev[i+1][j+1] = P(i,j);
	}
	else if(dp[i][j+1] < dp[i+1][j]){
	  dp[i+1][j+1] = dp[i+1][j];
	  prev[i+1][j+1] = P(i+1,j);
	}
	else {
	  dp[i+1][j+1] = dp[i][j+1];
	  prev[i+1][j+1] = P(i,j+1);
	}
      }
    }

    string res = "";
    queue<P> que;
    que.push(P(str.size(),r_str.size()));
    while(!que.empty()){
      P p = que.front();
      que.pop();
      int i = p.first;
      int j = p.second;
      P next = prev[i][j];
      if(str[i] == r_str[j]){
	res.push_back(str[i]);
      }
      if(i == 0 || j == 0) break;
      que.push(next);
    }
    cout << res << endl;
  }
}
