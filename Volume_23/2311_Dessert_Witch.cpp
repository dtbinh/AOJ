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
 
const static int tx[] = {0,1,1,1,0,-1,-1,-1};
const static int ty[] = {-1,-1,0,1,1,1,0,-1};
 
static const double EPS = 1e-8;

struct ChooseHand{
  int pos_x;
  int pos_y;
  int dir;
  int get_stone_num;
};

char stage[8][8];

ChooseHand search(int x,int y,char stone){
  int max_get_stone_num = 0;
  char inv_stone = (stone == 'o' ? 'x' : 'o');

  int get_stone_num = 0;
  int dir = 0;
  for(int t_idx=0;t_idx<8;t_idx++){
    int tmp_get_num = 0;
    bool is_close = false;
    for(int dist=1;dist<=8;dist++){
      int dx = x + tx[t_idx] * dist;
      int dy = y + ty[t_idx] * dist;
      if(dx < 0 || dy < 0 
	 || dx >= 8 || dy >= 8) break;

      if(stage[dy][dx] == inv_stone){
	tmp_get_num++;
      }
      else if(stage[dy][dx] == stone){
	is_close = true;
	dir |= (1<<t_idx);
	break;
      }
      else{
	break;
      }
    }
    if(is_close){
      get_stone_num += tmp_get_num;
    }
  }

  ChooseHand ch = {x,y,dir,get_stone_num};
  return ch;
}

ChooseHand SearchForMami(char stone){
  int max_get_stone_num = 0;
  ChooseHand ch = {-1,-1,0,0};
  
  for(int y=0;y<8;y++){
    for(int x=0;x<8;x++){
      if(stage[y][x] != '.'){
	continue;
      }
      ChooseHand tmp_ch = search(x,y,stone);
      if(max_get_stone_num < tmp_ch.get_stone_num){
	max_get_stone_num = tmp_ch.get_stone_num;
	ch = tmp_ch;
      }
    }
  }
  return ch;
}

ChooseHand SearchForWitch(char stone){
  int max_get_stone_num = 0;
  ChooseHand ch = {-1,-1,0,0};
  
  for(int y=8-1;y>=0;y--){
    for(int x=8-1;x>=0;x--){
      if(stage[y][x] != '.'){
	continue;
      }
      ChooseHand tmp_ch = search(x,y,stone);
      if(max_get_stone_num < tmp_ch.get_stone_num){
	max_get_stone_num = tmp_ch.get_stone_num;
	ch = tmp_ch;
      }
    }
  }
  return ch;
}

void FlipStones(ChooseHand ch,char stone){
  int x = ch.pos_x;
  int y = ch.pos_y;
  stage[y][x] = stone;

  for(int t_idx=0;t_idx<8;t_idx++){
    if(!(ch.dir & (1<<t_idx))) continue;
    for(int dist=1;dist <= ch.get_stone_num; dist++){
      int dx = ch.pos_x + tx[t_idx] * dist;
      int dy = ch.pos_y + ty[t_idx] * dist;
      stage[dy][dx] = stone;
    }
  }
}

void PrintStage(){
  for(int y=0;y<8;y++){
    for(int x=0;x<8;x++){
      printf("%c",stage[y][x]);
    }
    printf("\n");
  }
  printf("\n");
}

int main(){
  char line[12];
  while(~scanf("%s",line)){
    for(int x=0;x<8;x++) stage[0][x] = line[x];
    for(int y=1;y<8;y++){
      scanf("%s",line);
      for(int x=0;x<8;x++){
	stage[y][x] = line[x];
      }
    }

    while(1){
      ChooseHand ch;
      //first player: mami o upper -> left
      ch = SearchForMami('o');
      if(ch.get_stone_num == 0) break;
      FlipStones(ch,'o');

      //second player: witch x lower -> right
      ch = SearchForWitch('x');
      if(ch.get_stone_num == 0) break;
      FlipStones(ch,'x');
    }
    
    PrintStage();
  }
}
