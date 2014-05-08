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
static const ll MAX = 1e15;
  
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};

class State{
public:
  int x;
  int y;
  int cost;
  int scrolling;
  State(int _x,int _y,int _c,int _s) : x(_x),y(_y),cost(_c),scrolling(_s) {}
  bool operator<(const State& s) const {
    return cost < s.cost;
  }
  bool operator>(const State& s) const {
    return cost > s.cost;
  }
};

int main(){
  int W,H;
  while(~scanf("%d %d",&W,&H)){
    char stage[101][101];
    int times[101][101];
    int scrolling2idx[101][101];

    vector<P> holes;

    int sx,sy;
    int gx,gy;
    int scrolling_size = 0;
    for(int y=0; y<H;y++){
      char buf[128];
      scanf("%s",buf);
      for(int x=0; x<W;x++){
	stage[y][x] = buf[x];
	if(buf[x] == '#'){
	  holes.push_back(P(x,y));
	}
	else if(buf[x] == 'M'){
	  scrolling2idx[y][x] = scrolling_size++;
	}
	else if(buf[x] == 'S'){
	  sy = y;
	  sx = x;
	}
	else if(buf[x] == 'G'){
	  gy = y;
	  gx = x;
	}
      }
    }
    for(int y=0; y<H;y++){
      for(int x=0; x<W;x++){
	int dist = INF;
	for(int i=0;i<holes.size();i++){
	  dist = min(dist,max(abs(y - holes[i].second),abs(x - holes[i].first)));
	}
	times[y][x] = max(1,4-dist);
      }
    }

    priority_queue<State,vector<State>,greater<State> > que;
    que.push(State(sx,sy,0,0));

    int dp[101][101][1<<5];
    memset(dp,0x3f,sizeof(dp));

    while(!que.empty()){
      State s = que.top();
      que.pop();
      dp[s.x][s.y][s.scrolling] = s.cost;

      for(int i=0;i<4;i++){
	int dx = s.x + tx[i];
	int dy = s.y + ty[i];
	if(dx < 0 || dy < 0 || dx >= W || dy >=H ) continue;
	if(stage[dy][dx] == '#') continue;

	int next_scrolling = s.scrolling;
	if(stage[dy][dx] == 'M'){
	   next_scrolling |= (1 << scrolling2idx[dy][dx]);
	}
	if(dp[dx][dy][next_scrolling] <= s.cost + times[s.y][s.x]) continue;
	dp[dx][dy][next_scrolling] = s.cost + times[s.y][s.x];
	que.push(State(dx,dy,s.cost + times[s.y][s.x],next_scrolling));
      }
    }
    printf("%d\n",dp[gx][gy][(1<<scrolling_size)-1]);
  }
}
