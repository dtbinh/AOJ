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
 
const int tx[] = {0,1,1,0};
const int ty[] = {0,0,1,1};
 
static const double EPS = 1e-10;

struct Point {
  int x;
  int y;
  Point(int _x,int _y) : x(_x) , y(_y) {}
  bool operator ==(const Point& p) const{
    return (x == p.x && y == p.y);
  }
};

int main(){
  int H,W;

  while(~scanf("%d %d",&H,&W)){
    char stage[500][500];
    map<char,vector<Point> > tiles;
    for(int y=0;y<H;y++){
      string line;
      cin >> line;
      for(int x=0;x<W;x++){
	stage[y][x] = line[x];
	if(stage[y][x] != '.'){
	  tiles[stage[y][x]].push_back(Point(x,y));
	}
      }
    }

    int erased_count = 0;
    bool erased[256];
    memset(erased,false,sizeof(erased));
    erased['.'] = true;

    for(int round=0;round <= 500*500; round++){

      bool update = false;
      for(int target_char = 'A'; target_char <= 'Z'; target_char++){
	if(erased[target_char]) continue;
	if(tiles.find(target_char) == tiles.end()) continue;
	
	Point p1(tiles[target_char][0].x,tiles[target_char][0].y);
	Point p2(tiles[target_char][1].x,tiles[target_char][1].y);

	bool isok = true;
	if(p1.x == p2.x){
	  if(abs(p1.y-p2.y) == 1) isok = false;

	  int x = p1.x;
	  for(int y=min(p1.y,p2.y)+1;y<max(p1.y,p2.y);y++){
	    if(!erased[stage[y][x]]){
	      isok = false;
	      break;
	    }
	  }
	}
	else if(p1.y==p2.y){
	  if(abs(p1.x-p2.x) == 1) isok = false;

	  int y = p1.y;
	  for(int x=min(p1.x,p2.x)+1;x<max(p1.x,p2.x);x++){
	    if(!erased[stage[y][x]]){
	      isok = false;
	      break;
	    }
	  }
	}
	else{

	  vector<Point> medium;
	  bool can_found = false;
	  for(int i=0;i<tiles[target_char].size();i++){
	    for(int j=0;j<tiles[target_char].size();j++){
	      Point mid(tiles[target_char][i].x,tiles[target_char][j].y);
	      
	      if(mid == p1 || mid == p2) continue;
	      if(!erased[stage[mid.y][mid.x]]) continue;

	      //target p1.x,p1.y
	      int flag1 = 0;
	      for(int x = min(mid.x,p1.x);x <= max(mid.x,p1.x); x++){
		if(Point(x,p1.y) == p1) continue;
		if(!erased[stage[mid.y][x]]) flag1 |= 1;
	      }

	      for(int y = min(mid.y,p1.y); y<= max(mid.y,p1.y) ; y++){
		if(Point(p1.x,y) == p1) continue;
		if(!erased[stage[y][mid.x]]) flag1 |= (1<<1);
	      }

	      //target x2,y2
	      int flag2 = 0;
	      for(int x = min(mid.x,p2.x);x <= max(mid.x,p2.x); x++){
		if(Point(x,p2.y) == p2) continue;
		if(!erased[stage[mid.y][x]]) flag2 |= 1;
	      }

	      for(int y = min(mid.y,p2.y) ;y <= max(mid.y,p2.y) ; y++){
		if(Point(p2.x,y) == p2) continue;
		if(!erased[stage[y][mid.x]]) flag2 |= (1<<1);
	      }

	      if(flag1 == 0 && flag2 == 0){
		can_found = true;
	      }
	    }
	  }

	  if(!can_found){
	    isok = false;
	  }
	}
	if(isok){
	  update = true;
	  erased[target_char] = true;
	  erased_count++;
	}
      }

      if(!update) break;
    }
    printf("%d\n",erased_count*2);
  }
}
