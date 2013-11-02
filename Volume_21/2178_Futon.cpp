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

class Cell{
public:
  int id;
  int x;
  int y;
  bool has_head;
  Cell(){}
  Cell(int _id,int _x,int _y) : id(_id), x(_x), y(_y),has_head(false) {}
};

class Bed{
public:
  Cell head;
  Cell tail;
  Bed() {}
  Bed (Cell _c1, Cell _c2) : head(_c1),tail(_c2){}
};

void dfs(map<P,Bed*>& stage, map<P,Bed*>::iterator it, bool used[20000]){
  int id = it->second->head.id;
  used[id] = true;

  int x = it->second->head.x;
  int y = it->second->head.y;

  int next_x = it->second->tail.x;
  int next_y = it->second->tail.y;

  map<P,Bed*>::iterator dst_it;
  for(int i=0;i<4;i++){
    int dx = x + tx[i];
    int dy = y + ty[i];
    if((dst_it = stage.find(P(dx,dy))) != stage.end()){
      dfs(stage,dst_it,used);
    }
  }
  for(int i=0;i<4;i++){
    int dx = next_x + tx[i];
    int dy = next_y + ty[i];
    if((dst_it = stage.find(P(dx,dy))) != stage.end()){
      dfs(stage,dst_it,used);
    }
  }
}

int main(){
  int total_beds;
  while(~scanf("%d",&total_beds)){
    if(total_beds == 0) break;

    map<P,Bed*> stage;
    bool used[20000];
    memset(used,false,sizeof(used));
    
    for(int bed_idx = 0; bed_idx < total_beds; bed_idx++){
      int x,y;
      char dir[2];
      scanf("%d %d %s",&x,&y,dir);

      int dx = 0;
      int dy = 0;
      if(dir[0] == 'x'){
	dx = x+1;
	dy = y;
      }
      else if(dir[0] == 'y'){
	dx = x;
	dy = y+1;
      }

      Cell head(bed_idx,x,y);
      Cell tail(bed_idx,dx,dy);

      Bed bed(head,tail);
      stage[P(x,y)] = &bed;
      stage[P(dx,dy)] = &bed;
    }

    for(map<P,Bed*>::iterator it = stage.begin();
	it != stage.end();
	it++){
      int id = it->second->head.id;
      if(used[id]) continue;
      
      dfs(stage,it,used);
    }
  }
}
