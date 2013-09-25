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

int main(){
  int N;
  while(~scanf("%d",&N)){
    for(int stage_idx = 0; stage_idx < N; stage_idx++){
      int H,W;
      char stage[50*50];
      memset(stage,'.',sizeof(stage));
      
      scanf("%d %d",&H,&W);
      map<char,Belongings> layer;
    
      for(int y=0;y<H;y++){
	char line[51];
	scanf("%s",line);
	for(int x=0;x<W;x++){
	  stage[y*W+x] = line[x];
	  //x:0->...
	  //y:0
	  //  |
	  //  v
	  //  .
	  //  upper
	  //left right
	  //  lower
	  char c = stage[y*W+x];
	  layer[c].left = min(layer[c].left,x);
	  layer[c].right = max(layer[c].right,x);
	  layer[c].upper = min(layer[c].upper,y);
	  layer[c].lower = max(layer[c].lower,y);
	}
      }

      string res = "SUSPICIOUS";
    
      vector<char> order;
      for(map<char,Belongings>::iterator it = layer.begin();
	  it != layer.end();
	  it++){
	order.push_back(it->first);
      }
      sort(order.begin(),order.end());
      char hypothesis[50*50];

      do{
	memset(hypothesis,'.',sizeof(hypothesis));

	for(int i=0;i<order.size();i++){
	  int c = order[i];
	  Belongings& it = layer[c];
	  for(int y=it.upper; y<=it.lower; y++){
	    for(int x=it.left; x<=it.right; x++){
	      hypothesis[y*W+x] = c;
	    }
	  }
	}

	if(strcmp(hypothesis,stage) == 0){
	  res = "SAFE";
	  break;
	}
      }while(next_permutation(order.begin(),order.end()));
      cout << res << "\n";
    }
  }
}
