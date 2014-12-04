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

typedef complex<double> Point;
const static double EPS = 1e-12;

class State {
public:
  int bits;
  int cost;
  State(int bits,int cost) :
    bits(bits), cost(cost) {}
  bool operator<(const State& s) const {
    return cost < s.cost;
  }
  bool operator>(const State& s) const {
    return cost > s.cost;
  }
};

int dp[1<<15];

int main(){
  int bit_length;
  int run_length;
  while(~scanf("%d %d",&bit_length,&run_length)){
    int init = 0;
    for(int i = 0; i < bit_length; i++){
      int bit;
      scanf("%d",&bit);
      if(bit > 0) init |= (1<<i);
    }
    
    vector<int> width;
    for(int i = 0; i < run_length; i++){
      int run;
      scanf("%d",&run);
      width.push_back(run);
    }

    priority_queue<State,vector<State>,greater<State> > que;
    que.push(State(init,0));
    memset(dp,0x3f,sizeof(dp));
    dp[init] = 0;

    while(!que.empty()){
      State s = que.top();
      que.pop();
      for(int i = 0; i + 1 < bit_length; i++){
	int j = i + 1;
	int next = s.bits;
	if((s.bits & (1<<i)) && !(s.bits & (1<<j))){
	  next &= ~(1<<i);
	  next |= (1<<j);
	  if(dp[next] > s.cost + 1){
	    dp[next] = s.cost + 1;
	    que.push(State(next,s.cost + 1));
	  }
	}
	else if(!(s.bits & (1<<i)) && (s.bits & (1<<j))){
	  next &= ~(1<<j);
	  next |= (1<<i);
	  if(dp[next] > s.cost + 1){
	    dp[next] = s.cost + 1;
	    que.push(State(next,s.cost + 1));
	  }
	}
      }
    }
    
    int res = INF;
    for(int S = 0; S < (1<<bit_length); S++){
      int offset = 0;
      bool isok = true;
      for(int i = 0; i < width.size(); i++){
	if(offset > 0 && ((S >> offset) & 1) == ((S >> (offset-1)) & 1)){
	  isok = false;
	  break;
	}
	for(int j = offset; j + 1 < offset + width[i]; j++){
	  if(((S >> j) & 1) != ((S >> (j+1)) & 1)){
	    isok = false;
	    break;
	  }
	}
	offset += width[i];
	if(!isok) break;
      }

      if(isok){
	res = min(dp[S],res);
      }
    }

    printf("%d\n",res);
  }
}
