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
  struct MatchingResult {
    map<string,int> rv;
    long long id;
  };
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

  AhoCorasick::Node* get_transition(const char c){
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

  long long get_id() const{
    return reinterpret_cast<long long>(this);
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
      tmp_nodes.reserve(nodes.size() + root->get_transitions()[i]->get_transitions().size() + 1); 
      merge(nodes.begin(), nodes.end(),
	    root->get_transitions()[i]->get_transitions().begin(), root->get_transitions()[i]->get_transitions().end(),
	    back_inserter<vector<AhoCorasick::Node*> >(tmp_nodes));
      nodes.swap(tmp_nodes);
    }

    while(nodes.size() > 0){
      vector<AhoCorasick::Node*> next_nodes;
      for(int i=0;i<nodes.size();i++){
	AhoCorasick::Node* r = nodes[i]->get_parent()->get_failure();
	const char c = nodes[i]->get_char();
      
	while((r != NULL) && (r->get_transition(c) == NULL)){
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
	tmp_nodes.reserve(next_nodes.size() + nodes[i]->get_transitions().size() + 1); 
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

  MatchingResult feed(const string& text){
    MatchingResult mr;
    int index = 0;
    while(index < text.length()){
      AhoCorasick::Node* trans = NULL;
      while(state != NULL){
	trans = state->get_transition(text[index]);
	if(state == root || trans != NULL) break;
	state = state->get_failure();
      }

      if(trans != NULL){
	state = trans;
      }
      
      set<string> results;
      if(state != NULL) results = state->get_results();
      for(set<string>::iterator it = results.begin();
	  it != results.end();
	  it++){
	mr.rv[*it] = index - it->length() + 1;
      }
      index++;
    }
    mr.id = state->get_id();
    state = root;
    return mr;
  }
};

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

int main(){
  int H,W;
  while(~scanf("%d %d",&H,&W)){
    if(H==0 && W==0) break;
    char stage[50][50];
    set<ll> dp[50][50];

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
      keywords.insert(str);
    }

    AhoCorasick::SearchMachine* sm = new AhoCorasick::SearchMachine(keywords);

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

	string next = route + dir_str[i];
	if(next.size() > 10) next = next.substr(next.size()-10);
	AhoCorasick::MatchingResult mr = sm->feed(next);

	if((!mr.rv.empty())){
	  // cout << mr.rv.begin()->first << endl;
	  // cout << next << endl;
	  continue;
	}

	if(dp[dy][dx].count(mr.id)) continue;
	dp[dy][dx].insert(mr.id);

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
