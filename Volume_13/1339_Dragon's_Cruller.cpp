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

static const int W = 3;
static const int H = 3;

vector<int> move[9];
int move_cost[2];
int init;
int goal;

class State{
public:
  int white_space_pos;
  int stage;
  int cost;
  State(int _w,int _st,int _c)
    : white_space_pos(_w),stage(_st),cost(_c) {}
  bool operator <(const State& s) const {
    return cost < s.cost;
  }
  bool operator >(const State& s) const {
    return cost > s.cost;
  }
};


int fast_pow(int x, int n) {
  int res = 1;
  while(n > 0) {
    if (n & 1) res = res * x;
    x = x * x;
    n >>= 1;
  }
  return res;
}

int idx2num(int target,int idx){
  target = target / fast_pow(10,idx);
  return target % 10;
}

int change(int stage,int pos,int num){
  return stage - ((stage % fast_pow(10,pos + 1)) / fast_pow(10,pos))
    * fast_pow(10,pos) + fast_pow(10,pos) * num;
}

void bfs(int white_space_pos){
  map<int,int> dp;
  int conv[10];

  for(int i=0;i<9;i++){
    conv[idx2num(goal,i)] = i;
  }

  priority_queue<State,vector<State>,greater<State> > que;
  que.push(State(white_space_pos,init,0));

  map<int,int>::iterator it;
  int res = INF;

  while(!que.empty()){
    State s = que.top();
    que.pop();

    dp[s.stage] = s.cost;
    if(s.stage == goal){
      res = s.cost;
      break;
    }

    for(int i=0;i<4;i++){

      int neighbor = move[s.white_space_pos][i];
      int next = s.stage;

      next = change(s.stage,neighbor,0);
      next = change(next,s.white_space_pos,idx2num(s.stage,neighbor));

      if((it = dp.find(next)) != dp.end()
	 && it->second <= s.cost + move_cost[i % 2]){
	continue;
      }
      dp[next] = s.cost + move_cost[i % 2];
      que.push(State(neighbor,next,s.cost + move_cost[i % 2]));
    }
  }
  printf("%d\n",res);
}

int main(){
  enum Cell{
    A,B,C,D,E,F,G,H,I
  };

  //clockwise
  move[A].push_back(G);
  move[A].push_back(B);
  move[A].push_back(D);
  move[A].push_back(I);

  move[B].push_back(H);
  move[B].push_back(C);
  move[B].push_back(E);
  move[B].push_back(A);

  move[C].push_back(I);
  move[C].push_back(D);
  move[C].push_back(F);
  move[C].push_back(B);

  move[D].push_back(A);
  move[D].push_back(E);
  move[D].push_back(G);
  move[D].push_back(C);

  move[E].push_back(B);
  move[E].push_back(F);
  move[E].push_back(H);
  move[E].push_back(D);

  move[F].push_back(C);
  move[F].push_back(G);
  move[F].push_back(I);
  move[F].push_back(E);

  move[G].push_back(D);
  move[G].push_back(H);
  move[G].push_back(A);
  move[G].push_back(F);

  move[H].push_back(E);
  move[H].push_back(I);
  move[H].push_back(B);
  move[H].push_back(G);

  move[I].push_back(F);
  move[I].push_back(A);
  move[I].push_back(C);
  move[I].push_back(H);

  //0:vertical 1:horizontal
  while(~scanf("%d %d",&move_cost[1],&move_cost[0])){
    if(move_cost[1] == 0 
       && move_cost[0] == 0) break;
    init = 0;
    goal = 0;

    int white_space_pos = 0;
    vector<int> rev_init;
    vector<int> rev_goal;
    for(int y=0;y<3;y++){
      for(int x=0;x<3;x++){
	int num = 0;
	scanf("%d",&num);
	rev_init.push_back(num);
	if(num == 0){
	  white_space_pos = y * W + x;
	}
      }
    }

    for(int i=rev_init.size() - 1;i>=0;i--){
      init = init * 10 + rev_init[i];
    }
    int white_space_pos_g = 0;
    for(int y=0;y<3;y++){
      for(int x=0;x<3;x++){
	int num = 0;
	scanf("%d",&num);
	rev_goal.push_back(num);
      }
    }
    for(int i=rev_goal.size() - 1;i>=0;i--){
      goal = goal * 10 + rev_goal[i];
    }

    bfs(white_space_pos);
  }
}
