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

void bfs(int start_x,int start_y,vector<Face>& face){
  queue<P> que;
  bool visited[5][5];
  memset(visited,false,sizeof(visited));
  que.push(P(start_x,start_y));
  while(!que.empty()){
    P p = que.front();
    que.pop();
    visited[p.first][p.second] = true;
    for(int i = 0; i < 4; i++){
      int dx = p.first + tx[i];
      int dy = p.second + ty[i];
      if(dx >= 5 || dx < 0 || dy >= 5 || dy < 0) continue;
      if(visited[dx][dy]) continue;
      if(stage[dy][dx] != 0){
	face.push_back(Face(dx - start_x,dy - start_y,stage[dy][dx]));
	que.push(P(dx,dy));
      }
    }
  }
}

void face2dice(const vector<Face>& face,Dice& d){
  for(int i = 0; i < face.size(); i++){
    int diff_x = face[i].diff_x;
    int diff_y = face[i].diff_y;
    int num = face[i].num;
    printf("%d %d %d\n",diff_x,diff_y,num);
    string dir_x = "west";
    if(diff_x < 0) dir_x = "east";
    string dir_y = "north";
    if(diff_y < 0) dir_y = "south";

    for(int j = 0; j < abs(diff_x); j++){
      d.rotateDice(dir_x);
    }
    for(int j = 0; j < abs(diff_y); j++){
      d.rotateDice(dir_y);
    }
    d.writeTop(num);
    
    string back_x = "west";
    if(dir_x == "west") back_x = "east";
    string back_y = "south";
    if(dir_y == "south") back_y = "north";
    for(int j = 0; j < abs(diff_x); j++){
      d.rotateDice(back_x);
    }
    for(int j = 0; j < abs(diff_y); j++){
      d.rotateDice(back_y);
    }
    cout << "---------------------" << endl;
    d.print();
    cout << "---------------------" << endl;

  }
};

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
      vector<Face> face;
      face.push_back(Face(0,0,start_num));
      bfs(start_x,start_y,face);
      Dice dice;
      face2dice(face,dice);
      
      if(face.size() != 6 || !dice.check()){
	printf("false\n");
      }
      else{
	printf("true\n");
      }
    }
  }
}
