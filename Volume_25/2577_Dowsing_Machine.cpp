#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f

#include <iostream>
#include <cstdio>
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
typedef pair <int,P> PP;
  
static const double EPS = 1e-8;
  
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};

bool inside_mark(int flag[51][51],
		 int cx,int cy,int range){
  int tmp_flag[51][51];
  memcpy(tmp_flag,flag,sizeof(int)*51*51);
  
  for(int y=cy-range;y<=cy+range;y++){
    for(int x=cx-range;x<=cx+range;x++){
      if(y < 0 || x < 0 || y > 50 || x > 50) continue;
      if(tmp_flag[y][x] == 0){
	tmp_flag[y][x] = 1;
      }
      else if(tmp_flag[y][x] == -1){
	return false;
      }
    }
  }

  for(int y=0;y<50;y++){
    for(int x=0;x<50;x++){
      if(y >= cy-range && y <= cy+range
      && x >= cx-range && x <= cx+range){
	continue;
      }

      if(tmp_flag[y][x] == 0){
	tmp_flag[y][x] = -1;
      }
      else if(tmp_flag[y][x] == 1){
	return false;
      }
    }
  }

  memcpy(flag,tmp_flag,sizeof(int)*51*51);
  return true;
}

bool outside_mark(int flag[51][51],
		  int cx,int cy,int range){
  int tmp_flag[51][51];
  memcpy(tmp_flag,flag,sizeof(int)*51*51);
  
  for(int y=cy-range;y<=cy+range;y++){
    for(int x=cx-range;x<=cx+range;x++){
      if(y < 0 || x < 0 || y > 50 || x > 50) continue;
      if(tmp_flag[y][x] == 0){
	tmp_flag[y][x] = -1;
      }
      else if(tmp_flag[y][x] == 1){
	return false;
      }
    }
  }

  for(int y=0;y<50;y++){
    for(int x=0;x<50;x++){
      if(y >= cy-range && y <= cy+range
      && x >= cx-range && x <= cx+range){
	continue;
      }

      if(tmp_flag[y][x] == 0){
	tmp_flag[y][x] = 1;
      }
      else if(tmp_flag[y][x] == -1){
	return false;
      }
    }
  }

  memcpy(flag,tmp_flag,sizeof(int)*51*51);
  return true;
}

int main(){
  int h,w,d_range,total_responses;
  while(~scanf("%d %d %d %d",&h,&w,&d_range,&total_responses)){
    char stage[51][51];

    int d_x,d_y;
    for(int y=0;y<h;y++){
      char line[256];
      scanf("%s",line);
      for(int x=0;x<w;x++){
	stage[y][x] = line[x];
	if(line[x] == 'D'){
	  d_x = x;
	  d_y = y;
	}
      }
    }

    int r[101];
    r[0] = 0;
    for(int d_idx=1;d_idx<=d_range;d_idx++){
      int distance;
      scanf("%d",&distance);
      r[d_idx] = distance;
    }

    bool is_broken = false;
    int flag[51][51];
    memset(flag,0,sizeof(flag));

    for(int response_idx=0;response_idx<total_responses;response_idx++){
      int x,y,s;
      scanf("%d %d %d",&x,&y,&s);
      if(s == d_range){
	bool is_valid = outside_mark(flag,x,y,r[s]);
	printf("outside : %d valid : %d\n",r[s],is_valid);
      }
      else if(s < d_range){
	bool is_valid = inside_mark(flag,x,y,r[s]);
	printf("inside : %d valid : %d\n",r[s],is_valid);
      }
    }
    for(int y=0;y<h;y++){
      for(int x=0;x<w;x++){
	printf("%02d ",flag[y][x]);
      }
      printf("\n");
    }
  }
}
