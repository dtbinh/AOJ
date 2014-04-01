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

int w,h;

void mark_outside_false(bool is_treasure[51][51],
		 int cx,int cy,int range){
  for(int y=0;y<=h;y++){
    for(int x=0;x<=w;x++){
      if(y >= cy-range && y <= cy+range
	 && x >= cx-range && x <= cx+range){
  	continue;
      }

      is_treasure[y][x] = false;
    }
  }
}

void mark_inside_false(bool is_treasure[51][51],
		  int cx,int cy,int range){
  for(int y=cy-range;y<=cy+range;y++){
    for(int x=cx-range;x<=cx+range;x++){
      if(y < 0 || x < 0 || y >= h || x >= w) continue;
      is_treasure[y][x] = false;
    }
  }
}

void dfs(char stage[51][51],
	 bool visited[51][51],
	 int sx,int sy){
  visited[sy][sx] = true;
  for(int i=0;i<4;i++){
    int dx = sx + tx[i];
    int dy = sy + ty[i];
    if(dx < 0 || dy < 0 
       || dy >= h || dx >= w) continue;
    if(stage[dy][dx] == '#') continue;
    if(visited[dy][dx]) continue;

    dfs(stage,visited,dx,dy);
  }
}

int main(){
  int d_range,total_responses;
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

    bool visited[51][51];
    memset(visited,false,sizeof(visited));
    dfs(stage,visited,d_x,d_y);

    bool is_treasure[51][51];
    memset(is_treasure,true,sizeof(is_treasure));

    for(int y=0;y<h;y++){
      for(int x=0;x<w;x++){
	if(stage[y][x] == '#'){
	  is_treasure[y][x] = false;
	}
      }
    }


    for(int response_idx=0;response_idx<total_responses;response_idx++){
      int x,y,s;
      scanf("%d %d %d",&x,&y,&s);
      if(1<=s && s <= d_range -1){
	int inside = r[s];
	int outside = r[s+1];
	mark_outside_false(is_treasure,x,y,outside);
	mark_inside_false(is_treasure,x,y,inside);
      }
      else if(s == d_range){
	mark_inside_false(is_treasure,x,y,r[s]);
	// printf("x:%d y:%d outside : %d \n",x,y,r[s]);
      }
      else if(s == 0){
	mark_outside_false(is_treasure,x,y,r[1]);
	// printf("x:%d y:%d inside : %d \n",x,y,r[s]);
      }
    }
    
    bool has_treasure = false;
    bool has_missing = false;
    for(int y=0;y<h;y++){
      for(int x=0;x<w;x++){
	if(visited[y][x] && is_treasure[y][x]){
	  has_treasure = true;
	}
	if(!visited[y][x] && is_treasure[y][x]){
	  has_missing = true;
	}
      }
    }

    if(has_treasure && has_missing){
      cout << "Unknown" << endl;
    }
    else if(has_treasure && !has_missing){
      cout << "Yes" << endl;
    }
    else if(!has_treasure && has_missing){
      cout << "No" << endl;
    }
    else if(!has_treasure && !has_missing){
      cout << "Broken" << endl;
    }
  }
}
