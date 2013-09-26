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

class Belongings {
public:
  Belongings() : left(100),right(0),upper(100),lower(0){}
  int left,right,upper,lower;
};


bool check(char hypothesis[50][50],char stage[50][50],int W,int H){
  for(int y=0;y<H;y++){
    for(int x=0;x<W;x++){
      if(hypothesis[y][x] != stage[y][x]) return false;
    }
  }
  return true;
}

int main(){
  int N;
  while(~scanf("%d",&N)){
    for(int stage_idx = 0; stage_idx < N; stage_idx++){
      int H,W;
      
      scanf("%d %d",&H,&W);

      char stage[50][50];
      char hypothesis[50][50];

      memset(stage,'.',sizeof(stage));

      map<char,Belongings> layer;

      for(int y=0;y<H;y++){
	char line[51];
	scanf("%s",line);
	for(int x=0;x<W;x++){
	  stage[y][x] = line[x];
	  if(line[x] == '.') continue;
	  //x:0->...
	  //y:0
	  //  |
	  //  v
	  //  .
	  //  upper
	  //left right
	  //  lower
	  Belongings& be = layer[stage[y][x]];
	  be.left = min(be.left,x);
	  be.right = max(be.right,x);
	  be.upper = min(be.upper,y);
	  be.lower = max(be.lower,y);
	}
      }

      bool is_safe = false;

      vector<char> order;
      for(map<char,Belongings>::iterator it = layer.begin();
	  it != layer.end();
	  it++){
	order.push_back(it->first);
      }
      sort(order.begin(),order.end());


      do{
	memset(hypothesis,'.',sizeof(hypothesis));

	for(int i=0;i<order.size();i++){
	  char c = order[i];
	  Belongings& be = layer[c];
	  for(int y=be.upper; y<=be.lower; y++){
	    for(int x=be.left; x<=be.right; x++){
	      hypothesis[y][x] = c;
	    }
	  }
	}

	if(check(hypothesis,stage,W,H)){
	  is_safe = true;
	  break;
	}
      }while(next_permutation(order.begin(),order.end()));
      printf("%s\n",is_safe ? "SAFE" : "SUSPICIOUS");
      
    }
  }
  return 0;
}
