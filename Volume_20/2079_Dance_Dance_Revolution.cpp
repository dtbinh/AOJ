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
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

bool check_sequence(const string& command){
  for(int i=0;i+1<command.size();i++){
    if(command[i] == command[i+1]) return false;
  }
  return true;
}

bool check_cross(int lpos,int rpos){
  if(lpos == -1 || rpos == -1) return true;
  if(lpos !=0 && lpos < rpos) return false;
  if(lpos == 0 && rpos == 3) return false;
  return true;
}

int compute_pos(char dir){
  int pos = 0;
  if(dir == 'U'){
    pos = 0;
  }
  else if(dir == 'R'){
    pos= 1;
  }
  else if(dir == 'D'){
    pos = 2;
  }
  else if(dir == 'L'){
    pos = 3;
  }

  return pos;
}

int main(){
  int N;
  while(~scanf("%d",&N)){
    for(int i = 0; i < N; i++){
      bool isok = true;
      string command;
      cin >> command;

      int lpos = -1;
      int rpos = -1;
      int flag = 0;

      if(!check_sequence(command)){
	isok = false;
	goto gameover;
      }

      for(int command_i = 0; command_i < command.size(); command_i++){
	if(command_i % 2 == 1) {
	  lpos = compute_pos(command[command_i]);
	}
	else {
	  rpos = compute_pos(command[command_i]);
	}

	if(!check_cross(lpos,rpos)){
	  flag |= (1<<0);
	}
      }

      lpos = -1;
      rpos = -1;

      for(int command_i = 0; command_i < command.size(); command_i++){
	if(command_i % 2 == 0) {
	  lpos = compute_pos(command[command_i]);
	}
	else {
	  rpos = compute_pos(command[command_i]);
	}

	if(!check_cross(lpos,rpos)){
	  flag |= (1<<1);
	}
      }

    gameover:;
      printf("%s\n",(!isok || (flag == (1<<2) - 1)) ? "No" : "Yes");
    }
  }
}
