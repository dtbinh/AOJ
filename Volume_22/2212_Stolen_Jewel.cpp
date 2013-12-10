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
 
int tx[] = {0,1,0,-1};//URDL
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

class Nodes {
public:
  class Nodes* children[256];
  bool has_word;
  Nodes() : has_word(false){
    for(int i=0;i<256;i++){
      children[i] = NULL;
    }
  }
};

class Trie {
private:
  Nodes* root;
public:
  Trie(){
    root = new Nodes();
  }

  void insert(const string& str){
    Nodes* current = root;
    for(int i=0;i<str.size();i++){
      char c = str[i];
      if(current->children[c] == NULL){
	current->children[c] = new Nodes();
      }
      current = current->children[c];
    }
    current->has_word = true;
  }

  bool common_prefix_search(const string& str){
    Nodes* current = root;

    for(int i=0;i<str.size();i++){
      char c = str[i];
      if(current->children[c] != NULL){
	current = current->children[c];
      }
      else{
	return false;
      }

      if(current->has_word) return true;
    }

    return false;
  }

  bool exact_match(const string& str){
    Nodes* current = root;

    for(int i=0;i<str.size();i++){
      char c = str[i];
      if(current->children[c] != NULL){
	current = current->children[c];
      }
      else{
	return false;
      }

      if(i == str.size()-1
	 && current->has_word) return true;
    }

    return false;
  }
};

//URDL
const static char dir[4] = {'U','R','D','L'};
const static string dir_str[4] = {"U","R","D","L"};

class State{
public:
  int cost;
  string route;
  int x;
  int y;
  State(int _x,int _y,int _c,string _r) : cost(_c), route(_r),x(_x),y(_y){}
  bool operator<(const State& s) const{
    return cost < s.cost;
  }
  bool operator>(const State& s) const{
    return cost > s.cost;
  }
};

char stage[50][50];
Trie dp[50][50];
Trie trie;

int main(){

  int H,W;
  while(~scanf("%d %d",&H,&W)){
    if(H==0 && W==0) break;

    int sx = 0;
    int sy = 0;
    int gx = 0;
    int gy = 0;
    for(int y=0;y<H;y++){
      char line[51];
      scanf("%s",line);
      for(int x=0;x<W;x++){
	stage[y][x] = line[x];
	if(line[x] == 'S'){
	  sx = x;
	  sy = y;
	}
	else if(line[x] == 'G'){
	  gx = x;
	  gy = y;
	}
      }
    }
    int total_prohibited_sequences;
    scanf("%d",&total_prohibited_sequences);

    for(int sequence_idx=0;
	sequence_idx < total_prohibited_sequences;
	sequence_idx++){
      string str;
      cin >> str;
      reverse(str.begin(),str.end());
      trie.insert(str);
    }

    priority_queue<State,vector<State>,greater<State> > que;
    que.push(State(sx,sy,0,""));
    int res = INF;
    while(!que.empty()){
      State s = que.top();
      string route = s.route;
      int cost = s.cost;
      int sx = s.x;
      int sy = s.y;

      que.pop();
      for(int i=0;i<4;i++){
	int dx = sx + tx[i];
	int dy = sy + ty[i];
	if(dx < 0 || dx >= W
	   || dy < 0 || dy >= H) continue;

	if(stage[dy][dx] == '#') continue;

	string next = dir_str[i] + route;
	if(trie.common_prefix_search(next)){
	  // cout << next << endl;
	  continue;
	}

	string recent10step = next.substr(0,10);
	if(dp[dy][dx].exact_match(recent10step)) continue;
	dp[dy][dx].insert(recent10step);

	if(stage[dy][dx] == 'G'){
	  res = cost + 1;
	  goto found;
	}

	que.push(State(dx,dy,cost+1,next));
      }
    }

  found:;
    printf("%d\n",res == INF ? -1 : res);
  }
}
