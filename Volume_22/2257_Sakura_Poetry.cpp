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
#include <unordered_map>
#include <functional>
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
    int match_count;
    long long id;
    MatchingResult() : match_count(0), id(0){}
  };
};

class AhoCorasick::Node {
private:
  set<string> results;
  unordered_map<char,AhoCorasick::Node*> transitions;
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
  void set_state(AhoCorasick::Node* current){
    state = current;
  }
  void set_state(long long current_num){
    state = reinterpret_cast<AhoCorasick::Node*>(current_num);
  }

  AhoCorasick::MatchingResult feed(const string& text){
    AhoCorasick::MatchingResult matching_result;
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
      
      matching_result.match_count += state->get_results().size();
      index++;
    }
    matching_result.id = state->get_id();
    state = root;
    return matching_result;
  }
};

class State{
public:
  int last_word;
  int seasonword_count;
  ll last_node_address;
  State() : last_word(0),seasonword_count(0),last_node_address(0) {}
  State(ll _a) : last_word(0),seasonword_count(0),last_node_address(_a) {}
  State(int _s,int _sc,ll _a) : last_word(_s),seasonword_count(_sc),last_node_address(_a) {}

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

  bool operator==(const State& s) const{
    return (last_word == s.last_word
	    && seasonword_count == s.seasonword_count
	    && last_node_address == s.last_node_address);
  }
};

namespace std {
  template <>
  struct hash<State>
  {
    std::size_t operator()(const State& k) const
    {
      using std::size_t;
      using std::hash;
      using std::string;
      
      // Compute individual hash values for first,
      // second and third and combine them using XOR
      // and bit shifting:
      
      return ((hash<int>()(k.last_word)
	       ^ (hash<int>()(k.seasonword_count) << 1)) >> 1)
	^ (hash<ll>()(k.last_node_address) << 1);
    }
  };
};


vector<string> words;
map<string,int> visited_words;

int word2num(const string& str){
  if(visited_words.find(str) == visited_words.end()){
    words.push_back(str);
    visited_words[str] = words.size() - 1;
    return words.size() - 1;
  }
  return visited_words[str];
}

int main(){
  int connect_dic_size;
  int word_limit;
  int total_seasonwords;
  
  while(~scanf("%d %d %d",
	       &connect_dic_size,
	       &word_limit,
	       &total_seasonwords)){
    if(word_limit == 0) break;

    words.clear();
    visited_words.clear();

    set<string> seasonwords;
    vector<int> connects[1000];

    for(int i=0;i<connect_dic_size;i++){
      string from,to;
      cin >> from >> to;
      int f_num = word2num(from);
      int t_num = word2num(to);
      connects[f_num].push_back(t_num);
    }

    for(int i=0;i<total_seasonwords;i++){
      string seasonword;
      cin >> seasonword;
      seasonwords.insert(seasonword);
    }

    AhoCorasick::SearchMachine* sm = new AhoCorasick::SearchMachine(seasonwords);
    
    AhoCorasick::MatchingResult start = sm->feed("");
    unordered_map<State,int> dp[600];

    //init
    for(int i=0;i<words.size();i++){
      sm->set_state(start.id);
      AhoCorasick::MatchingResult mr = sm->feed(words[i]);
      //last_word,season_count,last_node
      if(mr.match_count >= 2) continue;
      dp[words[i].size()][State(i,mr.match_count,mr.id)] = 1;
    }

    for(int prev_word_length = 0; 
	prev_word_length < word_limit; 
	prev_word_length++){
      unordered_map<State,int>& prev = dp[prev_word_length];
      for(unordered_map<State,int>::iterator prev_state_it = prev.begin();
	  prev_state_it != prev.end();
	  prev_state_it++){

	for(int to_idx=0;
	    to_idx < connects[prev_state_it->first.last_word].size();
	    to_idx++){

	  int next_idx = connects[prev_state_it->first.last_word][to_idx];
	  sm->set_state(prev_state_it->first.last_node_address);
	  AhoCorasick::MatchingResult mr = sm->feed(words[next_idx]);

	  if(prev_state_it->first.seasonword_count + mr.match_count >= 2) continue;
	  //last_word,season_count,last_node
	  State next(next_idx, 
		     prev_state_it->first.seasonword_count + mr.match_count,
		     mr.id);

	  dp[prev_word_length + words[next_idx].size()][next]
	    += prev_state_it->second % MOD;
	  
	  dp[prev_word_length + words[next_idx].size()][next] %= MOD;
	}
      }
      dp[prev_word_length].clear();
    }
    int res = 0;

    unordered_map<State,int>& last_state = dp[word_limit];
    for(unordered_map<State,int>::iterator prev_state_it = last_state.begin();
	prev_state_it != last_state.end();
	prev_state_it++){
      if(prev_state_it->first.seasonword_count != 1) continue;

      res += prev_state_it->second % MOD;
      res %= MOD;
    }

    printf("%d\n",res);
  }
}
