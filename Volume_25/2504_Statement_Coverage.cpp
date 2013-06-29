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
  
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};
static const int MAX_V = 1000;

int V = 1000;
vector<int> G[MAX_V];
vector<int> rG[MAX_V];
vector<int> vs;
bool used[MAX_V];
int cmp[MAX_V];

void add_edge(int from,int to){
  G[from].push_back(to);
  rG[to].push_back(from);
}

void dfs(int v) {
  used[v] = true;
  for(int i=0; i<G[v].size();i++){
    if(!used[G[v][i]]) dfs(G[v][i]);
  }
  vs.push_back(v);
}

void rdfs(int v,int k){
  used[v] = true;
  cmp[v] = k;
  for(int i=0; i<rG[v].size();i++){
    if(!used[rG[v][i]]) rdfs(rG[v][i],k);
  }
}

int scc(){
  memset(used,0,sizeof(used));
  vs.clear();
  for( int v=0; v < V; v++){
    if(!used[v]) dfs(v);
  }

  memset(used,0,sizeof(used));
  int k=0;
  for(int i=vs.size()-1; i>=0; i--){
    if(!used[vs[i]]) rdfs(vs[i],k++);
  }
  return k;
}

  // EQUA = FACT | FACT (& FACT)* | FACT (| FACT)*
  // FACT = INVS TERM
  // TERM = (EQUA) | LETTERS
  // INVS = INVS INV | eps
  // LETTER = A | B | ... | Z

class Data {
public:
  Data(int p,bool v) : pos(p),val(v){}
  Data() : pos(0),val(true){}
  int pos;
  bool val;
};

Data invs(int pos,const string& str,map<string,bool>& table);
Data letters(int pos,const string& str,map<string,bool>& table);
Data equation(int pos,const string& str,map<string,bool>& table);
Data term(int pos,const string& str,map<string,bool>& table);
Data factor(int pos,const string& str,map<string,bool>& table);

// EQUA = factor (& factor)* | factor (| factor)*
Data equation(int pos,const string& str,map<string,bool>& table){
  Data r = factor(pos,str,table);
  while(str[r.pos+1] == '&' || str[r.pos+1] == '|'){
    Data _r = factor(r.pos+2,str,table);

    if(str[r.pos+1] == '&'){
      r.val = (r.val && _r.val);
    }
    else{
      r.val = (r.val || _r.val);
    }
    r.pos = _r.pos;
  }
  return r;
}

Data factor(int pos, const string& str,map<string,bool>& table){
  Data inv_r = invs(pos,str,table);
  //  printf("inv result: %s str:%s pos:%d\n",inv_r.val ? "true" : "false" ,str.c_str(),inv_r.pos);
  Data term_r = term(inv_r.pos+1,str,table);
  
  if(inv_r.val == true){
    //    printf("factor result: %s str:%s pos:%d\n",term_r.val ? "true" : "false" ,str.substr(pos,term_r.pos-pos+1).c_str(),term_r.pos);
    return term_r;
  }
  else{
    term_r.val = !term_r.val;
    //    printf("factor result: %s str:%s pos:%d\n",term_r.val ? "true" : "false" ,str.substr(pos,term_r.pos-pos+1).c_str(),term_r.pos);
    return term_r;
  }
}

Data invs(int pos,const string& str,map<string,bool>& table){
  bool val = true;
  int last_pos = pos;
  
  while(str[last_pos] == '~'){
    val = !val;
    last_pos++;
    // printf("last_pos:%d val:%s\n",last_pos,val ? "true" : "false");
  }

  Data res(last_pos-1,val);
  return res;
}

// term = (equation) | letters
Data term(int pos,const string& str,map<string,bool>& table){
  if(str[pos] == '('){
    Data res = equation(pos+1,str,table);
    res.pos += 1;
    return res;
  }
  else{
    Data res = letters(pos,str,table);
    //    printf("last term: %c\n",str[res.pos]);
    return res;
  }
}

struct Data letters(int pos,const string& str,map<string,bool>& table){
  string key = "";
  int last_pos = pos;
  while(isalpha(str[last_pos])){
    key.push_back(str[last_pos]);
    last_pos++;
  }

  bool b;
  if(table.find(key) == table.end()){
    b = true;
  }
  else{
    b = table[key];
  }
  //  printf("%s %s\n",key.c_str(),b ? "true" : "false");
  Data res(last_pos-1,b);
  return res;
}

void UpdateTable(map<string,bool>& table){
  // cout << table.size() << endl;
  for(map<string,bool>::iterator it = table.begin();
      it != table.end();
      it++){

    bool flag = rand() % 2;
    it->second = flag;
  }
}

void PrintTable(map<string,bool>& table){
  //  cout << table.size() << endl;
  for(map<string,bool>::iterator it = table.begin();
      it != table.end();
      it++){
    printf("%s %s ",(it->first).c_str(),it->second ? "true" : "false"); 
  }
  printf("\n");
}

void SetTable(map<string,bool>& table,
	      const vector<string>& commands, 
	      map<int,vector<string> >& has_vals)
{
  for(int i=0;i<commands.size();i++){
    //      cout << commands[i] << endl;
    string str = "";
    for(int j=0;j<commands[i].size();j++){
      if(isalpha(commands[i][j])){
	str.push_back(commands[i][j]);
      }
      else{
	if(str.size() >= 1){
	  //	    cout << str << endl;
	  has_vals[i].push_back(str);
	  table[str] = true;
	}
	str = "";
      }
    }
  }
}

