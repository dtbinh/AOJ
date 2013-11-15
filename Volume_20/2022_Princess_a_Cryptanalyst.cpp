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

	  string catstr = dp[from][S];
	  for(int smoothing = min(catstr.size(),constituents[to].size());
	      smoothing >= 0 ;
	      smoothing--){
	    string front = catstr.substr(catstr.size()-smoothing,smoothing);
	    string rear = constituents[to].substr(0,smoothing);

	    if(front == rear){
	      catstr += constituents[to].substr(smoothing,constituents[to].size()-smoothing);
	      break;
	    }
	  }
	  if(dp[to][S | (1<<to)].size() > catstr.size()){
	    dp[to][S | (1<<to)] = catstr;
	  }
	  else if(dp[to][S | (1<<to)].size() == catstr.size() 
		  && dp[to][S | (1<<to)] > catstr){
	    dp[to][S | (1<<to)] = catstr;
	  }
	}
      }
    }

    string res = dp[0][(1<<n)-1];

    for(int i=0;i<n;i++){
      if(res.size() > dp[i][(1<<n)-1].size()){
	res = dp[i][(1<<n)-1];
      }
      else if(dp[i][(1<<n)-1].size() == res.size()
	      && dp[i][(1<<n)-1] > res){
	res = dp[i][(1<<n)-1];
      }
    }
    cout << res << endl;
  }
}
