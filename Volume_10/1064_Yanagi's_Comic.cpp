#define _USE_MATH_DEFINES
#define INF 100000000
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
#include <cstdio>

using namespace std;

typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P> PP;

static const double EPS = 1e-8;

const int tx[] = {0,1,0,-1};
const int ty[] = {-1,0,1,0};

struct Rect {
  int lx,ly;
  int rx,ry;
  int id;
  Rect(int rx,int ry,int lx,int ly,int id) :
    rx(rx),ry(ry),lx(lx),ly(ly),id(id) {}
  Rect() {}

  Rect(const Rect& r) {
    lx = r.lx;
    ly = r.ly;
    rx = r.rx;
    ry = r.ry;
    id = r.id;
  }

  bool operator>(const Rect& r) const {
    if(rx == r.rx){
      return ry > r.ry;
    }
    return rx > r.rx;
  }
};

bool used[10];
int order[10];
int idx;
int total_pages;
void dfs(int border_x,int lower_bound,const vector<Rect>& pages){
  for(int round = 0; round < total_pages; round++){
    priority_queue<Rect,vector<Rect>,greater<Rect> > candidates;
    
    for(int i = 0; i < total_pages; i++){
      if(used[i]) continue;
      if(lower_bound < pages[i].ly) continue;
      if(pages[i].lx > border_x) continue;
      candidates.push(pages[i]);
    }
    
    if(candidates.empty()) return;
    
    Rect last = candidates.top();
    candidates.pop();
    
    order[last.id] = idx++;
    used[last.id] = true;
    
    int next_lower_bound = last.ly;
    int next_border_x = 1000;
    for(int i = 0; i < total_pages; i++){
      if(pages[i].ly > last.ly && pages[i].ry < last.ly
	 && pages[i].rx >= last.lx){
	next_border_x = min(pages[i].rx,next_border_x);
      }
    }
    dfs(next_border_x,next_lower_bound,pages);
  }
}

int main(){
  bool is_first = true;
  while(~scanf("%d",&total_pages)){
    if(total_pages == 0) break;
    vector<Rect> pages;
    for(int i = 0; i < total_pages; i++){
      int lx,ly;
      int rx,ry;
      scanf("%d %d %d %d",&rx,&ry,&lx,&ly);
      pages.push_back(Rect(rx,ry,lx,ly,i));
    }


    memset(used,false,sizeof(used));
    memset(order,0,sizeof(order));
    idx = 1;
    dfs(1000,1000,pages);

    if(!is_first) {
      printf("\n");
    }
    for(int i = 0;i<total_pages;i++){
      printf("%d\n",order[i]);
    }
    is_first = false;
  }
}
