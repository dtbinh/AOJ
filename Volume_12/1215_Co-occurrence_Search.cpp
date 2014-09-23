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
vector<int> gIndex[1024];

class State {
public:
  int _min_pos;
  int _max_pos;
  int _query_i;

  State(int min_pos,int max_pos,int query_i) :
    _min_pos(min_pos), _max_pos(max_pos), _query_i(query_i) {}
  bool operator<(const State& s) const{
    if(_max_pos - _min_pos == s._max_pos - s._min_pos){
      return _query_i > s._query_i;
    }
    return _max_pos - _min_pos < s._max_pos - s._min_pos;
  }
  bool operator>(const State& s) const{
    if(_max_pos - _min_pos == s._max_pos - s._min_pos){
      return _query_i > s._query_i;
    }
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
  int ans_min_pos = INF;
  int ans_max_pos = -INF;
  map<int,bool> freq;
  map<P,bool> visited[64];

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
      if(freq.find(s._min_pos) != freq.end()) continue;
      freq[s._min_pos] = true;

      if(ans_min_pos > s._min_pos){
	ans_max_pos = s._max_pos;
	ans_min_pos = s._min_pos;
      }
    }

    int next_lower
      = lower_bound(gIndex[gQuery[s._query_i]].begin(),gIndex[gQuery[s._query_i]].end(),s._min_pos)
      - gIndex[gQuery[s._query_i]].begin();
    
    if(next_lower < gIndex[gQuery[s._query_i]].size()
       && gIndex[gQuery[s._query_i]][next_lower] <= s._max_pos){
      if(visited[s._query_i].find(P(s._min_pos,s._max_pos)) != visited[s._query_i].end()) continue;
      que.push(State(s._min_pos,
		     s._max_pos,
		     s._query_i + 1));
    }

    else{
      for(int index_i = 0; index_i < gIndex[gQuery[s._query_i]].size(); index_i++){
	int next_min = min(s._min_pos,gIndex[gQuery[s._query_i]][index_i]);
	int next_max = max(s._max_pos,gIndex[gQuery[s._query_i]][index_i]);
	if(visited[s._query_i].find(P(next_min,next_max)) != visited[s._query_i].end()) continue;
	
	visited[s._query_i][P(next_min,next_max)] = true;
	que.push(State(next_min,
		       next_max,
		       s._query_i + 1));
      }
    }
  }


  // if(printed) printf("\n");
  if(freq.size() > 0){
    printf("%d\n",freq.size());
    printf("\n");
    print_text(gText.substr(ans_min_pos,ans_max_pos-ans_min_pos+1));
    printf("\n");
  }
  else {
    printf("0\n");
    printf("\n");
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
