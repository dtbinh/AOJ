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
  bool has_leg;
  Cell(){}
  Cell(int _id,int _x,int _y) : id(_id), x(_x), y(_y),has_head(false),has_leg(false) {}
};

class Bed{
public:
  Cell head;
  Cell tail;
  bool has_head;

  Bed() {}
  Bed (Cell _c1, Cell _c2) : head(_c1),tail(_c2),has_head(false){}
  Cell* getCell(int x,int y){
    if(head.x == x && head.y == y){
      return &head;
    }

    else if(tail.x == x && tail.y == y){
      return &tail;
    }
  }

  Cell* getCellOtherSide(int x,int y){
    if(head.x == x && head.y == y){
      return &tail;
    }

    else if(tail.x == x && tail.y == y){
      return &head;
    }
  }

  bool is_used(){
    return (head.has_head || tail.has_head || head.has_leg || tail.has_leg);
  }

  bool is_same_bed(int x,int y){
    if((head.x == x && head.y == y) || (tail.x == x && tail.y == y)){
      return true;
    }
    return false;
  }
};

void dfs(map<P,Bed*>& stage, map<P,Bed*>::iterator it, bool used[20000]){
  int id = it->second->head.id;
  used[id] = true;

  int head_x = it->second->head.x;
  int head_y = it->second->head.y;
  bool is_head_leg = it->second->head.has_leg;
  bool is_head_head = it->second->head.has_head;

  int tail_x = it->second->tail.x;
  int tail_y = it->second->tail.y;
  bool is_tail_leg = it->second->tail.has_leg;
  bool is_tail_head = it->second->tail.has_head;

  map<P,Bed*>::iterator dst_bed;
  for(int i=0;i<4;i++){
    int dx = head_x + tx[i];
    int dy = head_y + ty[i];

    if(is_head_head){
      if((dst_bed = stage.find(P(dx,dy))) != stage.end()){
	if(dst_bed->second->is_used()) continue;

	dst_bed->second->getCell(dx,dy)->has_head = true;
	dst_bed->second->getCellOtherSide(dx,dy)->has_leg = true;
	// printf("x:%d y:%d %s\n",dx,dy,"h");
	dfs(stage,dst_bed,used);
      }
    }

    else if(is_head_leg){
      if((dst_bed = stage.find(P(dx,dy))) != stage.end()){
	if(dst_bed->second->is_used()) continue;

	dst_bed->second->getCell(dx,dy)->has_leg = true;
	dst_bed->second->getCellOtherSide(dx,dy)->has_head = true;
	// printf("x:%d y:%d %s\n",dx,dy,"l");
	dfs(stage,dst_bed,used);
      }
    }
  }
  for(int i=0;i<4;i++){
    int dx = tail_x + tx[i];
    int dy = tail_y + ty[i];
    
    if(is_tail_leg){
      if((dst_bed = stage.find(P(dx,dy))) != stage.end()){
	if(dst_bed->second->is_used()) continue;

	dst_bed->second->getCell(dx,dy)->has_leg = true;
	dst_bed->second->getCellOtherSide(dx,dy)->has_head = true;
	// printf("x:%d y:%d %s\n",dx,dy,"l");
	dfs(stage,dst_bed,used);
      }
    }

    else if(is_tail_head){
      if((dst_bed = stage.find(P(dx,dy))) != stage.end()){
	if(dst_bed->second->is_used()) continue;

	dst_bed->second->getCell(dx,dy)->has_head = true;
	dst_bed->second->getCellOtherSide(dx,dy)->has_leg = true;
	// printf("x:%d y:%d %s\n",dx,dy,"h");
	dfs(stage,dst_bed,used);
      }
    }
  }
}

bool checkStage(map<P,Bed*>& stage){
  for(map<P,Bed*>::iterator it = stage.begin();
    	it != stage.end();
    	it++){
    int id = it->second->head.id;

    int head_x = it->second->head.x;
    int head_y = it->second->head.y;
    bool is_head_leg = it->second->head.has_leg;
    bool is_head_head = it->second->head.has_head;

    int tail_x = it->second->tail.x;
    int tail_y = it->second->tail.y;
    bool is_tail_leg = it->second->tail.has_leg;
    bool is_tail_head = it->second->tail.has_head;

    map<P,Bed*>::iterator dst_bed;
    for(int i=0;i<4;i++){
      int dx = head_x + tx[i];
      int dy = head_y + ty[i];
      if(it->second->is_same_bed(dx,dy)) continue;
      if((dst_bed = stage.find(P(dx,dy))) != stage.end()){
	if(is_head_leg){
	  if(dst_bed->second->getCell(dx,dy)->has_head) return false;
	}
	else if(is_head_head){
	  if(dst_bed->second->getCell(dx,dy)->has_leg) return false;
	}
      }
    }

    for(int i=0;i<4;i++){
      int dx = tail_x + tx[i];
      int dy = tail_y + ty[i];
      if(it->second->is_same_bed(dx,dy)) continue;
      if((dst_bed = stage.find(P(dx,dy))) != stage.end()){
	if(is_tail_leg){
	  if(dst_bed->second->getCell(dx,dy)->has_head) return false;
	}
	else if(is_tail_head){
	  if(dst_bed->second->getCell(dx,dy)->has_leg) return false;
	}
      }
    }
  }
  return true;
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

      Bed* bed = new Bed(head,tail);

      stage[P(x,y)] = bed;
      stage[P(dx,dy)] = bed;
    }

    for(map<P,Bed*>::iterator it = stage.begin();
    	it != stage.end();
    	it++){
      int id = it->second->head.id;
      if(used[id]) continue;

      // printf("x:%d y:%d %s\n",it->second->head.x,it->second->head.y,"h");
      it->second->head.has_head = true;
      it->second->tail.has_leg = true;
      dfs(stage,it,used);
    }

    bool isok = checkStage(stage);
    printf("%s\n",isok ? "Yes" : "No");
  }
}
