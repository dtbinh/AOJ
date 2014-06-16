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
  State(int _w,const string& _st,int _c,int _h)
    : white_space_pos(_w),stage(_st),cost(_c),heuristic(_h) {}
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

void bfs(int white_space_pos){
  map<string,int> dp;
  char conv[256];

  int edges[10][10];
  memset(edges,0x3f,sizeof(edges));


  for(int i=0;i<9;i++){
    conv[goal[i]] = i;
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

  que.push(State(white_space_pos,init,0,calc(init,conv,edges)));

  while(!que.empty()){
    State s = que.top();
    que.pop();
    // dp[s.stage] = s.cost;

    if(s.stage == goal) break;

    int h = calc(s.stage,conv,edges);
    for(int i=0;i<4;i++){

      int from = move[s.white_space_pos][i];
      string next = s.stage;

      int gpos_sp = conv[s.stage[s.white_space_pos]];
      h -= edges[s.white_space_pos][gpos_sp];

      int gpos_nsp = conv[s.stage[from]];
      h -= edges[from][gpos_nsp];

      next[from] = '0';
      next[s.white_space_pos] = s.stage[from];

      gpos_sp = conv[next[from]];
      h += edges[from][gpos_sp];

      gpos_nsp = conv[next[s.white_space_pos]];
      h += edges[s.white_space_pos][gpos_nsp];

      map<string,int>::iterator it;
      if((it = dp.find(next)) != dp.end()
	 && it->second <= s.cost + move_cost[i % 2]){
	continue;
      }
      dp[next] = s.cost + move_cost[i % 2];

      que.push(State(from,next,s.cost + move_cost[i % 2],h));
    }
  }
  printf("%d\n",dp[goal]);
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

    int white_space_pos = 0;
    for(int y=0;y<3;y++){
      for(int x=0;x<3;x++){
	int num = 0;
	scanf("%d",&num);
	init.push_back('0' + num);
	if(num == 0){
	  white_space_pos = y * W + x;
	}
      }
    }
    for(int y=0;y<3;y++){
      for(int x=0;x<3;x++){
	int num = 0;
	scanf("%d",&num);
	goal.push_back('0' + num);
      }
    }
    bfs(white_space_pos);
  }
}
