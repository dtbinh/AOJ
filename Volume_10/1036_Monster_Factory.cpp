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
  char mid;
  int upper_idx;
  int left_idx;
  State(int _u,int _l,char _m) : upper_idx(_u),left_idx(_l),mid('.'){}
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
  if(s.mid != '.') next.green.push_back(s.mid);
  if(s.left_idx < green_str.size()){
    next.mid = green_str[s.left_idx];
    next.left_idx = s.left_idx+1;
  }
  else{
    next.mid = '.';
  }
  return next;
}

State push_down(const State& s){
  State next = s;
  if(s.mid != '.') next.red.push_back(s.mid);
  if(s.upper_idx < red_str.size()){
    next.mid = red_str[s.upper_idx];
    next.upper_idx = s.upper_idx+1;
  }
  else{
    next.mid = '.';
  }
  return next;
}

int main(){
  while(cin >> red_str){
    if(red_str == "-") break;

    cin >> green_str;
    cin >> pak_str;

    State state(0,0,-1);

    for(int round =0; round < 1000;round++){
      if(state.mid != -1){
	bool has_pak = false;
	for(int i=0;i<pak_str.size();i++){
	  if(state.mid == pak_str[i]){
	    has_pak = true;
	  }
	}
	if(has_pak){
	  state = push_down(state);
	}
	else{
	  state = push_right(state);
	}
      }
      else{
	State prev = state;
	state = push_down(state);
	if(prev == state) break;
      }
    }

    cout << state.green << endl;
  }
}