bool OR_Operation(const string& command,
		  const vector<string>& keys,
		  map<string,bool>& table,
		  map<string,int>& keyidx) {
  string key1 = keys[0];
  string key2 = keys[1];
  int node1 = keyidx[key1]*2;
  int inv_node1 = keyidx[key1]*2+1;
  int node2 = keyidx[key2]*2;
  int inv_node2 = keyidx[key2]*2+1;

  for(int i=0;i<=1;i++){
    table[key1] = (bool)i;  
    for(int j=0;j<=1;j++){
      if(key1 == key2 && i!=j) continue;
      table[key2] = (bool)j;  
      Data d = equation(0,command,table);      
      if(d.val == false){
	if(i==0 && j==0){
	  //a|b
	  add_edge(inv_node2,node1);
	  add_edge(inv_node1,node2);
	}
	else if(i==0 && j==1){
	  //a|~b
	  add_edge(node2,node1);
	  add_edge(inv_node1,inv_node2);
	}
	else if(i==1 && j==0){
	  //~a|b
	  add_edge(inv_node2,inv_node1);
	  add_edge(node1,node2);
	}
	else if(i==1 && j==1){
	  //~a|~b
	  add_edge(node2,inv_node1);
	  add_edge(node1,inv_node2);
	}
	goto found_false;
      }
    }
  }
 found_false:;
}

bool AND_Operation(const string& command ,
		   const vector<string>& keys,
		   map<string,bool>& table,
		   map<string,int>& keyidx) {
  string key1 = keys[0];
  string key2 = keys[1];
  int node1 = keyidx[key1]*2;
  int inv_node1 = keyidx[key1]*2+1;
  int node2 = keyidx[key2]*2;
  int inv_node2 = keyidx[key2]*2+1;

  bool isok = false;
  for(int i=0;i<=1;i++){
    table[key1] = (bool)i;  
    for(int j=0;j<=1;j++){
      if(key1 == key2 && i!=j) continue;
      table[key2] = (bool)j;  
      Data d = equation(0,command,table);      
      if(d.val == true) {
	isok = true;
	if(i==0 && j==0){
	  //~a&~b -> (~a|~a) & (~b|~b)
	  add_edge(node1,inv_node1);
	  add_edge(node2,inv_node2);
	}
	else if(i==0 && j==1){
	  //~a&b -> (~a|~a) & (b|b)
	  add_edge(node1,inv_node1);
	  add_edge(inv_node2,node2);
	}
	else if(i==1 && j==0){
	  //a&~b -> (a|a) & (~b|~b)
	  add_edge(inv_node1,node1);
	  add_edge(node2,inv_node2);
	}
	else if(i==1 && j==1){
	  //a&b -> (a|a) & (b|b)
	  add_edge(inv_node1,node1);
	  add_edge(inv_node2,node2);
	}
	goto found_true;
      }
    }
  }
  if(!isok){
    // a&~a -> (a|a) & (~a|~a)
    if(key1==key2){
      add_edge(inv_node1,node1);
      add_edge(node1,inv_node1);
    }
  }

 found_true:;
}

void Without_Operand_Operation(const string& command,
		  const vector<string>& keys,
		  map<string,bool>& table,
		  map<string,int>& keyidx) {
  string key1 = keys[0];
  int node1 = keyidx[key1]*2;
  int inv_node1 = keyidx[key1]*2+1;

  for(int i=0;i<=1;i++){
    table[key1] = (bool)i;  
    Data d = equation(0,command,table);      
    if(d.val == true){
      if(i==0){
	//~a -> (~a|~a)
	add_edge(node1,inv_node1);
	break;
      }
      else if(i==1){
	//a -> (a|a)
	add_edge(inv_node1,node1);
	break;
      }
    }
  }
}


void ClearGraph(){
  for(int i=0;i<MAX_V;i++){
    G[i].clear();
    rG[i].clear();
  }
  vs.clear();
  memset(used,0,sizeof(used));
  memset(cmp,-1,sizeof(cmp));
}

char find_operand(const string& str) {
  for(int i=0;i<str.size();i++){
    if(str[i] == '&'){
      return '&';
    }
    else if(str[i] == '|'){
      return '|';
    }
  }
  return '#';
}
int main(){

  int command_num,val_num;
  while(~scanf("%d %d",&command_num,&val_num)){
    ClearGraph();
    vector<string> commands;
    for(int i=0;i<command_num;i++){
      string str;
      cin >> str;
      commands.push_back(str);
    }

    map<string,bool> table;
    map<string,int> keyidx;
    map<int,vector<string> > has_vals;
    SetTable(table,commands,has_vals);
    V = table.size() * 2;

    int idx = 0;
    for(map<string,bool>::iterator it = table.begin(); it != table.end(); it++){
      keyidx[it->first] = idx++;
    }

    bool satisfied = true;
    
    for(int i=0;i<commands.size();i++){
      char op = find_operand(commands[i]);
      if(op == '#'){
	Without_Operand_Operation(commands[i],has_vals[i],table,keyidx);
      }
      else if(op == '&'){
	AND_Operation(commands[i],has_vals[i],table,keyidx);
      }
      else if(op == '|'){
	OR_Operation(commands[i],has_vals[i],table,keyidx);
      }
    }

    scc();

    for(int i=0;i<V/2;i++){
      if(cmp[2*i]==cmp[2*i+1]){
	satisfied = false;
      }
    }

    printf("%s\n",satisfied ? "accept" : "reject");

  }
}
