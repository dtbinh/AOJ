#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdio>
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
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
 
static const double EPS = 1e-8;

static const char* one[8]
= {
  "#######",
  "#.....#",
  "#...|.#",
  "#.....#",
  "#...|.#",
  "#..-..#",
  "#######",
};

static const char* two[8] 
= {
  "#######",
  "#..-..#",
  "#...|.#",
  "#..-..#",
  "#.|...#",
  "#..-..#",
  "#######",
};

static const char* three[8]
= {
  "#######",
  "#..-..#",
  "#...|.#",
  "#..-..#",
  "#...|.#",
  "#..-..#",
  "#######",
};

static const char* four[8]
= {
  "#######",
  "#.....#",
  "#.|.|.#",
  "#..-..#",
  "#...|.#",
  "#.....#",
  "#######",
};

static const char* five[8] 
= {
  "#######",
  "#..-..#",
  "#.|...#",
  "#..-..#",
  "#...|.#",
  "#..-..#",
  "#######",
};

static const char* six[8]
= {
  "#######",
  "#..-..#",
  "#.|...#",
  "#..-..#",
  "#.|.|.#",
  "#..-..#",
  "#######",
};
   
static const char* seven[8]
= {
  "#######",
  "#..-..#",
  "#...|.#",
  "#.....#",
  "#...|.#",
  "#.....#",
  "#######",
};
   
   
static const char* eight[8]
= {
  "#######",
  "#..-..#",
  "#.|.|.#",
  "#..-..#",
  "#.|.|.#",
  "#..-..#",
  "#######",
};

static const char* nine[8]
= {
  "#######",
  "#..-..#",
  "#.|.|.#",
  "#..-..#",
  "#...|.#",
  "#..-..#",
  "#######",
};

static const char** dice[9] = 
  {one,two,three,four,five,six,seven,eight,nine};

class Reader {
private:
  char target[7][7];

  void rotate90(){
    char tmp[7][7];
    for(int y=0;y<7;y++){
      for(int x=0;x<7;x++){
	int dy = x;
	int dx = 6-y;
	tmp[dy][dx] = target[y][x];
	if(target[y][x] == '|'){
	  tmp[dy][dx] = '-';
	}
	if(target[y][x] == '-'){
	  tmp[dy][dx] = '|';
	}
      }
    }
    memcpy(target,tmp,sizeof(char)*7*7);
  }

public:
  void disp(){
    for(int y=0;y<7;y++){
      for(int x=0;x<7;x++){
	printf("%c",target[y][x]);
      }
      printf("\n");
    }
    printf("\n");
  }

  void clip(int offset_y,int offset_x,
	    char stage[64][64]){
    for(int y=0;y<7;y++){
      for(int x=0;x<7;x++){
	target[y][x] = stage[offset_y + y][offset_x + x];
      }
    }
  }

  void flip_horizontal(){
    char tmp[7][7];
    for(int y=0;y<7;y++){
      for(int x=0;x<7;x++){
	tmp[y][6-x] = target[y][x];
      }
    }
    memcpy(target,tmp,sizeof(char)*7*7);
  }

  void flip_vertical(){
    char tmp[7][7];
    for(int y=0;y<7;y++){
      for(int x=0;x<7;x++){
	tmp[6-y][x] = target[y][x];
      }
    }
    memcpy(target,tmp,sizeof(char)*7*7);
  }

  void iter(int round){
    while(round > 0){
      rotate90();
      round--;
    }
  }

  int get_num(){
    for(int num=1;num<=9;num++){
      bool isok = true;
      for(int y=0;y<7;y++){
	for(int x=0;x<7;x++){
	  if(target[y][x] != dice[num-1][y][x]){
	    isok = false;
	    goto over;
	  }
	}
      }
      
    over:;
      if(isok) return num;
    }
    return -1;
  }
};


int main(){
  int H = 21;
  int W = 57;
  
  char line[64];

  while(~scanf("%s",line)){
    if(line[0] == '0') break;

    char stage[64][64];
    for(int x=0;x<W;x++){
      stage[0][x] = line[x];
    }

    for(int y=1;y<H;y++){
      scanf("%s",line);
      for(int x=0;x<W;x++){
	stage[y][x] = line[x];
      }
    }

    Reader reader;
    int player_sum = 0;
    reader.clip(0,7,stage);
    reader.flip_horizontal();
    player_sum += reader.get_num();

    reader.clip(7,0,stage);
    reader.flip_horizontal();
    reader.iter(3);
    player_sum += reader.get_num();

    reader.clip(7,7,stage);
    reader.flip_horizontal();
    player_sum += reader.get_num();

    reader.clip(7,14,stage);
    reader.flip_horizontal();
    reader.iter(1);
    player_sum += reader.get_num();

    reader.clip(7,21,stage);
    reader.flip_horizontal();
    player_sum += reader.get_num();

    reader.clip(14,7,stage);
    reader.flip_vertical();
    player_sum += reader.get_num();

    int enemy_sum = 0;
    reader.clip(0,36,stage);
    reader.flip_horizontal();
    enemy_sum += reader.get_num();

    reader.clip(7,29,stage);
    reader.flip_horizontal();
    reader.iter(3);
    enemy_sum += reader.get_num();

    reader.clip(7,36,stage);
    reader.flip_horizontal();
    enemy_sum += reader.get_num();

    reader.clip(7,43,stage);
    reader.flip_horizontal();
    reader.iter(1);
    enemy_sum += reader.get_num();

    reader.clip(7,50,stage);
    reader.flip_horizontal();
    enemy_sum += reader.get_num();

    reader.clip(14,36,stage);
    reader.flip_vertical();
    enemy_sum += reader.get_num();

    printf("%s\n",player_sum >= enemy_sum ? "HIGH" : "LOW");
  }
}
