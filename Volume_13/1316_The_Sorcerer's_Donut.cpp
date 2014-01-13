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
 
const static int tx[] = {0,1,1,1,0,-1,-1,-1};
const static int ty[] = {-1,-1,0,1,1,1,0,-1};

int main(){
  int H,W;
  while(~scanf("%d %d",&H,&W)){
    if(H==0 && W==0) break;

    char line[32];
    char stage[10][20];

    for(int y=0;y<H;y++){
      scanf("%s",line);
      for(int x=0;x<W;x++){
	stage[y][x] = line[x];
      }
    }

    string res = "";
    vector<string> spells;
    map<string,int> freq;
    
    for(int y=0;y<H;y++){
      for(int x=0;x<W;x++){
	int sx = x;
	int sy = y;

	for(int dir=0;dir<8;dir++){
	  string spell = "";
	  spell.push_back(stage[sy][sx]);
	  int dx = sx;
	  int dy = sy;
	  for(int i=0;i<1000;i++){
	    dx = tx[dir] + dx;
	    dy = ty[dir] + dy;
	    if(dx < 0) dx = W-1;
	    if(dx >= W) dx = 0;
	    if(dy < 0) dy = H-1;
	    if(dy >= H) dy = 0;

	    if(dy == sy && dx == sx) break;
	    spell.push_back(stage[dy][dx]);
	    freq[spell]++;
	    if(freq[spell] >= 2){
	      if(res.size() < spell.size()
		 || (res.size() == spell.size() && res > spell)){
		res = spell;
	      }
	    }
	  }
	  spells.push_back(spell);
	  // cout << spell << endl;
	}
      }
    }
    printf("%s\n",res != "" ? res.c_str() : "0");
  }
}
