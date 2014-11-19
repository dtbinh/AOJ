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

class Field {
private:
  int _stage[5][5];
  bool _marked[5][5];
  int _score[6];
  int compute_block_score(){
    int res = 0;
    for(int y = 0; y < 5; y++){
      for(int x = 0; x < 5; x++){
	if(_marked[y][x]) {
	  res += _score[_stage[y][x]];
	}
      }
    }
    return res;
  }
public:
  Field(int stage[5][5],int score[6]){
    memcpy(_stage,stage,sizeof(int)*5*5);
    memcpy(_score,score,sizeof(int)*6);
  }
  bool mark(){
    bool has_mark = false;
    memset(_marked,false,sizeof(_marked));
    for(int y = 0; y < 5; y++){
      for(int x = 0; x < 5; x++){
	//horizontal
	int h_count = 1;
	for(int dx = x; dx + 1 < 5; dx++){
	  if(_stage[y][dx] != 0
	     && _stage[y][dx] == _stage[y][dx+1]) h_count++;
	  else{
	    break;
	  }
	}
	if(h_count >= 3){
	  for(int dx = x; dx + 1 < 5; dx++){
	    if(h_count-- <= 0) break;
	    _marked[y][dx] = true;
	    has_mark = true;
	  }
	}

	//vertical
	int v_count = 1;
	for(int dy = y; dy + 1 < 5; dy++){
	  if(_stage[dy][x] != 0 
	     && _stage[dy][x] == _stage[dy + 1][x]) v_count++;
	  else{
	    break;
	  }
	}
	if(v_count >= 3){
	  for(int dy = y; dy + 1 < 5; dy++){
	    if(v_count-- <= 0) break;
	    _marked[dy][x] = true;
	    has_mark = true;
	  }
	}
      }
    }

    return has_mark;
  }

  void erase(){
    int next[5][5] = {};
    for(int x = 0; x < 5; x++){
      int pos = 4;
      for(int y = 4; y >= 0; y--){
	if(_marked[y][x]) continue;
	next[pos--][x] = _stage[y][x];
      }
    }
    memcpy(_stage,next,sizeof(int)*5*5);
  }

  int compute_score(){
    int bonus = 1;
    int sum = 0;
    while(mark()){
      sum += compute_block_score() * bonus;
      erase();
      bonus++;
    }
    return sum;
  }
};

int stage[5][5];
int score[6];

int dfs(int sx,int sy,int count){
  if(count <= 0) return Field(stage,score).compute_score();

  int res = 0;
  for(int i = 0; i < 4; i++){
    int dx = tx[i] + sx;
    int dy = ty[i] + sy;
    if(dx < 0 || dx >= 5 || dy < 0 || dy >= 5) continue;
    swap(stage[dy][dx],stage[sy][sx]);
    res = max(res,Field(stage,score).compute_score());
    res = max(res,dfs(dx,dy,count-1));
    swap(stage[dy][dx],stage[sy][sx]);
  }
  return res;
}
  
int main(){
  int move_limit;
  while(~scanf("%d",&move_limit)){
    if(move_limit == -1) break;

    for(int y = 0; y < 5; y++){
      for(int x = 0; x < 5; x++){
	scanf("%d",&stage[y][x]);
	stage[y][x];
      }
    }

    for(int i = 1; i <= 5; i++){
      scanf("%d",&score[i]);
    }

    int res = 0;
    for(int y = 0; y < 5; y++){
      for(int x = 0; x < 5; x++){
	res = max(res,dfs(x,y,move_limit));
      }
    }
    
    printf("%d\n",res);
  }
}
