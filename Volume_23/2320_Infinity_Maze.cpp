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
  int H,W,L;
  while(~scanf("%d %d %d",&H,&W,&L)){
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

    while(L-- > 0){
      int dx = current_x + tx[current_dir];
      int dy = current_y + ty[current_dir];

      // printStage(stage,H,W,current_x,current_y,current_dir);
      // cout << dx << " " << dy << " " << endl;
      if(dy < 0 || dy >= H || dx < 0 || dx >= W){
	current_dir = (current_dir + 1) % 4;
	L++;
	continue;
      }
      else if(stage[dy][dx] == '#'){
	current_dir = (current_dir + 1) % 4;
	L++;
	continue;
      }
      current_x = dx;
      current_y = dy;
    }
    printf("%d %d %c\n",current_y+1,current_x+1,dir_char[current_dir]);
  }
}
