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

//dp[prev,now][left_state][right_state][prev_foot_side]
int prev[10][10][2];
int next[10][10][2];

const int gHorizonalPos[] = {
  -1//none
  ,0//1->0
  ,1//2->1
  ,2//3->2
  ,0//4->0
  ,-1//5->-1(none)
  ,2//6->2
  ,0//7->0
  ,1//8->1
  ,2//9->2
};

bool canEnter(int prev_left_state,int prev_right_state,int next_step_state,
	     int next_foot_side,int prev_foot_side){
  int LHpos = gHorizonalPos[prev_left_state];
  int RHpos = gHorizonalPos[prev_right_state];
  int NHpos = gHorizonalPos[next_step_state];

  //next_foot_side := 0(left)
  if(next_foot_side == 0){
    if(RHpos == -1) return true;
    return RHpos < NHpos ? false : true;
  }
  //next_foot_side := 1(right)
  else if(next_foot_side == 1){
    if(LHpos == -1) return true;
    return NHpos < LHpos ? false : true;
  }
}

int ComputeLeastCost(){
  int res = INF;
  for(int left_state=0;left_state<10;left_state++){
    if(left_state == 5) continue;
    for(int right_state=0;right_state<10;right_state++){
    if(right_state == 5) continue;
      for(int foot_side=0;foot_side<2;foot_side++){
	res = min(res,next[left_state][right_state][foot_side]);
      }
    }
  }
  return res;
}

void debug(int next_step_pos,int turn){
  printf("turn:%d target:%d\n",turn,next_step_pos);
  for(int prev_left_state=0;prev_left_state<10;prev_left_state++){
    if(prev_left_state == 5) continue;
    for(int prev_right_state=0;prev_right_state<10;prev_right_state++){
      if(prev_right_state == 5) continue;
      for(int next_foot_side = 0;next_foot_side<2;next_foot_side++){
	printf("turn %d, left_state %d,right_state %d,foot_side %d,val %d\n",
	       turn,
	       prev_left_state,
	       prev_right_state,
	       next_foot_side,
	       next[prev_left_state][prev_right_state][next_foot_side]);
      }
    }
  }

  printf("\n");
}

int main(){
  string str;
  while(cin >> str){
    if(str.size() == 1 && str[0] == '#') break;

    memset(prev,0x3f,sizeof(prev));
    memset(next,0x3f,sizeof(next));
    prev[0][0][0] = 0;
    prev[0][0][1] = 0;
    for(int turn=0;turn < str.size(); turn++){
      memset(next,0x3f,sizeof(next));
      int next_step_pos = str[turn]-'0';
      for(int prev_left_state=0;prev_left_state<10;prev_left_state++){
	if(prev_left_state == 5) continue;
	for(int prev_right_state=0;prev_right_state<10;prev_right_state++){
	  if(prev_right_state == 5) continue;
	  for(int next_foot_side = 0;next_foot_side<2;next_foot_side++){
	    for(int prev_foot_side = 0;prev_foot_side<2;prev_foot_side++){
	      if(!canEnter(prev_left_state,prev_right_state,
			   next_step_pos,next_foot_side,prev_foot_side)) continue;

	      //dp[prev,now][left_state][right_state][prev_foot_side]
	      int cost = (prev_foot_side == next_foot_side ? 1 : 0);

	      if(next_foot_side == 0){
		next[next_step_pos][prev_right_state][next_foot_side]=min(cost
									  +prev[prev_left_state][prev_right_state][prev_foot_side],
									   next[next_step_pos][prev_right_state][next_foot_side]);
	      }

	      else{
		next[prev_left_state][next_step_pos][next_foot_side]=min(cost
									 +prev[prev_left_state][prev_right_state][prev_foot_side],
									  next[prev_left_state][next_step_pos][next_foot_side]);
	      }
	    }
	  }
	}
      }

      memcpy(prev,next,sizeof(next));

      // debug(next_step_pos,turn);
    }
    printf("%d\n",ComputeLeastCost());
  }
}
