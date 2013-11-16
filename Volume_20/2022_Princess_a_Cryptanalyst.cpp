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
 
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

string cat_string (const string& lhs,const string& rhs){

  if(lhs.size() >= rhs.size()){
    for(int i=0;i<lhs.size();i++){
      if(lhs.size() < i+rhs.size()) break;
      string candidate = lhs.substr(i,rhs.size());
      
      if(candidate == rhs){
	return lhs;
      }
    }
  }

  for(int smoothing = min(lhs.size(),rhs.size());
      smoothing >= 0 ;
      smoothing--){
    string front = lhs.substr(lhs.size()-smoothing,smoothing);
    string rear = rhs.substr(0,smoothing);
    
    if(front == rear){
      return lhs + rhs.substr(smoothing,rhs.size()-smoothing);
    }
  }
  return lhs+rhs;
}

string compute_short_string(const string& lhs,const string& rhs){
  if(lhs.size() < rhs.size()) {
    return lhs;
  }
  else if(lhs.size() > rhs.size()) {
    return rhs;
  }
  else if(lhs.size() == rhs.size()) {
    return lhs < rhs ? lhs : rhs;
  }
}

int main(){
  int n;
  while(~scanf("%d",&n)){
    if(n==0) break;

    vector<int> order;
    for(int i=0;i<n;i++){
      order.push_back(i);
    }

    vector<string> constituents;
    for(int i=0;i<n;i++){
      string str;
      cin >> str;
      constituents.push_back(str);
    }

    string dp[n][1<<n];

    for(int S=0;S<=(1<<n)-1;S++){
      for(int i=0;i<n;i++){
	for(int j=0;j<=110;j++) dp[i][S].push_back('z');
      }
    }

    for(int i=0;i<n;i++) {
      dp[i][(1<<i)] = constituents[i];
    }

    for(int S=0;S<=(1<<n)-1;S++){
      for(int from=0;from < n; from++){
	if((S & (1<<from)) == 0) continue;	     
	for(int to=0;to < n; to++){
	  if(from == to) continue;
	  if(S & (1<<to)) continue;
	  dp[to][S | (1<<to)]
	    = compute_short_string(cat_string(dp[from][S],constituents[to]),dp[to][S | (1<<to)]);
	}
      }
    }

    string res = dp[0][(1<<n)-1];

    for(int i=0;i<n;i++){
      res = compute_short_string(res,dp[i][(1<<n) - 1]);
    }
    cout << res << endl;
  }
}

