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

void dfs(int sx,int sy,char stage[12][6],bool toErase[12][6],char color,int* count){
  if(toErase[sy][sx]) return;
  toErase[sy][sx] = true;
  (*count)++;
  for(int i=0;i<4;i++){
    int dx = sx + tx[i];
    int dy = sy + ty[i];
 
    if(dx < 0 || dx >= 6 
       || dy < 0 || dy >= 12) continue;
    if(stage[dy][dx] != color) continue;
         
    dfs(dx,dy,stage,toErase,color,count);
  }
}
 
bool markBlock(bool toErase[12][6],char stage[12][6]){
 
  bool res = false;
  for(int y=0;y<12;y++){
    for(int x=0;x<6;x++){
      if(stage[y][x] == '.'
	 || stage[y][x] == 'O') continue;
 
      if(!toErase[y][x]){
	char color = stage[y][x];
	int count = 0;
	bool tmp[12][6];
	memcpy(tmp,toErase,sizeof(bool)*12*6);
 
	dfs(x,y,stage,toErase,color,&count);
	if(count < 4){
	  memcpy(toErase,tmp,sizeof(bool)*12*6);
	}
	else{
	  res = true;
	}
      }
    }
  }
 
  return res;
}
 
void eraseBlock(bool toErase[12][6],char stage[12][6]){
  for(int x=0;x<6;x++){
    for(int y=0;y<12;y++){
      if(stage[y][x] == '.'){
	toErase[y][x] = true;
	continue;
      }
      if(stage[y][x] == 'O'){
	for(int i=0;i<4;i++){
	  int dx = x + tx[i];
	  int dy = y + ty[i];
	  if(dx < 0 || dx >= 6 
	     || dy < 0 || dy >= 12) continue;
	  if(toErase[dy][dx] == true
                        && stage[dy][dx] != '.'
	     && stage[dy][dx] != 'O'){
	    toErase[y][x] = true;
	  }
	}
      }
    }
  }
 
  char nextStage[12][6];
  for(int x=0;x<6;x++){
    queue<char> que; 
    for(int y=12-1;y>=0;y--){
      if(!toErase[y][x]){
	que.push(stage[y][x]);
      }
    }
 
    int idx = 12-1;
    while(!que.empty()){
      nextStage[idx][x] = que.front();
      que.pop();
      idx--;
    }
    while(idx >= 0){
      nextStage[idx][x] = '.';
      idx--;
    }
  }
 
  memcpy(stage,nextStage,sizeof(char)*12*6);
}
 
void printStage(char stage[12][6]){
  for(int y=0;y<12;y++){
    for(int x=0;x<6;x++){
      printf("%c",stage[y][x]);
    }
    printf("\n");
  }
  printf("\n");
}
 
int main(){
  int n;
 
  while(~scanf("%d",&n)){
    for(int i=0;i<n;i++){
      char stage[12][6];
      bool toErase[12][6];
      memset(toErase,0,sizeof(toErase));
 
      for(int y=0;y<12;y++){
	string str;
	cin >> str;
	for(int x=0;x<6;x++){
	  stage[y][x] = str[x];
	}
      }
 
      //printStage(stage);
      int res = 0;
      while(markBlock(toErase,stage)){
	eraseBlock(toErase,stage);
	memset(toErase,0,sizeof(toErase));
	res++;
	//printStage(stage);
      }
      printf("%d\n",res);
    }
  }
}
