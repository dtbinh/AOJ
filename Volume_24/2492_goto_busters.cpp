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

class State{
public:
  int cost;
  int pos;
  State(int _c,int _p): cost(_c), pos(_p){}
  bool operator<(const State& s) const{
    return cost < s.cost;
  }
  bool operator>(const State& s) const{
    return cost > s.cost;
  }
};

int main(){
  int n;
  while(~scanf("%d",&n)){
    bool nodes[101][101];
    memset(nodes,false,sizeof(nodes));
    map<string,int> goto_dst;
    vector<string> code;

    for(int i=0;i<n;i++){
      string str;
      cin >> str;
      if(str == "goto"){
	cin >> str;
	str = str.substr(0,str.size()-1);
	code.push_back(str);
      }
      else{
	str = str.substr(0,str.size()-1);
	goto_dst[str] = i;
	code.push_back("goto");
      }
    }
    
    for(int i=0;i<code.size();i++){
      if(goto_dst.find(code[i]) != goto_dst.end()){
	nodes[i][goto_dst[code[i]]] = true;
      }
    }

    priority_queue<State,vector<State>,greater<State> > que;
    que.push(State(0,0));

    int dp[101];
    memset(dp,0x3f,sizeof(dp));
    dp[0] = 0;
    while(!que.empty()){
      State s = que.top();
      int cost = s.cost;
      int from = s.pos;

      que.pop();
      bool is_goto = false;
      for(int to=0;to<=n;to++){
	if(nodes[from][to]){
	  if(dp[to] > cost){
	    que.push(State(cost,to));
	    dp[to] = cost;
	  }
	  if(dp[from+1] > cost+1){
	    que.push(State(cost+1,from+1));
	    dp[from+1] = cost+1;
	  }
	  is_goto = true;
	  break;
	}
      }

      if(!is_goto){
	if(dp[from+1] > cost){
	  que.push(State(cost,from+1));
	  dp[from+1] = cost;
	}
      }
    }

    printf("%d\n",dp[n]);
  }
}
