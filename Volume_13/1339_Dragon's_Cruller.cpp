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

void dfs(map<string,int>& dp,string& stage,
	 int to,int cost){

  for(int i=0;i<4;i++){
    int from = move[to][i];
    swap(stage[to],stage[from]);
    if(dp.find(stage) != dp.end()
       && dp[stage] <= cost + move_cost[i % 2]){
      swap(stage[to],stage[from]);
      continue;
    }

    dp[stage] = cost + move_cost[i % 2];
    dfs(dp,stage,from,cost + move_cost[i % 2]);
    swap(stage[to],stage[from]);
  }
}

int main(){
  enum Cell{
    A,B,C,D,E,F,G,H,I
  };

  //non-clockwise
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
    init = "";
    goal = "";

    int to = 0;
    for(int y=0;y<3;y++){
      for(int x=0;x<3;x++){
	int num = 0;
	scanf("%d",&num);
	init.push_back('0' + num);
	if(num == 0){
	  to = y * W + x;
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
    map<string,int> dp;
    dp[init] = 0;
    dfs(dp,init,to,0);
  }
}
