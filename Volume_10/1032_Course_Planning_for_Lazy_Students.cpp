#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdio>
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
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
 
static const double EPS = 1e-8;

static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};

int prior[21];
int credit[21];
int dp[1<<20];
int total_subjects;
int credit_requirement;

class State {
public:
  int S;
  int sum;
  bool operator<(const State& s) const {
    return __builtin_popcount(S) < __builtin_popcount(s.S);
  }
  bool operator>(const State& s) const {
    return __builtin_popcount(S) > __builtin_popcount(s.S);
  }
  State(int S,int sum) : S(S),sum(sum) {}
};

int bfs(){
  priority_queue<State,vector<State>,greater<State> > que;
  que.push(State(0,0));
  while(!que.empty()){
    State s = que.top();
    que.pop();
    for(int i = 0; i < total_subjects; i++){
      if(s.S & (1<<i)) continue;
      if((prior[i] | s.S) == s.S){
	if(dp[s.S | (1<<i)] != -1) continue;
	dp[s.S | (1<<i)] = s.sum + credit[i];

	if(s.sum + credit[i] >= credit_requirement) {
	  return __builtin_popcount(s.S) + 1;
	}
	que.push(State(s.S | (1<<i),s.sum + credit[i]));
      }
    }
  }
  return 0;
}

int main(){
  while(~scanf("%d %d",&total_subjects,&credit_requirement)){
    if(total_subjects == 0 && credit_requirement == 0) break;
    memset(dp,-1,sizeof(dp));
    memset(prior,0,sizeof(prior));

    for(int subject_i = 0; subject_i < total_subjects; subject_i++){
      int prior_subject_num;
      scanf("%d %d",&credit[subject_i],&prior_subject_num);
      for(int subject_j = 0; subject_j < prior_subject_num; subject_j++){
	int subject_code;
	scanf("%d",&subject_code);
	prior[subject_i] |= (1<<subject_code);
      }
    }
    
    printf("%d\n",bfs());
  }
}
