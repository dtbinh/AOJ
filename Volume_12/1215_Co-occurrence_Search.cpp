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
#include <assert.h>
  
using namespace std;
  
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P> PP;
  
static const double EPS = 1e-8;

string gText;
string gQuery;
vector<int> gIndex[256];

class State {
public:
  int _min_pos;
  int _max_pos;
  int _query_i;

  State(int min_pos,int max_pos,int query_i) :
    _min_pos(min_pos), _max_pos(max_pos), _query_i(query_i) {}
  bool operator<(const State& s) const{
    return _max_pos - _min_pos < s._max_pos - s._min_pos;
  }
  bool operator>(const State& s) const{
    return _max_pos - _min_pos > s._max_pos - s._min_pos;
  }
};

bool printed = false;

void print_text(const string& text){
  int offset = 0;
  int text_i = 0;
  while(offset < text.size()){
    for(text_i = offset; text_i < text.size(); text_i++){
      if(text_i - offset >= 72) break;
      printf("%c",text[text_i]);
    }
    printf("\n");
    offset += 72;
  }
}

void bfs(){
  priority_queue<State,vector<State>,greater<State> > que;
  que.push(State(INF,-INF,0));

  bool is_first = true;
  int ans_length = 0;
  map<int,string> ans;
  while(!que.empty()){
    State s = que.top();
    que.pop();

    if(s._query_i == gQuery.size()){
      if(is_first) {
	ans_length = s._max_pos - s._min_pos + 1;
	is_first = false;
      }

      else if(!is_first) {
	if(ans_length != s._max_pos - s._min_pos + 1){
	  break;
	}
      }
      string tmp = gText.substr(s._min_pos,s._max_pos - s._min_pos + 1);
      if(ans.find(s._min_pos) != ans.end()) continue;
      ans[s._min_pos] = tmp;
    }

    for(int index_i = 0; index_i < gIndex[gQuery[s._query_i]].size(); index_i++){
      que.push(State(min(s._min_pos,gIndex[gQuery[s._query_i]][index_i]),
		     max(s._max_pos,gIndex[gQuery[s._query_i]][index_i]),
		     s._query_i + 1));
    }
  }


  if(printed) printf("\n");
  if(ans.size() > 0){
    printf("%d\n",ans.size());
    printf("\n");
    print_text(ans.begin()->second.c_str());
  }
  else {
    printf("0\n");
  }
  printed = true;
}

void print_co_occurrence(){
  for(int i=0;i<256;i++){
    gIndex[i].clear();
  }

  for(int text_i = 0; text_i < gText.size(); text_i++){
    gIndex[gText[text_i]].push_back(text_i);
  }

  bfs();  
}

int main(){
  string str;
  int phase = 0;
  while(getline(cin,str)){
    if(str.size() == 0){
      phase++;
      continue;
    }
    if(phase % 2 == 0){
      gText += str;
    }
    else{
      gQuery = str;

      print_co_occurrence();
      
      gQuery = "";
      gText = "";
    }
  }
}
