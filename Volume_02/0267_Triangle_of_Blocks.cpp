#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
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
typedef pair<int,string> P;

bool is_triangle(int blocks[100000],int W){

  bool is_first = true;
  for(int x=0;x<W;x++){
    if(blocks[x] == 0) continue;
    if(blocks[x] != 0){
      if(is_first){
	if(blocks[x] != 1) return false;
	is_first = false;
      }

      int target = -1;
      for(int dx=x+1;dx<W;dx++){
	if(blocks[dx] != 0){
	  target = dx;
	  break;
	}
      }

      if(target == -1) continue;
      if(blocks[x] + 1 != blocks[target]) return false;
    }
  }

  return true;
}

int main(){
  int W;
  while(~scanf("%d",&W)){
    if(W == 0) break;
    int blocks[100000];
    memset(blocks,0,sizeof(blocks));
    for(int x=0;x<W;x++){
      int block;
      scanf("%d",&block);
      blocks[x] = block;
    }

    int res = -1;
    bool isok = true;
    int nextW = W;
    for(int round = 0; round <= 10000;round++){
      if(is_triangle(blocks,nextW)){
	res = round;
	break;
      }

      int width = 0;
      for(int x=0;x<nextW;x++){
	if(blocks[x] > 0){
	  blocks[x]--;
	  width++;
	}
      }

      blocks[nextW++] = width;
    }

    printf("%d\n",res);
  }
}
