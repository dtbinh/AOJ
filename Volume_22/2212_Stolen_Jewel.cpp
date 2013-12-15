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
const static char dir[4] = {'U','R','D','L'};
const static string dir_str[4] = {"U","R","D","L"};

namespace AhoCorasick{
  class Node;
  class SearchMachine;
};

class AhoCorasick::Node {
private:
  set<string> results;
  map<char,AhoCorasick::Node*> transitions;
  vector<AhoCorasick::Node*> v_transitions;
  char character;
  AhoCorasick::Node* parent;
  AhoCorasick::Node* failure;
public:
  Node() : character('\0'),parent(NULL),failure(NULL){}
  Node(AhoCorasick::Node* _p,char _c) : parent(_p),character(_c),failure(NULL){}
  const char get_char() const {
    return character;
  }
  
  AhoCorasick::Node* get_parent() const{
    return parent;
  }

  AhoCorasick::Node* get_failure() const{
    return failure;
  }

  void set_failure(AhoCorasick::Node* _n){
    failure = _n;
  }

  AhoCorasick::Node* get_transition(char c){
    if(transitions.find(c) == transitions.end()) return NULL;
    return transitions[c];
  }

  const set<string>& get_results() const{
    return results;
  }

  void add_result(const string& str){
    results.insert(str);
  }

  void add_transition(AhoCorasick::Node* node){
    transitions[node->get_char()] = node;
    v_transitions.push_back(node);
  }

  const vector<AhoCorasick::Node*>& get_transitions() const{
    return v_transitions;
  }
  
};
class AhoCorasick::SearchMachine{
private:
  set<string> keywords;
  AhoCorasick::Node* root;
  AhoCorasick::Node* state;
public:
  SearchMachine(set<string> _k) : keywords(_k){
    _build_tree();
  }
  SearchMachine(){
    _build_tree();
  }
  void _build_tree(){
    root = new AhoCorasick::Node();
    
    for(set<string>::iterator it = keywords.begin();
	it != keywords.end();
	it++){
      AhoCorasick::Node* node = root;
      const string& keyword = *it;
      for(int i = 0; i < keyword.length(); i++){
	AhoCorasick::Node* next_node = node->get_transition(keyword[i]);
	if(next_node == NULL){
	  next_node = new AhoCorasick::Node(node,keyword[i]);
	  node->add_transition(next_node);
	}
	node = next_node;
      }
      node->add_result(keyword);
    }

    vector<AhoCorasick::Node*> nodes;
    for(int i=0;i<root->get_transitions().size();i++){
      root->get_transitions()[i]->set_failure(root);

      vector<AhoCorasick::Node*> tmp_nodes;
      tmp_nodes.reserve(nodes.size() + root->get_transitions()[i]->get_transitions().size()); 
      merge(nodes.begin(), nodes.end(),
	    root->get_transitions()[i]->get_transitions().begin(), root->get_transitions()[i]->get_transitions().end(),
	    back_inserter<vector<AhoCorasick::Node*> >(tmp_nodes));
      nodes.swap(tmp_nodes);
    }

    while(nodes.size() > 0){
      vector<AhoCorasick::Node*> next_nodes;
      for(int i=0;i<nodes.size();i++){
	AhoCorasick::Node* r = nodes[i]->get_parent()->get_failure();
	char c = nodes[i]->get_char();
      
	while((r != NULL) && (r->get_transition(c) != NULL)){
	  r = r->get_failure();
	}

	if(r == NULL){
	  nodes[i]->set_failure(root);
	}
	else{
	  AhoCorasick::Node* tc = r->get_transition(c);
	  nodes[i]->set_failure(tc);
	  
	  set<string> results;
	  if(tc != NULL) results = tc->get_results();
	  for(set<string>::iterator it = results.begin();
	      it != results.end();
	      it++){
	    nodes[i]->add_result(*it);
	  }
	}

	vector<AhoCorasick::Node*> tmp_nodes;
	tmp_nodes.reserve(next_nodes.size() + nodes[i]->get_transitions().size()); 
	merge(next_nodes.begin(), next_nodes.end(),
	      nodes[i]->get_transitions().begin(), nodes[i]->get_transitions().end(),
	      back_inserter<vector<AhoCorasick::Node*> >(tmp_nodes));
	next_nodes.swap(tmp_nodes);
      }

      nodes = next_nodes;
    }

    root->set_failure(root);
    state = root;
  }

  map<string,int> feed(const string& text,map<string,int> (*callback)(int pos,const string& text)){
    int index = 0;
    map<string,int> rv;
    while(index < text.length()){
      AhoCorasick::Node* trans = NULL;
      while(1){
	trans = state->get_transition(text[index]);
	if(state == root || trans != NULL) break;
	state = state->get_failure();
      }

      if(trans != NULL){
	state = trans;
      }

      set<string> results = state->get_results();
      for(set<string>::iterator it = results.begin();
	  it != results.end();
	  it++){
	rv = (*callback)(index - it->length() + 1,*it);
	if(!rv.empty()){
	  state = root;
	  return rv;
	}
      }
      index++;
    }
    state = root;
    return rv;
  }
};

class State{
public:
  int cost;
  long route;
  int x;
  int y;
  State(int _x,int _y,int _c,long _r) : cost(_c), route(_r),x(_x),y(_y){}
  bool operator<(const State& s) const{
    return cost < s.cost;
  }
  bool operator>(const State& s) const{
    return cost > s.cost;
  }
};


map<string,int> handle_first_func(int pos,const string& keyword){
  map<string,int> total;
  total[keyword] = pos;
  return total;
}

map<string,int> find_first(const string& text,AhoCorasick::SearchMachine* m){
  map<string,int> (*handle_first)(int pos,const string& keyword) = handle_first_func;
  map<string,int> rv = m->feed(text,handle_first);
  return rv;
}

int main(){
  int H,W;

  while(~scanf("%d %d",&H,&W)){
    if(H==0 && W==0) break;
    set<long> dp[50][50];
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

    set<string> keywords;
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
      keywords.insert(num_str);
    }

    AhoCorasick::SearchMachine* sm = new AhoCorasick::SearchMachine(keywords);

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
	if((!find_first(next,sm).empty())){
	  // cout << result.begin()->first << endl;
	  // cout << next << endl;
	  continue;
	}

	long next_num = atol(next.c_str());
	if(dp[dy][dx].count(next_num)) continue;
	dp[dy][dx].insert(next_num);

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
