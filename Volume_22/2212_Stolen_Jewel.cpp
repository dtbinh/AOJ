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
#include <iterator>
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;
 
int tx[] = {0,1,0,-1};//URDL
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

//URDL
// const static char dir[4] = {'U','R','D','L'};
// const static string dir_str[4] = {"U","R","D","L"};

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
};

class State{
public:
  int cost;
  int route;
  int x;
  int y;
  State(char _x,char _y,int _c,int _r) : cost(_c), route(_r),x(_x),y(_y){}
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
    if(H==0 && W==0) break;
    bitset<500000000> dp[50][50][4];
    char stage[50][50];

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

    Trie trie;
    for(int sequence_idx=0;
	sequence_idx < total_prohibited_sequences;
	sequence_idx++){
      string str;
      cin >> str;
      string num_str = "";
      for(int i=0;i<str.size();i++){
	if(str[i] == 'U'){
	  num_str += "1";
	}
	else if(str[i] == 'R'){
	  num_str += "2";
	}
	else if(str[i] == 'D'){
	  num_str += "3";
	}
	else if(str[i] == 'L'){
	  num_str += "4";
	}
      }

      reverse(num_str.begin(),num_str.end());
      trie.insert(num_str);
    }
    
    priority_queue<State,vector<State>,greater<State> > que;
    que.push(State(sx,sy,0,0));

    int res = INF;
    while(!que.empty()){
      State s = que.top();
      long route = s.route;
      int cost = s.cost;
      int sx = s.x;
      int sy = s.y;

      que.pop();

      string route_str;

      stringstream ss;
      ss << route;
      ss >> route_str;

      if(route_str == "0") route_str = "";

      for(int i=0;i<4;i++){
	int dx = sx + tx[i];
	int dy = sy + ty[i];
	if(dx < 0 || dx >= W
	   || dy < 0 || dy >= H) continue;

	if(stage[dy][dx] == '#') continue;

	string front;
	front = (char)((i+1) + '0');
	string next =  front + route_str;
	next = next.substr(0,10);
	if(trie.common_prefix_search(next)){
	  continue;
	}

	long next_num = atol(next.substr(0,9).c_str());
	if(dp[dy][dx][i][next_num]) continue;
	dp[dy][dx][i][next_num] = true;

	if(stage[dy][dx] == 'G'){
	  res = cost + 1;
	  goto found;
	}

	que.push(State(dx,dy,cost+1,next_num));
      }
    }

  found:;
    printf("%d\n",res == INF ? -1 : res);
  }
}
