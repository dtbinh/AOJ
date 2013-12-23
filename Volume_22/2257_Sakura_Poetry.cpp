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
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;
static const int MOD = 1000000007;

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

  void set_state(AhoCorasick::Node* current){
    state = current;
  }

  void set_state(long long current_num){
    state = reinterpret_cast<AhoCorasick::Node*>(current_num);
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
  string last_word;
  int seasonword_count;
  ll last_node_address;
  State() : last_word(""),seasonword_count(0),last_node_address(0) {}
  State(ll _a) : last_word(""),seasonword_count(0),last_node_address(_a) {}
  State(const string& _s,int _sc,ll _a) : last_word(_s),seasonword_count(_sc),last_node_address(_a) {}

  bool operator<(const State& s) const{
    if(last_word == s.last_word){
      if(seasonword_count == s.seasonword_count){
	return last_node_address < s.last_node_address;
      }
      else{
	return seasonword_count < s.seasonword_count;
      }
    }
    else{
      return last_word < s.last_word;
    }
  }
};

int main(){
  int connect_dic_size;
  int word_limit;
  int total_seasonwords;
  
  while(~scanf("%d %d %d",
	       &connect_dic_size,
	       &word_limit,
	       &total_seasonwords)){
    if(word_limit == 0) break;

    set<string> seasonwords;
    map<string,vector<string> > connects;
    for(int i=0;i<connect_dic_size;i++){
      string from,to;
      cin >> from >> to;
      connects[from].push_back(to);
    }
    for(int i=0;i<total_seasonwords;i++){
      string seasonword;
      cin >> seasonword;
      seasonwords.insert(seasonword);
    }

    AhoCorasick::SearchMachine* sm = new AhoCorasick::SearchMachine(seasonwords);
    AhoCorasick::MatchingResult start = sm->feed("");
    //dp[word_length][State]
    map<State,int> dp[501];
    dp[0][State()] = 1;

    //init
    for(map<string,vector<string> >::iterator it = connects.begin();
	it != connects.end();
	it++){

      sm->set_state(start.id);
      const string& from = it->first;
      AhoCorasick::MatchingResult mr = sm->feed(from);

      //last_word,season_count,last_node
      State next(from, 
		 mr.rv.size(),
		 mr.id);
      dp[from.size()][next] = 1;
    }

    for(int prev_word_length = 0; prev_word_length <= word_limit; prev_word_length++){
	for(map<State,int>::iterator prev_state_it = dp[prev_word_length].begin();
	    prev_state_it != dp[prev_word_length].end();
	    prev_state_it++){

	  for(map<string,vector<string> >::iterator it = connects.begin();
	      it != connects.end();
	      it++){
	    for(int to_idx=0;to_idx < it->second.size(); to_idx++){
	      const string& from = it->first;
	      const string& to = it->second[to_idx];

	      if(from == prev_state_it->first.last_word){
		sm->set_state(prev_state_it->first.last_node_address);
		AhoCorasick::MatchingResult mr = sm->feed(to);
		
		//last_word,season_count,last_node
		State next(to, 
			   prev_state_it->first.seasonword_count + mr.rv.size(),
			   mr.id);
		
		// cout << "from:" << from <<  " to:" << to << endl;
		
		dp[prev_word_length + to.size()][next]
		  += dp[prev_word_length][prev_state_it->first] % MOD;
		dp[prev_word_length + to.size()][next] %= MOD;
	      }
	    }
	  }
	}
    }
    
    int res = 0;
    for(map<State,int>::iterator prev_state_it = dp[word_limit].begin();
	prev_state_it != dp[word_limit].end();
	prev_state_it++){
      if(prev_state_it->first.seasonword_count != 1) continue;

      res += dp[word_limit][prev_state_it->first] % MOD;
      res %= MOD;
    }

    printf("%d\n",res);
  }
}
