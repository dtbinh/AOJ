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
 
const int tx[] = {+0,+1,+0,-1};
const int ty[] = {-1,+0,+1,+0};
 
static const double EPS = 1e-8;

int init_dic(int x,int y,
	    map<P,int>& dic){
  if(dic.find(P(x,y)) == dic.end()){
    int idx = dic.size();
    dic[P(x,y)] = idx;
  }
  return dic[P(x,y)];
}

void fill_dic(int W,int H,map<P,int>& dic){
  for(int x=0;x<=W;x++){
    for(int y=0;y<=H;y++){
      if(dic.find(P(x,y)) == dic.end()){
	dic[P(x,y)] = -1;
      }
    }
  }
}

class State{
public:
  int x;
  int y;
  int dir;
  int remaining;
  int cost;
  vector<char> route;
  State(int _x,int _y,int _dir,int _remaining,int _cost,const vector<char>& _r)
    : x(_x),y(_y),dir(_dir),remaining(_remaining),cost(_cost),route(_r) {}
  State(int _x,int _y,int _dir,int _remaining,int _cost)
    : x(_x),y(_y),dir(_dir),remaining(_remaining),cost(_cost) {}
  bool operator<(const State& s) const{
    return cost < s.cost;
  }
  bool operator>(const State& s) const{
    return cost > s.cost;
  }
};

int main(){
  int H,W;
  while(~scanf("%d %d",&H,&W)){
    char stage[101][101];
    int sx,sy;
    int dir;
    int init_state=0;
    map<P,int> dic;

    for(int y=0;y<H;y++){
      char buf[101];
      scanf("%s",buf);
      for(int x=0;x<W;x++){
	stage[y][x] = buf[x];
	if(buf[x] == 'U' || buf[x] == 'R'
	   || buf[x] == 'D' || buf[x] == 'L'){
	  sx = x;
	  sy = y;
	  init_state |= (1<<init_dic(x,y,dic));

	  const char dirs[4] = {'U','R','D','L'};
	  for(int i=0;i<4;i++){
	    if(dirs[i] == buf[x]){
	      dir = i;
	      break;
	    }
	  }
	}
	if(buf[x] == 'o'){
	  init_state |= (1<<init_dic(x,y,dic));
	}
      }
    }
    
    fill_dic(W,H,dic);
    priority_queue<State,vector<State>,greater<State> > que;
    que.push(State(sx,sy,dir,init_state,0));

    set<int> visited[101][101][4];
    bool flag = false;
    while(!que.empty()){
      State s = que.top();
      que.pop();

      if(visited[s.x][s.y][s.dir].count(s.remaining) > 0) continue;
      visited[s.x][s.y][s.dir].insert(s.remaining);

      if(__builtin_popcount(s.remaining) == 1){
	const char dirs[4] = {'U','R','D','L'};
	string ans = "";
	for(int i=0; i<s.route.size(); i++){
	  ans += dirs[s.route[i]];
	}
	cout << ans << endl;
      }

      for(int i=0;i<4;i++){
	if(i == (s.dir + 2) % 4) continue;

	int dx,dy;
	for(int j=1;j<=max(H,W);j++){
	  dx = s.x + tx[i] * j;
	  dy = s.y + ty[i] * j;
	  if(dx < 0 || dy < 0 || dx >= W || dy >= H ) continue;
	  if(dic[P(dx,dy)] == -1) continue;
	  
	  if(s.remaining & (1<<dic[P(dx,dy)])){
	    int next = s.remaining & ~(1<<dic[P(s.x,s.y)]);
	    vector<char> next_route = s.route;
	    next_route.push_back(i);
	    que.push(State(dx,dy,i,next,s.cost+1,next_route));
	    break;
	  }
	}
      }
    }
  }
}
