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
  
using namespace std;
  
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P> PP;
  
static const double EPS = 1e-8;
  
int tx[] = {+0,+1,+1,+1,+0,-1.-1,-1};
int ty[] = {-1,-1.+0,+1,+1,+1,+0,-1};

namespace AhoCorasick{
  class Node;
  class SearchMachine;
  struct MatchingResult {
    multimap<string,int> rv;
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
public:
  SearchMachine(set<string> _k) : keywords(_k){
    _build_tree();
  }
  SearchMachine(){
    _build_tree();
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
	mr.rv.insert(make_pair(*it,index - it->length() + 1));
      }
      index++;
    }
    mr.id = state->get_id();
    state = root;
    return mr;
  }
};

int dp[16][1<<16];
map<string,set<int> > route;

void dfs(int x,int y,
	 string str,
	 int bits,
	 char stage[4][4],
	 AhoCorasick::SearchMachine* sm){
  if(__builtin_popcount(bits) > 8) return;

  AhoCorasick::MatchingResult mr = sm->feed(str);
  if(mr.rv.size() > 0){
    route[mr.rv.rbegin()->first].insert(mr.rv.rbegin()->second);
  }

  for(int i=0;i<8;i++){
    int dx = x + tx[i];
    int dy = y + ty[i];
    if(dx < 0 || dx >= 4 || dy < 0 || dy >= 4) continue;
    int idx = dy * 4 + dx;
    if(bits & (1<<idx)) continue;
    string next = str;
    next.push_back(stage[y][x]);
    dfs(dx,dy,next,bits | (1<<idx),stage,sm);
  }
}

int main(){
  int N;
  while(~scanf("%d",&N)){
    char stage[4][4];

    set<string> keywords;
    vector<string> idx2keyword;
    map<string,int> score_table;

    for(int i=0;i<N;i++){
      string word;
      int score;
      cin >> word >> score;
      score_table[word] = score;
      idx2keyword.push_back(word);
      keywords.insert(word);
    }
    for(int y=0;y<4;y++){
      string line;
      cin >> line;
      for(int x=0;x<4;x++){
	stage[y][x] = line[x];
      }
    }

    int time;
    scanf("%d",&time);
    memset(dp,0x3f,sizeof(dp));

    AhoCorasick::SearchMachine sm(keywords);

    for(int y=0;y<4;y++){
      for(int x=0;x<4;x++){
	dfs(x,y,"",0,stage,&sm);
      }
    }

    dp[0][0] = 0;
    for(int S=0;S <= (1<<16)-1;S++){
      for(int idx=0;idx<16;idx++){
	if(S & (1<<idx)) continue;
	string key = idx2keyword[idx];
	for(set<int>::iterator it = route[key].begin();
	    it != route[key].end();
	    it++){
	}
      }
    }
  }
}
