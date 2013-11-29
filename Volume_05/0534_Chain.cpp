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
  
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};

class Block{
public:
  int color;
  int size;
  Block(int _c,int _s) : color(_c),size(_s){}
};

int check_stage(deque<Block>& stage){

  int res = 0;
  int max_round = stage.size();
  for(int round=0;round<max_round;round++){
    bool update = false;
    res = 0;
    for(int i=0;i+1<stage.size();i++){
      if(stage[i].color == stage[i+1].color){
	Block b(stage[i].color,stage[i].size+stage[i+1].size);
	stage.erase(stage.begin()+i,stage.begin()+i+2);
	stage.insert(stage.begin()+i,b);
	i--;
	update = true;
      }
    }
    for(int i=0;i<stage.size();i++){
      res += stage[i].size;
      if(stage[i].size >= 4){
	stage.erase(stage.begin()+i);
	update = true;
      }
    }
    if(!update) break;
  }
  return res;
}

int main(){
  int n;
  while(~scanf("%d",&n)){
    if(n==0) break;

    deque<Block> stage;
    queue<int> que;
    int prev = -1;
    for(int i=0;i<n;i++){
      int color;
      scanf("%d",&color);

      if(i==0 || color == prev){
	que.push(color);
      }
      else{
	stage.push_back(Block(prev,que.size()));
	while(!que.empty()) que.pop();
	que.push(color);
      }
      prev = color;
    }

    if(!que.empty()){
      stage.push_back(Block(prev,que.size()));
    }

    int res = n;
    for(int i=0;i<stage.size();i++){
      if(stage[i].size != 1) continue;


      for(int color=1;color<=3;color++){
	if(stage[i].color == color) continue;

	deque<Block> tmp = stage;
	tmp[i].color = color;
	res = min(res,check_stage(tmp));
      }
    }

    printf("%d\n",res);
  }
}
