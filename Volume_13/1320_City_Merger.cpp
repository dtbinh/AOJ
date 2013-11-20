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
  return (lhs.size() < rhs.size()) ? lhs : rhs;
}

int main(){
  int n;
  while(~scanf("%d",&n)){
    if(n==0) break;

    vector<int> order;
    for(int i=0;i<n;i++){
      order.push_back(i);
    }

    vector<string> tmp_constituents;

    for(int i=0;i<n;i++){
      string str;
      cin >> str;
      tmp_constituents.push_back(str);
    }
    
    sort(tmp_constituents.begin(),tmp_constituents.end());

    bool can_use[n];
    memset(can_use,true,sizeof(can_use));

    for(int i=0;i<n;i++){
      for(int j=i+1;j<n;j++){
	if(tmp_constituents[i].size() <= tmp_constituents[j].size()){
	  for(int idx=0;idx<tmp_constituents[j].size();idx++){
	    if(tmp_constituents[j].size() < idx+tmp_constituents[i].size()) break;
	    string candidate = tmp_constituents[j].substr(idx,tmp_constituents[i].size());
      
	    if(candidate == tmp_constituents[i]){
	      can_use[i] = false;
	    }
	  }
	}
      }
    }

    vector<string> constituents;
    for(int i=0;i<tmp_constituents.size();i++){
      if(can_use[i]) constituents.push_back(tmp_constituents[i]);
    }

    n = constituents.size();

    string dp[n][1<<n];

    for(int i=0;i<n;i++) {
      dp[i][(1<<i)] = constituents[i];
    }

    for(int S=0;S<=(1<<n)-1;S++){
      for(int from=0;from < n; from++){
	if((S & (1<<from)) == 0) continue;	     
	for(int to=0;to < n; to++){
	  if(from == to) continue;
	  if(S & (1<<to)) continue;
	  if(dp[to][S | (1<<to)] == ""){
	    dp[to][S | (1<<to)]
	      =	cat_string(dp[from][S],constituents[to]);
	  }
	  else{
	    dp[to][S | (1<<to)]
	      = compute_short_string(cat_string(dp[from][S],constituents[to]),dp[to][S | (1<<to)]);
	  }
	}
      }
    }

    string res = dp[0][(1<<n)-1];

    for(int i=0;i<n;i++){
      res = compute_short_string(res,dp[i][(1<<n) - 1]);
    }
    cout << res.size() << endl;
  }
}

