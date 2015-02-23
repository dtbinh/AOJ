#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
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
typedef pair<int,string> P;

const static int tx[4] = {+0,+1,+0,-1};
const static int ty[4] = {-1,+0,+1,+0};

bool dp[21][21][101][1<<10];

class State{
public:
  int x;
  int y;
  int time;
  int got;
  bool operator<(const State& s) const {
    return time < s.time;
  }
  bool operator>(const State& s) const {
    return time > s.time;
  }
  State(int x,int y,int time,int got) 
    : x(x), y(y), time(time), got(got){}
};

class Goods{
public:
  int item_id;
  int discounted_price;
  int sale_start_time;
  int sale_end_time;
  Goods(int item_id,int discounted_price, int sale_start_time,int sale_end_time)
    : item_id(item_id),discounted_price(discounted_price),sale_start_time(sale_start_time), sale_end_time(sale_end_time){}
  Goods(){}
};

int main(){
  int W,H;
  while(~scanf("%d %d",&W,&H)){
    if(W == 0 && H == 0) break;
    char stage[21][21];
    memset(dp,false,sizeof(dp));
    int sx,sy;
    for(int y = 0; y < H; y++){
      for(int x = 0; x < W; x++){
	char cell[8];
	scanf("%s",cell);
	stage[y][x] = cell[0];
	if(stage[y][x] == 'P'){
	  sy = y;
	  sx = x;
	}
      }
    }
    int total_time_sales;
    scanf("%d",&total_time_sales);

    map<int,Goods> goods;
    for(int i = 0; i < total_time_sales; i++){
      int item_id;
      int discounted_price;
      int sale_start_time;
      int sale_end_time;
      scanf("%d %d %d %d",
	    &item_id,
	    &discounted_price,
	    &sale_start_time,
	    &sale_end_time);
      goods[item_id] = Goods(item_id,discounted_price,sale_start_time,sale_end_time);
    }
    priority_queue<State,vector<State>,greater<State> > que;
    que.push(State(sx,sy,0,0));
    dp[sx][sy][0][0] = true;
    while(!que.empty()){
      State s = que.top();
      que.pop();
      for(int i = 0; i < 4; i++){
	int dx = s.x + tx[i];
	int dy = s.y + ty[i];
	if(dx < 0 || dx >= W || dy < 0 || dy >= H) continue;
	if(stage[dy][dx] == '.' || stage[dy][dx] == 'P') continue;
	const Goods& g = goods[stage[dy][dx] - '0'];
	if(g.sale_start_time <= s.time && s.time < g.sale_end_time){
	  s.got |= (1 << g.item_id);
	}
      }

      for(int i = 0; i < 4; i++){
	int dx = s.x + tx[i];
	int dy = s.y + ty[i];
	if(dx < 0 || dx >= W || dy < 0 || dy >= H) continue;
	if(stage[dy][dx] != '.' && stage[dy][dx] != 'P') continue;
	if(dp[dx][dy][s.time+1][s.got]) continue;
	if(s.time+1 > 100) continue;
	dp[dx][dy][s.time+1][s.got] = true;
	que.push(State(dx,dy,s.time+1,s.got));
      }
    }

    int res = 0;
    for(int y = 0; y < H; y++){
      for(int x = 0; x < W; x++){
	for(int time = 0; time <= 100; time++){
	  for(int S = 0; S < (1<<10); S++){
	    if(dp[x][y][time][S]){
	      int sum = 0;
	      for(int i = 0; i < 10; i++){
		if(S & (1<<i)){
		  sum += goods[i].discounted_price;
		}
	      }
	      res = max(res,sum);
	    }
	  }
	}
      }
    }
    printf("%d\n",res);
  }
}
