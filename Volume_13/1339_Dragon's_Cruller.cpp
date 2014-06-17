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
string init;
string goal;

class State{
public:
  int white_space_pos;
  string stage;
  int cost;
  int heuristic;
  short depth;
  State(int _w,const string& _st,int _c,int _h,int _d)
    : white_space_pos(_w),stage(_st),cost(_c),heuristic(_h),depth(_d) {}
  bool operator <(const State& s) const {
    return cost + heuristic < s.cost + s.heuristic;
  }
  bool operator >(const State& s) const {
    return cost + heuristic > s.cost + s.heuristic;
  }
};


int calc(const string& stage,char conv[256],
	 int edges[10][10]){
  int res = 0;
  for(int spos=0;spos<9;spos++){
    int gpos = conv[stage[spos]];
    res += edges[spos][gpos];
  }
  return res;
}

void bfs(int white_space_pos_s,int white_space_pos_g){
  map<string,int> s2g_dp;
  map<string,int> g2s_dp;
  char conv_g[256];
  char conv_s[256];

  int edges[10][10];
  memset(edges,0x3f,sizeof(edges));


  for(int i=0;i<9;i++){
    conv_g[goal[i]] = i;
    conv_g[init[i]] = i;
    for(int j=0;j<4;j++){
      edges[i][move[i][j]] = move_cost[j % 2];
      edges[move[i][j]][i] = move_cost[j % 2];
    }
  }

  for(int k=0;k<9;k++){
    for(int i=0;i<9;i++){
      for(int j=0;j<9;j++){
	edges[i][j] = min(edges[i][j],
			  edges[i][k] + edges[k][j]);
      }
    }
  }

  priority_queue<State,vector<State>,greater<State> > que;

  que.push(State(white_space_pos_s,init,0,calc(init,conv_s,edges),0));

  map<string,int>::iterator it;
  int res = INF;
  while(!que.empty()){
    State s = que.top();
    que.pop();

    if(s.depth >= 11) continue;
    s2g_dp[s.stage] = s.cost;

    if(s.stage == goal){
      res = s.cost;
      break;
    }

    // int h = calc(s.stage,conv_s,edges);
    int h = 0;
    for(int i=0;i<4;i++){

      int from = move[s.white_space_pos][i];
      string next = s.stage;

      // int gpos_sp = conv_s[s.stage[s.white_space_pos]];
      // h -= edges[s.white_space_pos][gpos_sp];

      // int gpos_nsp = conv_s[s.stage[from]];
      // h -= edges[from][gpos_nsp];

      next[from] = '0';
      next[s.white_space_pos] = s.stage[from];

      // gpos_sp = conv_s[next[from]];
      // h += edges[from][gpos_sp];

      // gpos_nsp = conv_s[next[s.white_space_pos]];
      // h += edges[s.white_space_pos][gpos_nsp];

      if(s2g_dp.find(next) != s2g_dp.end()
	 && s2g_dp[next] <= s.cost + move_cost[i % 2]){
	continue;
      }
      s2g_dp[next] = s.cost + move_cost[i % 2];
      que.push(State(from,next,s.cost + move_cost[i % 2],h,s.depth+1));
    }
  }

  priority_queue<State,vector<State>,greater<State> > empty;
  swap(que,empty);

  priority_queue<State,vector<State>,greater<State> > que2;
  que2.push(State(white_space_pos_g,goal,0,calc(goal,conv_g,edges),0));

  while(!que2.empty()){
    State s = que2.top();
    que2.pop();

    if(s.depth >= 11) continue;
    g2s_dp[s.stage] = s.cost;

    if(s.stage == init){
      res = s.cost;
      break;
    }

    // int h = calc(s.stage,conv_g,edges);
    int h = 0;
    for(int i=0;i<4;i++){

      int from = move[s.white_space_pos][i];
      string next = s.stage;

      // int gpos_sp = conv_g[s.stage[s.white_space_pos]];
      // h -= edges[s.white_space_pos][gpos_sp];

      // int gpos_nsp = conv_g[s.stage[from]];
      // h -= edges[from][gpos_nsp];

      next[from] = '0';
      next[s.white_space_pos] = s.stage[from];

      // gpos_sp = conv_g[next[from]];
      // h += edges[from][gpos_sp];

      // gpos_nsp = conv_g[next[s.white_space_pos]];
      // h += edges[s.white_space_pos][gpos_nsp];

      if(g2s_dp.find(next) != g2s_dp.end()
	 && g2s_dp[next] <= s.cost + move_cost[i % 2]){
	continue;
      }
      g2s_dp[next] = s.cost + move_cost[i % 2];
      que2.push(State(from,next,s.cost + move_cost[i % 2],h,s.depth+1));
    }
  }

  if(res == INF){
    for(map<string,int>::iterator it = g2s_dp.begin();
	it != g2s_dp.end();
	it++){
      map<string,int>::iterator it2;
      if((it2 = s2g_dp.find(it->first)) != s2g_dp.end()){
	res = min(res,it->second + it2->second);
      }
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
    init = "";
    goal = "";

    int white_space_pos_s = 0;
    for(int y=0;y<3;y++){
      for(int x=0;x<3;x++){
	int num = 0;
	scanf("%d",&num);
	init.push_back('0' + num);
	if(num == 0){
	  white_space_pos_s = y * W + x;
	}
      }
    }
    int white_space_pos_g = 0;
    for(int y=0;y<3;y++){
      for(int x=0;x<3;x++){
	int num = 0;
	scanf("%d",&num);
	goal.push_back('0' + num);
	if(num == 0){
	  white_space_pos_g = y * W + x;
	}
      }
    }
    bfs(white_space_pos_s,white_space_pos_g);
  }
}
