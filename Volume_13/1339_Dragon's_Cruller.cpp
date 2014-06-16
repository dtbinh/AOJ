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

int main(){
  int horizontaly_cost;
  int verticaly_cost;
  
  vector<int> move[9];

  enum Cell{
    A,B,C,D,E,F,G,H,I
  };

  //non-clockwise
  move[A].push_back(B);
  move[A].push_back(I);
  move[A].push_back(G);
  move[A].push_back(D);

  move[B].push_back(C);
  move[B].push_back(A);
  move[B].push_back(H);
  move[B].push_back(E);

  move[C].push_back(D);
  move[C].push_back(B);
  move[C].push_back(I);
  move[C].push_back(F);

  move[D].push_back(E);
  move[D].push_back(C);
  move[D].push_back(A);
  move[D].push_back(G);

  move[E].push_back(F);
  move[E].push_back(D);
  move[E].push_back(B);
  move[E].push_back(H);

  move[F].push_back(G);
  move[F].push_back(E);
  move[F].push_back(C);
  move[F].push_back(I);

  move[G].push_back(H);
  move[G].push_back(F);
  move[G].push_back(D);
  move[G].push_back(A);

  move[H].push_back(I);
  move[H].push_back(G);
  move[H].push_back(E);
  move[H].push_back(B);

  move[I].push_back(A);
  move[I].push_back(H);
  move[I].push_back(F);
  move[I].push_back(C);

  while(~scanf("%d %d",&horizontaly_cost,&verticaly_cost)){
    int init[3][3];
    int goal[3][3];

    for(int y=0;y<3;y++){
      for(int x=0;x<3;x++){
	scanf("%d",&init[y][x]);
      }
    }
    for(int y=0;y<3;y++){
      for(int x=0;x<3;x++){
	scanf("%d",&goal[y][x]);
      }
    }

    
  }
}
