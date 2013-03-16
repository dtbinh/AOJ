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
 
int tx[] = {1,-1};
 
static const double EPS = 1e-8;
 
void EraseBlock(char stage[31][31],bool marked_stage[31][31],int h,int w,int n){
  for(int y=0;y<h;y++){
    for(int x=0;x<w;x++){
      if(marked_stage[y][x]){
	stage[y][x] = '.';
      }
    }
  }
}
 
void DropBlock(char stage[31][31],int h,int w,int n){
  for(int x=0;x<w;x++){
    queue<char> blocks;
    for(int y=h-1;y>=0;y--){
      if(stage[y][x] == '.') continue;
      blocks.push(stage[y][x]);
    }
    for(int y=h-1;y>=0;y--){
      if(!blocks.empty()){
	stage[y][x] = blocks.front();
	blocks.pop();
      }
      else{
	stage[y][x] = '.';
      }
    }
  }
}
 
bool isClearStage(char stage[31][31],int h,int w){
  for(int y=0;y<h;y++){
    for(int x=0;x<w;x++){
      if(stage[y][x] != '.'){
	return false;
      }
    }
  }
  return true;
}
 
 
bool MarkVirtical(char stage[31][31],bool marked_stage[31][31],int sx,int sy,int h,int w,int n){
 
  bool tmp[31][31];
  memcpy(tmp,marked_stage,sizeof(bool)*31*31);
 
  char start_block = stage[sy][sx];
  int ey=sy;
  for(int y=sy;y<h;y++){
    if(start_block == stage[y][sx]){
      marked_stage[y][sx] = true;
      ey = y;
    }
    else{       
      break;
    }
  }
 
  if(ey >= sy + n - 1) return true;
 
  memcpy(marked_stage,tmp,sizeof(bool)*31*31);
  return false;
}
 
bool MarkHorizonal(char stage[31][31],bool marked_stage[31][31],int sx,int sy,int h,int w,int n){
 
  bool tmp[31][31];
  memcpy(tmp,marked_stage,sizeof(bool)*31*31);
 
  char start_block = stage[sy][sx];
  int ex=sx;
  for(int x=sx;x<w;x++){
    if(start_block == stage[sy][x]){
      marked_stage[sy][x] = true;
      ex = x;
    }
    else{
      break;
    }
  }
 
  if(ex >= sx + n - 1) return true;
 
  memcpy(marked_stage,tmp,sizeof(bool)*31*31);
  return false;
}
bool MarkToEraseBlock(char stage[31][31],bool marked_stage[31][31],int h,int w,int n){
  memset(marked_stage,0,sizeof(char)*31*31);
  bool isMarked = false;
  for(int sy=0;sy<h;sy++){
    for(int sx=0;sx<w;sx++){
      if(stage[sy][sx] == '.') continue;
      if(sy+n <= h) isMarked |= MarkVirtical(stage,marked_stage,sx,sy,h,w,n);
      if(sx+n <= w) isMarked |= MarkHorizonal(stage,marked_stage,sx,sy,h,w,n);
    }
  }
 
  return isMarked;
}
 
int main(){
  int h,w,n;
 
  char stage[31][31];
  memset(stage,'\0',sizeof(stage));
  while(~scanf("%d %d %d",&h,&w,&n)){
    for(int y=0;y<h;y++){
      char buf[31];
      scanf("%s",buf);
      for(int x=0;x<w;x++){
	stage[y][x] = buf[x];
      }
    }
 
    bool isok = false;
    char tmp_stage[31][31];
    bool marked_stage[31][31];
 
    //swap blocks
    for(int y1=0;y1<h;y1++){
      for(int x1=0;x1<w;x1++){
	for(int i=0;i<2;i++){
	  int x2 = tx[i] + x1;
	  int y2 = y1;
	  if(x2 < 0 || y2 < 0 || x2 >= w || y2 >= h) continue;
 
	  memcpy(tmp_stage,stage,sizeof(char)*31*31);
 
	  swap(stage[y1][x1],stage[y2][x2]);
 
	  DropBlock(stage,h,w,n);
	  while(MarkToEraseBlock(stage,marked_stage,h,w,n)){
	    EraseBlock(stage,marked_stage,h,w,n);
	    DropBlock(stage,h,w,n);
	  }
 
	  if(isClearStage(stage,h,w)){
	    isok = true;
	    goto found;
	  }
 
	  memcpy(stage,tmp_stage,sizeof(char)*31*31);
	}
      }
    }
  found:;
 
    printf("%s\n",isok ? "YES" : "NO"); 
  }
}
