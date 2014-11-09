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

    int order[10];
    int idx = 1;
    queue<Rect> candidates;
    for(int round = 0; round < n; round++){
      int min_rx = 1000;

      if(candidates.empty()){
	for(int i = 0; i < n; i++){
	  if(used[i]) continue;
	  if(pages[i].rx < min_rx){
	    while(!candidates.empty()) candidates.pop();
	    min_rx = pages[i].rx;
	    candidates.push(pages[i]);
	  }
	  else if(pages[i].rx == min_rx){
	    candidates.push(pages[i]);
	  }
	}
      }
	
      if(candidates.empty()) break;

      int min_ry = 1000; 
      int selected = -1;
      while(!candidates.empty()){
	Rect r = candidates.front();
	candidates.pop();
	if(used[r.id]) continue;
	if(r.ry < min_ry){
	  min_ry = r.ry;
	  selected = r.id;
	}
      }
      used[selected] = true;
      order[selected] = idx++;

      Rect last = pages[selected];
      int border_x = last.lx;
      bool visited[10];
      memset(visited,false,sizeof(visited));
      for(int round2 = 0; round2 < n; round2++){
	bool over = true;
	for(int i = 0; i < n; i++){
	  if(visited[i]) continue;
	  if(border_x != pages[i].rx) continue;
	  if(pages[i].ly != last.ly) continue;
	  // cout << "i" << i << "idx" << idx << endl;
	  // order[i] = idx++;
	  border_x = pages[i].lx;
	  visited[i] = true;
	}
	if(over) break;
      }
      for(int i = 0; i < n; i++){
	if(used[i]) continue;
	if(pages[i].lx <= border_x){
	  candidates.push(pages[i]);
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
