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
 
const static int tx[] = {1,0,-1,0};
const static int ty[] = {0,1,0,-1};
const static char dir_char[] = {'E','S','W','N'};
 
enum dir {
  EAST,
  SOUTH,
  WEST,
  NORTH
};

struct PosInfo{
  int x;
  int y;
  int dir;
  PosInfo(int _x,int _y,int _dir) : x(_x),y(_y),dir(_dir) {}
};

static const double EPS = 1e-8;


void printStage(char stage[100][100],int H,int W,
		int current_x,int current_y,int current_dir){

  char output[100][100];

  //init
  for(int y=0;y<H;y++){
    for(int x=0;x<W;x++){
      output[y][x] = '.';
    }
  }

  //wall
  for(int y=0;y<H;y++){
    for(int x=0;x<W;x++){
      if(stage[y][x] == '#'){
	output[y][x] = '#';
      }
    }
  }

  //robot
  output[current_y][current_x] = dir_char[current_dir];

  //write
  for(int y=0;y<H;y++){
    for(int x=0;x<W;x++){
      printf("%c",output[y][x]);
    }
    printf("\n");
  }
  printf("\n");
}

int main(){
  int H,W;
  ll L;
  while(~scanf("%d %d %ld",&H,&W,&L)){
    if(H == 0 && W == 0 && L == 0) break;

    char stage[100][100];

    int current_dir = NORTH;
    int current_x = 0;
    int current_y = 0;

    for(int y=0;y<H;y++){
      char line[120];
      scanf("%s",line);
      for(int x=0;x<W;x++){
	stage[y][x] = line[x];
	if(stage[y][x] == 'E'){
	  current_dir = EAST;
	  current_x = x;
	  current_y = y;
	}
	else if(stage[y][x] == 'S'){
	  current_dir = SOUTH;
	  current_x = x;
	  current_y = y;
	}
	else if(stage[y][x] == 'W'){
	  current_dir = WEST;
	  current_x = x;
	  current_y = y;
	}
	else if(stage[y][x] == 'N'){
	  current_dir = NORTH;
	  current_x = x;
	  current_y = y;
	}
      }
    }

    int dp[4][100][100];
    for(int i=0;i<4;i++){
      memset(dp[i],-1,sizeof(dp[i]));
    }

    ll round = 0;
    for(;round < L;round++){
      if(dp[current_dir][current_x][current_y] >= 0) break;
      
      dp[current_dir][current_x][current_y]=round;
      // printStage(stage,H,W,current_x,current_y,current_dir);
      // cout << dx << " " << dy << " " << endl;

      for(int i=0;i<4;i++){
	//i==0 : not rotating
	int next_dir = (current_dir + i) % 4;
	int dx = current_x + tx[next_dir];
	int dy = current_y + ty[next_dir];

	if(dy < 0 || dy >= H || dx < 0 || dx >= W){
	  continue;
	}
	else if(stage[dy][dx] == '#'){
	  continue;
	}

	current_dir = next_dir;
	current_x = dx;
	current_y = dy;
	break;
      }
    }

    int res_x = current_x;
    int res_y = current_y;
    int res_dir = current_dir;

    //start:0 3 6 9 ... start:96
    ll last_round = round;
    ll cycle_begining_round = dp[current_dir][current_x][current_y];

    if(last_round < L){
      ll cycle_length = last_round - cycle_begining_round;
      ll cycle_relative_pos = (L - cycle_begining_round) % cycle_length;
      ll cycle_abs_pos = cycle_relative_pos + cycle_begining_round;

      for(int i=0;i<4;i++){
	for(int x=0;x<W;x++){
	  for(int y=0;y<H;y++){
	    // printf("i:%d x:%d y:%d %d\n",i,x,y,dp[i][x][y]);
	    if(dp[i][x][y] == cycle_abs_pos){
	      res_x = x;
	      res_y = y;
	      res_dir = i;
	    }
	  }
	}
      }
    }

    printf("%d %d %c\n",res_y+1,res_x+1,dir_char[res_dir]);
  }
}
