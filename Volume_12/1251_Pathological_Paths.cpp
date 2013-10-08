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

class Node{
public:
  Node(string _n,string _p) : name(_n),parent(_p),id(0){}
  string name;
  string parent;
  int id;
};

void str2node(const string& str,
	      map<string,vector<Node> >& tree){
		
  string name="";
  string parent="root";
  for(int i=0;i<str.size();i++){
    if(str[i] == '/'){
      if(name != ""){
	tree[parent].push_back(Node(name,parent));
	parent = name;
      }
      name="";
      continue;
    }
    name.push_back(str[i]);
  }
  if(name != ""){
    tree[parent].push_back(Node(name,parent));
  }
}
  
int find_tree(vector<string> operation,map<string,vector<Node> >& tree){
    string current_dir = "root";
    int pos = 0;
    while(pos < operation.size()){
      if(operation[pos]=="/"){
	if(pos+1 < operation.size()){
	  bool is_found = false;
	  for(int j=0;j<tree[current_dir].size();j++){
	    if(tree[current_dir][j].name == operation[pos+1]){
	      current_dir = operation[pos+1];
	      pos+=2;
	      is_found = true;
	      break;
	    }
	  }

	  if(!is_found){
	    return -1;
	  }
	}
	else{
	  return -1;
	  //?
	}
      }
      else{
	//?
      }
      
    }
    return -1;
}

vector<string> tokenize(const string& str){
  vector<string> res;
  string name = "";
  for(int i=0;i<str.size();i++){
    if(str[i]=='/'){
      if(name != "") res.push_back(name);
      res.push_back("/");
    }
    else{
      name.push_back(str[i]);
    }
  }

  if(name != "") res.push_back(name);

  return res;
}

int main(){
  int total_reference;
  int total_suspicious;
  while(~scanf("%d %d",&total_reference,&total_suspicious)){
    if(total_reference == 0 && total_suspicious == 0) break;
    
    map<string,vector<Node> > tree;
    for(int i=0;i<total_reference;i++){
      string url;
      cin >> url;
      str2node(url,tree);
    }
    for(int i=0;i<total_suspicious;i++){
      string url1,url2;
      cin >> url1;
      cin >> url2;
      vector<string> tok1 = tokenize(url1);
      vector<string> tok2 = tokenize(url2);
      int id1 = find_tree(tok1,tree);
      int id2 = find_tree(tok2,tree);
      printf("%d %d\n",id1,id2);
    }
  }
}
