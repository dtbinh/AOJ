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
 
int tx[] = {1,0};
int ty[] = {0,1};
 
static const double EPS = 1e-8;

class State{
public:
  int mX;
  int mY;
  int mCost;
  State(int x,int y,int cost) : mX(x), mY(y), mCost(cost){}

  bool operator <(const State& s) const{
    return mCost < s.mCost;
  }

  bool operator >(const State& s) const{
    return mCost > s.mCost;
  }
};

int main(){
  int H,W;
  while(~scanf("%d %d",&H,&W)){
    char stage[50][50];
    for(int y=0;y<H;y++){
      char buf[51];
      scanf("%s",buf);
      for(int x=0;x<W;x++){
	stage[y][x] = buf[x];
      }
    }

    int cost_table[50][50];
    memset(cost_table,0x3f,sizeof(cost_table));
    priority_queue<State,vector<State>,greater<State> > que;
    cost_table[0][0] = stage[0][0]-'0';

    que.push(State(0,0,stage[0][0]-'0'));
    while(!que.empty()){
      State s = que.top();
      que.pop();
      for(int i=0;i<2;i++){
	int dx = s.mX + tx[i];
	int dy = s.mY + ty[i];
	if(dx < 0 || dx >= W 
	   || dy < 0 || dy >= H) continue;
	   
	   if(cost_table[dy][dx] <= s.mCost + stage[dy][dx]-'0') continue;
	   cost_table[dy][dx] = s.mCost + stage[dy][dx]-'0';
	   que.push(State(dx,dy,s.mCost + stage[dy][dx]-'0'));
	   }
      }

      printf("%d\n",cost_table[H-1][W-1]);
  }
}
