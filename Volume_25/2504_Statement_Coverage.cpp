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
  
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};

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

map<string,bool> table;

Data invs(int pos,const string& str);
Data letters(int pos,const string& str);
Data equation(int pos,const string& str);
Data term(int pos,const string& str);
Data factor(int pos,const string& str);

  // EQUA = factor (& factor)* | factor (| factor)*
Data equation(int pos,const string& str){
  Data r = factor(pos,str);
  while(str[r.pos+1] == '&' || str[r.pos+1] == '|'){
    Data _r = factor(r.pos+2,str);

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

Data factor(int pos, const string& str){
  Data inv_r = invs(pos,str);
  //  printf("inv result: %s str:%s pos:%d\n",inv_r.val ? "true" : "false" ,str.c_str(),inv_r.pos);
  Data term_r = term(inv_r.pos+1,str);
  
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

Data invs(int pos,const string& str){
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
Data term(int pos,const string& str){
  if(str[pos] == '('){
    Data res = equation(pos+1,str);
    res.pos += 1;
    return res;
  }
  else{
    Data res = letters(pos,str);
    //    printf("last term: %c\n",str[res.pos]);
    return res;
  }
}

struct Data letters(int pos,const string& str){
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

int main(){

  int command_num,val_num;
  while(~scanf("%d %d",&command_num,&val_num)){

    vector<string> commands;
    for(int i=0;i<command_num;i++){
      string str;
      cin >> str;
      commands.push_back(str);
    }

    map<int,vector<string> > vals;
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
	    vals[i].push_back(str);
	    table[str] = true;
	  }
	  str = "";
	}
      }
    }

    const int UPPER_ROUND = 20;
    bool satisfied = false;

    for(int round=1;round < UPPER_ROUND; round++){

      UpdateTable(table);

      for(int walk_num=1,size = table.size();walk_num <= 2 * size;walk_num++){
	bool isok = true;
	int clause_idx;
	for(int i=0;i<commands.size();i++){
	  Data d = equation(0,commands[i]);
	  if(d.val == false) {
	    clause_idx = i;
	    isok = false;
	    break;
	  }
	}

	if(isok){
	  satisfied = true;
	  goto found;
	}

	int inv_val_idx = rand() % vals[clause_idx].size();
	string key = vals[clause_idx][inv_val_idx];
	table[key] = !table[key];
      }
    }
  found:;
    printf("%s\n",satisfied ? "accept" : "reject");
  }
}
