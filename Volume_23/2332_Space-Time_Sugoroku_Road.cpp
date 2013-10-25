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
 
const static int tx[] = {0,1,1,1,0,-1,-1,-1};
const static int ty[] = {-1,-1,0,1,1,1,0,-1};
 
static const double EPS = 1e-10;

struct Player {
  int pos;
  int cost;
  
  Player(int _p,int _c) : pos(_p), cost(_c) {}
  bool operator <(const Player& p) const{
    return cost < p.cost;
  }
  bool operator >(const Player& p) const{
    return cost > p.cost;
  }
};

int stage[100000];
int dp[100000];

int main(){
  int N;
  
  while(~scanf("%d",&N)){
    memset(dp,0x3f,sizeof(dp));
    memset(stage,0,sizeof(stage));

    for(int i=0;i<N;i++){
      scanf("%d",stage+i);
    }

    priority_queue<Player,vector<Player>,greater<Player> > que;
    que.push(Player(0,0));
    while(!que.empty()){
      Player player = que.top(); 
      que.pop();
      for(int spots=1;spots<=6;spots++){
	int next = player.pos + spots;
	if(next >= N-1){
	  dp[N-1] = min(dp[N-1],player.cost+1);
	  continue;
	}

	while(stage[next] != 0){
	  next += stage[next];
	  if(stage[next] != 0 && dp[next] > player.cost + 1){
	    dp[next] = player.cost + 1;
	  }
	  else{
	    break;
	  }
	}

	if(dp[next] > player.cost + 1){
	  dp[next] = player.cost + 1;
	  que.push(Player(next,player.cost+1));
	}
      }
    }

    printf("%d\n",dp[N-1]);
  }
}
