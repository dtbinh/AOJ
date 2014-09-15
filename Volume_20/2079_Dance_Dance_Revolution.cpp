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

int main(){
  int N;
  while(~scanf("%d",&N)){
    for(int i = 0; i < N; i++){
      bool isok = true;
      string command;
      cin >> command;

      int lpos = 3;
      int rpos = 1;
      if(!check_sequence(command)){
	isok = false;
	goto gameover;
      }
      for(int command_i = 0; command_i < command.size(); command_i++){
	if(command_i % 2 == 1) {
	  if(command[command_i] == 'U'){
	    lpos = 0;
	  }
	  else if(command[command_i] == 'R'){
	    lpos = 1;
	  }
	  else if(command[command_i] == 'D'){
	    lpos = 2;
	  }
	  else if(command[command_i] == 'L'){
	    lpos = 3;
	  }
	}
	else {
	  if(command[command_i] == 'U'){
	    rpos = 0;
	  }
	  else if(command[command_i] == 'R'){
	    rpos = 1;
	  }
	  else if(command[command_i] == 'D'){
	    rpos = 2;
	  }
	  else if(command[command_i] == 'L'){
	    rpos = 3;
	  }
	}

	if(!check_cross(lpos,rpos)){
	  isok = false;
	  goto gameover;
	}
      }

    gameover:;
      printf("%s\n",isok ? "Yes" : "No");
    }
  }
}
