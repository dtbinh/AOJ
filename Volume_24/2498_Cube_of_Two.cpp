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
  
void opeU(char cube[6][9]){
  char next[6][9];
  memcpy(next,cube,sizeof(char) * 6 * 9);

  //red
  next[0][3] = cube[0][2];
  next[1][3] = cube[0][3];
  next[1][2] = cube[1][3];
  next[0][2] = cube[1][2];

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

  memcpy(cube,next,sizeof(char) * 6 * 9);
}

void opeR(char cube[6][9]){
  char next[6][9];
  memcpy(next,cube,sizeof(char) * 6 * 9);

  //blue
  next[2][5] = cube[2][4];
  next[3][5] = cube[2][5];
  next[3][4] = cube[3][5];
  next[2][4] = cube[3][4];

  //red
  next[2][6] = cube[1][3];
  next[3][6] = cube[0][3];

  //white
  next[5][3] = cube[2][6];
  next[4][3] = cube[3][6];

  //orange
  next[2][3] = cube[4][3];
  next[3][3] = cube[5][3];

  //yellow
  next[0][3] = cube[2][3];
  next[1][3] = cube[3][3];

  memcpy(cube,next,sizeof(char) * 6 * 9);
}

void opeL(char cube[6][9]){
  char next[6][9];
  memcpy(next,cube,sizeof(char) * 6 * 9);

  //green
  next[2][1] = cube[2][0];
  next[3][1] = cube[2][1];
  next[3][0] = cube[3][1];
  next[2][0] = cube[3][0];

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

  memcpy(cube,next,sizeof(char) * 6 * 9);
}

void opeF(char cube[6][9]){  
  char next[6][9];
  memcpy(next,cube,sizeof(char) * 6 * 9);

  //yellow
  next[2][3] = cube[2][2];
  next[3][3] = cube[2][3];
  next[3][2] = cube[3][3];
  next[2][2] = cube[3][2];
  
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

  memcpy(cube,next,sizeof(char) * 6 * 9);
}

void opeD(char cube[6][9]){
  char next[6][9];
  memcpy(next,cube,sizeof(char) * 6 * 9);

  //orange
  next[4][3] = cube[4][2];
  next[5][3] = cube[4][3];
  next[5][2] = cube[5][3];
  next[4][2] = cube[5][2];

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

  memcpy(cube,next,sizeof(char) * 6 * 9);
}

void opeB(char cube[6][9]){
  char next[6][9];
  memcpy(next,cube,sizeof(char) * 6 * 9);

  //white
  next[2][7] = cube[2][6];
  next[3][7] = cube[2][7];
  next[3][6] = cube[3][7];
  next[2][6] = cube[3][6];

  //red
  next[3][0] = cube[0][2];
  next[2][0] = cube[0][3];

  //green
  next[5][2] = cube[2][0];
  next[5][3] = cube[3][0];

  //orange
  next[3][5] = cube[5][2];
  next[2][5] = cube[5][3];

  //blue
  next[0][2] = cube[2][5];
  next[0][3] = cube[3][5];

  memcpy(cube,next,sizeof(char) * 6 * 9);
}

void disp(char cube[6][9]){
  for(int y=0;y<6;y++){
    for(int x=0;x<8;x++){
      printf("%c",cube[y][x]);
    }
    printf("\n");
  }
  printf("\n");
}

int main(){

  char cube[][9] = {
    "..rr....",
    "..rr....",
    "ggyybbww",
    "ggyybbww",
    "..oo....",
    "..oo...."
  };

  string command;
  while(cin >> command){
    // char tmp[6][9];
    // memcpy(tmp,cube,sizeof(char) * 6 * 9);

    for(int i=0;i<command.size();i++){
      if(command[i] == 'U'){
	opeU(cube);
      }
      else if(command[i] == 'F'){
	opeF(cube);
      }
      else if(command[i] == 'R'){
	opeR(cube);
      }
      else if(command[i] == 'D'){
	opeD(cube);
      }
      else if(command[i] == 'B'){
	opeB(cube);
      }
      else if(command[i] == 'L'){
	opeL(cube);
      }
      
      disp(cube);
    }
    // memcpy(cube,tmp,sizeof(char) * 6 * 9);
  }
}
