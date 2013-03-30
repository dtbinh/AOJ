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
 
int tx[] = {0,1,0,-1};//URDL
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

class State{
public:
  int mDir;
  int mMemory;
  int mX;
  int mY;
  State(int dir,int memory,int x,int y) : mDir(dir),mMemory(memory),mX(x),mY(y) {}
  State(int memory,int x,int y) : mMemory(memory),mX(x),mY(y) {}
};
struct DIR_MEM{
  int mDirBits;
  int mMemory;
};

struct DIR_MEM ReadCommand(char _command,int _memory,int _dir){
  int memory=_memory;
  int dir=(1<<_dir);
  switch(_command){
  case '<':// '<' … 実行の向きを左にする．
    dir = (1<<3);//U:=0,R:=1,D:=2,L:=3
    break;
  case '>':// '>' … 実行の向きを右にする．
    dir = (1<<1);//U:=0,R:=1,D:=2,L:=3
    break;
  case '^':// '^' … 実行の向きを上にする
    dir = (1<<0);//U:=0,R:=1,D:=2,L:=3
    break;
  case 'v':// 'v' … 実行の向きを下にする．
    dir = (1<<2);//U:=0,R:=1,D:=2,L:=3
    break;
  case '_':// '_' … メモリの値が 0 ならば実行の向きを右に，そうでなければ左にする．
    dir = (_memory == 0 ? (1<<1) : (1<<3));//U:=0,R:=1,D:=2,L:=3
    break;
  case '|':// '|' … メモリの値が 0 ならば実行の向きを下に，そうでなければ上にする．
    dir = (_memory == 0 ? (1<<2) : (1<<0));//U:=0,R:=1,D:=2,L:=3
    break;
  case '?':// '?' … 実行の向きが上下左右のいずれかにランダムに等確率で変更される
    dir = (1<<4) - 1;
    break;
  case '.':// '.' … 何もしない．
    break;
  case '@':// '@' … プログラムの実行を停止する．
    dir = 0;
    break;
  case '0':case '1':case '2':// '0' - '9' … メモリの値を指定の数値にする．
  case '3':case '4':case '5':
  case '6':case '7':case '8':case '9':
    memory = _command - '0';
    break;
  case '+':// '+' … メモリの値に 1 を加える，ただし値が 15 だった場合 0 にする．
    memory = (_memory == 15 ? 0 : _memory + 1);
    break;
  case '-':// '-' … メモリの値から 1 を引く，ただし値が 0 だった場合 15 にする．
    memory = (_memory == 0 ? 15 : _memory - 1);
    break;
  default:
    break;
  }

  struct DIR_MEM dm = {dir,memory};
  return dm;
}


bool isClear(bool visited[21][21][16][4],const vector<P>& goals){
  if(goals.size() == 0) return false;
  for(int i = 0; i < goals.size();i++){
    for(int mem=0;mem<=15;mem++){
      for(int dir=0;dir<4;dir++){
	int gx = goals[i].first;
	int gy = goals[i].second;
	if(visited[gx][gy][mem][dir]) return true;
      }
    }
  }
  return false;
}

int main(){
  int H,W;
  int commands[21][21];
  bool visited[21][21][16][4];

  while(~scanf("%d %d",&H,&W)){
    memset(visited,0,sizeof(visited));

    vector<P> goals;
    for(int y=0;y<H;y++){
      char buf[21];
      scanf("%s",buf);
      for(int x=0;x<W;x++){
	commands[y][x] = buf[x];
	if(buf[x] == '@'){
	  goals.push_back(P(x,y));
	}
      }
    }
    
    queue<State> que;
    
    //dir,memory,x,y
    //U:=0,R:=1,D:=2,L:=3
    que.push(State(1,0,0,0));

    visited[0][0][0][1] = true;

    while(!que.empty()){
      State s = que.front();
      que.pop();
      int x = s.mX;
      int y = s.mY;
      char command = commands[y][x];
      struct DIR_MEM next_dir_mem = ReadCommand(command,s.mMemory,s.mDir);
      // printf("mem %d x:%d y:%d command:%c\n",s.mMemory,x,y,command);

      for(int dir=0;dir<4;dir++){
	if(!(next_dir_mem.mDirBits & (1<<dir))) continue;
	int dx = (tx[dir] + x + W) % W;
	int dy = (ty[dir] + y + H) % H;

	if(visited[dx][dy][next_dir_mem.mMemory][dir]) continue;

	//dir,memory,x,y
	State next(dir,next_dir_mem.mMemory,dx,dy);

	//[x][y][memory]
	visited[dx][dy][next_dir_mem.mMemory][dir] = true;

	que.push(next);
      }
    }
    // printf("%d %d\n",gx,gy);
    printf("%s\n",isClear(visited,goals) ? "YES" : "NO");
  }
}
