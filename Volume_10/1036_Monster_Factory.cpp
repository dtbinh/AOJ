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

using namespace std;

typedef long long ll;
typedef pair <int,int> P;

static const double EPS = 1e-8;

string red_str;
string green_str;
string pak_str;

class State{
public:
  string green;
  string red;
  int mid;
  int upper_idx;
  int left_idx;
  State(int _u,int _l,int _m) : upper_idx(_u),left_idx(_l),mid(_m){}
  bool operator ==(const State& s) const{
    return (green==s.green
	    && red == s.red
	    && mid == s.mid
	    && upper_idx == s.upper_idx
	    && left_idx == s.left_idx);
  }
  bool operator !=(const State& s) const{
    return !(green==s.green
	     && red == s.red
	     && mid == s.mid
	     && upper_idx == s.upper_idx
	     && left_idx == s.left_idx);
  }
};

State push_right(const State& s){
  State next = s;
  if(s.mid != -1) next.green.push_back(s.mid);
  if(s.left_idx < green_str.size()){
    next.mid = green_str[s.left_idx];
    next.left_idx = s.left_idx+1;
  }
  else{
    next.mid = -1;
  }
  return next;
}

State push_down(const State& s){
  State next = s;
  if(s.mid != -1) next.red.push_back(s.mid);
  if(s.upper_idx < red_str.size()){
    next.mid = red_str[s.upper_idx];
    next.upper_idx = s.upper_idx+1;
  }
  else{
    next.mid = -1;
  }
  return next;
}

int main(){
  while(cin >> red_str){
    if(red_str == "-") break;

    cin >> green_str;
    cin >> pak_str;

    queue<State> que;
    que.push(State(0,0,-1));

    while(!que.empty()){
      State s = que.front();
      que.pop();

      if(pak_str.size() < s.red.size()) continue;

      if(s.red.size() > 0
	 && pak_str.substr(0,s.red.size()) != s.red) continue;

      if(s.green.size() + s.red.size()
	 == green_str.size() + red_str.size()){
	if(s.red != pak_str) continue;
	cout << s.green << endl;
	goto found;
      }

      State next_push_down_state = push_down(s);
      State next_push_right_state = push_right(s);
      if(next_push_down_state != s){
	que.push(next_push_down_state);
      }
      if(next_push_right_state != s){
	que.push(next_push_right_state);
      }
    }
  found:;
  }
}
