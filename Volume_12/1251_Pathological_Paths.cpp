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

string tok2str(const deque<string>& tok);

void make_set(deque<string> tok,
	      set<string>& dirs,
	      set<string>& web_pages){
  string dir = "";
  for(int i=0;i<tok.size();i++){
    dir += tok[i];
    dirs.insert(dir);
  }
  

  if(tok[tok.size()-1] == "index.html"){
    tok.pop_back();
    tok.pop_back();
  }
  web_pages.insert(tok2str(tok));
}

deque<string> tokenize(const string& str){
  deque<string> res;
  string name = "";
  for(int i=0;i<str.size();i++){
    if(str[i]=='/'){
      if(name != "") res.push_back(name);
      res.push_back("/");
      name="";
    }
    else{
      name.push_back(str[i]);
    }
  }

  if(name != "") res.push_back(name);

  return res;
}

string tok2str(const deque<string>& tok){
  string res = "";
  for(int i=0;i<tok.size();i++){
    res += tok[i];
  }
  return res;
}

bool tok2dir(const deque<string>& tok,deque<string>& res,
	     const set<string>& dirs){
  
  for(int i=0;i<tok.size();i++){
    if(tok[i] == ".."){
      if(res.size() < 3) return false;
      res.pop_back();
      res.pop_back();
      res.pop_back();
    }
    else if(tok[i] == "."){
      if(res.size() < 1) return false;
      res.pop_back();
    }
    else{
      res.push_back(tok[i]);
      string key = tok2str(res);
      if(dirs.find(key) == dirs.end()) return false;
    }
  }

  return true;
}

void shrink(deque<string>& tok,const set<string>& dirs){
  string key = tok2str(tok);
  if(tok[tok.size()-1] == "/"){
    tok.pop_back();
    return;
  }
  else if(tok[tok.size()-1] == "index.html"
	  && dirs.find(key + "/") == dirs.end()){
    tok.pop_back();
    tok.pop_back();
    return;
  }
}

int main(){
  int total_reference;
  int total_suspicious;
  while(~scanf("%d %d",&total_reference,&total_suspicious)){
    if(total_reference == 0 && total_suspicious == 0) break;
    
    set<string> dirs;
    set<string> web_pages;
    for(int i=0;i<total_reference;i++){
      string url;
      cin >> url;
      deque<string> tok = tokenize(url);
      make_set(tok,dirs,web_pages);
    }
    for(int i=0;i<total_suspicious;i++){
      string url1,url2;
      cin >> url1;
      cin >> url2;
      deque<string> tok1 = tokenize(url1);
      deque<string> tok2 = tokenize(url2);
      deque<string> res1;
      deque<string> res2;
      bool isok1 = tok2dir(tok1,res1,dirs);
      bool isok2 = tok2dir(tok2,res2,dirs);
      shrink(res1,dirs);
      shrink(res2,dirs);
      string url1_dir = tok2str(res1);
      string url2_dir = tok2str(res2);

      // cout << "url1:" << url1_dir << endl;
      // cout << "url2:" << url2_dir << endl;
      //search -> same -> web_dir
      if(isok1 && isok2){
	if(url1_dir == url2_dir){
	  if(web_pages.find(url1_dir) != web_pages.end()){
	    printf("yes\n");
	  }
	  else{
	    printf("not found\n");
	  }
	}
	else{
	  if(web_pages.find(url1_dir) == web_pages.end()
	     || web_pages.find(url2_dir) == web_pages.end()){
	    printf("not found\n");
	  }
	  else{
	    printf("no\n");
	  }
	}
      }
      else{
	printf("not found\n");
      }
    }
  }
}
