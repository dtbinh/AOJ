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
 
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

char stage[4][4];
bool has_stamp[5][5];
bool left_right_stamp[5][5];
bool top_bottom_stamp[5][5];
bool corner_stamp[5][5];

map<ll,int> dp;

ll compute_hash(){
  ll res = 0;
  ll base = 1;
  for(int y = 0; y < 4; y++){
    for(int x = 0; x < 4; x++){
      ll num = 0; //stage[y][x] eq '.'
      if(stage[y][x] == 'R') num = 1;
      if(stage[y][x] == 'G') num = 2;
      if(stage[y][x] == 'B') num = 3;
      res += num;
      res *= base;
      base *= 5LL;
    }
  }
  return res;
}

ll generate_clear_hash(){
  ll res = 0;
  ll base = 1;
  for(int y = 0; y < 4; y++){
    for(int x = 0; x < 4; x++){
      res += 0;
      res *= base;
      base *= 5LL;
    }
  }
  return res;

}

bool is_clear(ll hash){
  return (hash == 0);
}

bool can_erase(int ly,int lx,int ry,int rx){
  int freq[256] = {};
  int colors = 0;
  for(int y = ly; y <= ry; y++){
    for(int x = ry; x <= rx; x++){
      if(stage[y][x] != '.' && 
	 freq[stage[y][x]]++ > 0) colors++;
      if(colors >= 2) return false;
    }
  }
  return true;
}

void erase(int ly,int lx,int ry,int rx){
  for(int y = ly; y <= ry; y++){
    for(int x = ly; x <= rx; x++){
      stage[y][x] = '.';
    }
  }
}

void dfs(int count){
  ll hash = compute_hash();

  if(dp.find(hash) != dp.end() 
     && dp[hash] <= count) return;
  dp[hash] = count;

  for(int ly=0;ly<4;ly++){
    for(int lx=0;lx<4;lx++){
      for(int ry=ly;ry<4;ry++){
	for(int rx=lx;rx<4;rx++){
	  //corner
	  if((lx == 0 && ly == 0)
	     || (lx == 0 && ly == 3)
	     || (rx == 3 && ry == 3)
	     || (rx == 3 && ry == 0)){
	    if(corner_stamp[ry - ly + 1][rx - lx + 1]){
	      if(can_erase(ly,lx,ry,rx)){
		char tmp[4][4];
		memcpy(tmp,stage,sizeof(char)*4*4);
		erase(ly,lx,ry,rx);
		dfs(count+1);
		memcpy(stage,tmp,sizeof(char)*4*4);
	      }
	    }
	  }

	  //left or right
	  else if(lx == 0 || rx == 3){
	    if(left_right_stamp[ry - ly + 1][rx - lx + 1]){
	      if(can_erase(ly,lx,ry,rx)){
		char tmp[4][4];
		memcpy(tmp,stage,sizeof(char)*4*4);
		erase(ly,lx,ry,rx);
		dfs(count+1);
		memcpy(stage,tmp,sizeof(char)*4*4);
	      }
	    }
	  }

	  //top or bottom
	  else if(ly == 0 || ry == 3){
	    if(top_bottom_stamp[ry - ly + 1][rx - lx + 1]){
	      if(can_erase(ly,lx,ry,rx)){
		char tmp[4][4];
		memcpy(tmp,stage,sizeof(char)*4*4);
		erase(ly,lx,ry,rx);
		dfs(count+1);
		memcpy(stage,tmp,sizeof(char)*4*4);
	      }
	    }
	  }

	  //center
	  else {
	    if(has_stamp[ry - ly + 1][rx - lx + 1]){
	      if(can_erase(ly,lx,ry,rx)){
		char tmp[4][4];
		memcpy(tmp,stage,sizeof(char)*4*4);
		erase(ly,lx,ry,rx);
		dfs(count+1);
		memcpy(stage,tmp,sizeof(char)*4*4);
	      }
	    }
	  }
	}
      }
    }
  }
}

int main(){
  int num_of_stamps;
  while(~scanf("%d",&num_of_stamps)){
    memset(has_stamp,false,sizeof(has_stamp));
    memset(top_bottom_stamp,false,sizeof(top_bottom_stamp));
    memset(left_right_stamp,false,sizeof(left_right_stamp));
    memset(corner_stamp,false,sizeof(corner_stamp));
    dp.clear();

    for(int stamp_i = 0; stamp_i < num_of_stamps; stamp_i++){
      int H,W;
      scanf("%d %d",&H,&W);
      has_stamp[H][W] = true;
    }

    for(int h = 4; h >= 1; h--){
      bool flag = false;
      for(int w = 4; w >= 1; w--){
	if(has_stamp[h][w]) flag = true;
	if(flag) left_right_stamp[h][w] = true;
	if(flag) corner_stamp[h][w] = true;
      }
    }

    for(int w = 4; w >= 1; w--){
      bool flag = false;
      for(int h = 4; h >= 1; h--){
	if(has_stamp[h][w]) flag = true;
	if(flag) top_bottom_stamp[h][w] = true;
	if(flag) corner_stamp[h][w] = true;
      }
    }
    
    for(int y = 0; y < 4; y++){
      char line[8];
      scanf("%s",line);
      for(int x = 0; x < 4; x++){
	stage[y][x] = line[x];
      }
    }

    dfs(0);
    ll hash = generate_clear_hash();
    printf("%d\n",dp[hash]);
  }
}
