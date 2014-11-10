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

int main(){
  int n;
  bool is_first = true;
  while(~scanf("%d",&n)){
    if(n == 0) break;
    vector<Rect> pages;
    for(int i = 0; i < n; i++){
      int lx,ly;
      int rx,ry;
      scanf("%d %d %d %d",&rx,&ry,&lx,&ly);
      pages.push_back(Rect(rx,ry,lx,ly,i));
    }

    bool used[10];
    memset(used,false,sizeof(used));

    int order[10] = {};
    int idx = 1;
    priority_queue<Rect,vector<Rect>,greater<Rect> > candidates;

    int lower_bound = 1000;
    int border_x = 1000;
    // int last_rx = -1;
    for(int round = 0; round < 2*n; round++){
      for(int i = 0; i < n; i++){
	if(used[i]) continue;
	if(lower_bound < pages[i].ly) continue;
	if(pages[i].lx > border_x) continue;
	// if(pages[i].rx < last_rx) continue;
	candidates.push(pages[i]);
      }
      if(candidates.empty()){
	lower_bound = 1000;
	for(int i = 0; i < n; i++){
	  if(used[i]) continue;
	  if(pages[i].lx > border_x) continue;
	  // if(pages[i].rx < last_rx) continue;
	  candidates.push(pages[i]);
	}
      }

      if(candidates.empty()) break;

      Rect last = candidates.top();
      candidates.pop();

      while(!candidates.empty()) candidates.pop();
      // printf("border:%d id:%d lower:%d\n",border_x,last.id,lower_bound);
      order[last.id] = idx++;
      used[last.id] = true;

      // last_rx = last.rx;
      border_x = 1000;
      lower_bound = last.ly;
      // cout << "last:" << last.id<< endl;
      for(int i = 0; i < n; i++){
	if(pages[i].ly > last.ly && pages[i].ry < last.ly
	   && pages[i].rx >= last.lx){
	  border_x = min(pages[i].rx,border_x);
	}
      }
    }

    if(!is_first) {
      printf("\n");
    }
    for(int i = 0;i<n;i++){
      printf("%d\n",order[i]);
    }
    is_first = false;
  }
}
