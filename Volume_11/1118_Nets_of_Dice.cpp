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
 
const static int tx[] = {0,1,0,-1};
const static int ty[] = {-1,0,1,0};

const static double EPS = 1e-8;

struct Face {
  int diff_x;
  int diff_y;
  int num;
  Face(int x,int y,int n)
    : diff_x(x),diff_y(y),num(n) {}
};

class Dice{
  int top;
  int left;
  int right;
  int bottom;
  int front;
  int rear;
public:
  Dice(){
    top = -1;
    front = -1;
    left = -1;
    bottom = -1;
    right = -1;
    rear = -1;
  }
  void print(){
    printf("top:%d\n",top);
    printf("front:%d\n",front);
    printf("left:%d\n",left);
    printf("bottom:%d\n",bottom);
    printf("right:%d\n",right);
    printf("rear:%d\n",rear);
  }
  bool check(){
    if(left + right == 7
       && top + bottom == 7 
       && front + rear == 7) return true;
    return false;
  }
  void rotateDice(string dir){
    if(dir == "north"){
      //top2fr
      //fr2bot
      //bot2rear
      //rear2top
 
      int tmp_front = top;
      int tmp_bottom = front;
      int tmp_rear = bottom;
      int tmp_top = rear;
 
      front = tmp_front;
      bottom = tmp_bottom;
      rear = tmp_rear;
      top = tmp_top;
    }
 
    else if(dir == "south"){
      //top2fr
      //fr2bot
      //bot2rear
      //rear2top
 
      int tmp_front = bottom;
      int tmp_bottom = rear;
      int tmp_rear = top;
      int tmp_top = front;
 
      front = tmp_front;
      bottom = tmp_bottom;
      rear = tmp_rear;
      top = tmp_top;
    }
    else if(dir == "west"){
      int tmp_bottom = left;
      int tmp_top = right;
      int tmp_left = top;
      int tmp_right = bottom;
 
      bottom = tmp_bottom;
      top = tmp_top;
      left = tmp_left;
      right = tmp_right;
    }
 
    else if(dir == "east"){
      int tmp_bottom = right;
      int tmp_top = left;
      int tmp_left = bottom;
      int tmp_right = top;
 
      bottom = tmp_bottom;
      top = tmp_top;
      left = tmp_left;
      right = tmp_right;
    }
  }
 
  int tellTop() const{
    return top;
  }
  void writeTop(int t) {
    top = t;
  }
};

int stage[5][5];
bool visited[5][5];
const string dir[] = {"south","west","north","east"};
void dfs(int sx,int sy,Dice& d){
  d.writeTop(stage[sy][sx]);
  visited[sy][sx] = true;
  for(int i = 0; i < 4; i++){
    int dx = sx + tx[i];
    int dy = sy + ty[i];
    
    if(dx >= 5 || dx < 0 || dy >= 5 || dy < 0) continue;
    if(!visited[dy][dx] && stage[dy][dx] != 0){
      d.rotateDice(dir[i]);
      dfs(dx,dy,d);
      d.rotateDice(dir[(i + 2) % 4]);
    }
  }
}

int main(){
  int N;
  while(~scanf("%d",&N)){
    for(int i = 0; i < N; i++){

      int start_x = -1;
      int start_y = -1;
      int start_num = -1;
      for(int y = 0; y < 5; y++){
	for(int x = 0; x < 5; x++){
	  scanf("%d",&stage[y][x]);
	  if(stage[y][x] != 0){
	    start_x = x;
	    start_y = y;
	    start_num = stage[y][x];
	  }
	}
      }
      memset(visited,false,sizeof(visited));
      Dice dice;
      dfs(start_x,start_y,dice);
      printf("%s\n",dice.check() ? "true" : "false");
    }
  }
}
