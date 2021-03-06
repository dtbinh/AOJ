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
  
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};

class State {
public:
  vector<char> nums;
  int cost;
  bool operator <(const State& s) const {
    return cost < s.cost;
  }
  bool operator >(const State& s) const {
    return cost > s.cost;
  }
  State(const vector<char>& n,int c) {
    nums = n;
    cost = c;
  }
};

int bfs(const vector<char>& init,
	map<vector<char>,int>& dp,int limit = 4){
  priority_queue<State,vector<State>,greater<State> > que;
  que.push(State(init,0));
  dp[init] = 0;

  while(!que.empty()){
    State s = que.top();
    que.pop();
    if(s.cost >= limit) continue;
    for(int lhs = 0; lhs < s.nums.size(); lhs++){
      for(int rhs = lhs + 1; rhs <= s.nums.size(); rhs++){
	reverse(s.nums.begin() + lhs,s.nums.begin() + rhs);
	
	if(dp.find(s.nums) != dp.end()){
	  reverse(s.nums.begin() + lhs,s.nums.begin() + rhs);
	  continue;
	}

	dp[s.nums] = s.cost + 1;
	que.push(State(s.nums,s.cost+ 1));
	reverse(s.nums.begin() + lhs,s.nums.begin() + rhs);
      }
    }
  }
}

int main(){
  int N;
  while(~scanf("%d",&N)){
    vector<char> nums;
    for(int i=0; i < N; i++){
      int num;
      scanf("%d",&num);
      nums.push_back(num);
    }
    map<vector<char>,int> start;
    bfs(nums,start);

    map<vector<char>,int> goal;
    sort(nums.begin(),nums.end());
    bfs(nums,goal,4);
    
    int res = 9;
    for(map<vector<char>,int>::iterator it = start.begin();
	it != start.end();
	it++){
      if(goal.find(it->first) != goal.end()){
	res = min(it->second + goal[it->first],res);
      }
    }
    printf("%d\n",res);
  }
}
