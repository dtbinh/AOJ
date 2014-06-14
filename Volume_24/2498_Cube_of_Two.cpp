#define _USE_MATH_DEFINES
#define INF 100000000
  
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
  
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
  
void opeU(char cube[6][8]){
  char next[6][8];
  memset(next,cube,sizeof(char) * 6 * 8);

  //white
  next[2][5] = cube[2][6];
  next[2][4] = cube[2][7];

  //blue
  next[2][2] = cube[2][4];
  next[2][3] = cube[2][5];

  //yellow
  next[2][0] = cube[2][2];
  next[2][1] = cube[2][3];

  //green
  next[2][6] = cube[2][0];
  next[2][7] = cube[2][1];

}

void opeR(char cube[6][8]){
  char next[6][8];
  memset(next,cube,sizeof(char) * 6 * 8);

  //orange
  next[2][3] = cube[4][3];
  next[3][3] = cube[5][3];

  //red
  next[2][6] = cube[0][3];
  next[3][6] = cube[1][3];

  //white
  next[4][3] = cube[2][6];
  next[5][3] = cube[3][6];

  //yellow
  next[2][3] = cube[4][3];
  next[3][3] = cube[5][3];
}

void opeL(char cube[6][8]){
  char next[6][8];
  memset(next,cube,sizeof(char) * 6 * 8);

  //red
  next[2][2] = cube[0][2];
  next[3][2] = cube[1][2];

  //yellow
  next[4][2] = cube[2][2];
  next[5][2] = cube[3][2];

  //orange
  next[3][7] = cube[4][2];
  next[2][7] = cube[5][2];

  //white
  next[0][2] = cube[3][7];
  next[1][2] = cube[2][7];

}

void opeF(char cube[6][8]){  
  char next[6][8];
  memset(next,cube,sizeof(char) * 6 * 8);

  //red
  next[2][4] = cube[1][2];
  next[3][4] = cube[1][3];

  //blue
  next[4][3] = cube[2][4];
  next[4][2] = cube[3][4];

  //orange
  next[2][1] = cube[4][3];
  next[3][1] = cube[4][2];

  //green
  next[1][3] = cube[2][1];
  next[1][2] = cube[3][1];
}

void opeD(char cube[6][8]){
  char next[6][8];
  memset(next,cube,sizeof(char) * 6 * 8);

  //yellow
  next[3][4] = cube[3][2];
  next[3][5] = cube[3][3];
  
  //blue
  next[3][6] = cube[3][4];
  next[3][7] = cube[3][5];

  //white
  next[3][0] = cube[3][6];
  next[3][1] = cube[3][7];

  //green
  next[3][2] = cube[3][0];
  next[3][3] = cube[3][1];
}

void opeB(char cube[6][8]){
  char next[6][8];
  memset(next,cube,sizeof(char) * 6 * 8);

  //red
  next[2][5] = cube[0][2];
  next[3][5] = cube[0][3];

  //blue
  next[5][2] = cube[2][5];
  next[5][3] = cube[3][5];

  //orange
  next[2][0] = cube[5][2];
  next[3][0] = cube[5][3];

  //green
  next[0][2] = cube[2][0];
  next[0][3] = cube[3][0];

}

int main(){
  string ope;
  
  char cube[6][8] = {"..rr....",
		     "..rr....",
		     "ggyybbww",
		     "ggyybbww",
		     "..oo....",
		     "..oo...."};
		   
  while(cin >> ope){
  }
}
