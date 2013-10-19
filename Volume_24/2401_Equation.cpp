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

struct ParseInfo {
  int pos;
  bool val;
};

set<char> char_set;
bool char_table[256];

ParseInfo parse_formula(int pos, const string& str){

  if('a' <= str[pos] && str[pos] <= 'k'){
    bool val = char_table[str[pos]];
    ParseInfo pi = {pos+1,val};
    return pi;
  }

  else if(str[pos] == 'T'){
    bool val = true;
    ParseInfo pi = {pos+1,val};
    return pi;
  }

  else if(str[pos] == 'F'){
    bool val = false;
    ParseInfo pi = {pos+1,val};
    return pi;
  }

  else if(str[pos] == '-'){
    ParseInfo pi = parse_formula(pos+1,str);
    pi.val = !pi.val;
    return pi;
  }

  else if(str[pos] == '('){
    ParseInfo pi1 = parse_formula(pos+1,str);
    if(str[pi1.pos] == '*'){
      ParseInfo pi2 = parse_formula(pi1.pos+1,str);
      pi2.val = (pi1.val && pi2.val);
      
      //skip ')'
      pi2.pos++;
      return pi2;
    }
    else if(str[pi1.pos] == '+'){
      ParseInfo pi2 = parse_formula(pi1.pos+1,str);
      pi2.val = (pi1.val || pi2.val);

      //skip ')'
      pi2.pos++;
      return pi2;
    }
    else if(str[pi1.pos] == '-'
	    && str[pi1.pos+1] == '>'){
      ParseInfo pi2 = parse_formula(pi1.pos+2,str);
      pi2.val = (!pi1.val || pi2.val);

      //skip ')'
      pi2.pos++;
      return pi2;
    }
  }
}

ParseInfo parse_equation(int pos, const string& str){
  ParseInfo pi1 = parse_formula(pos,str);
  
  //skip '='
  ParseInfo pi2 = parse_formula(pi1.pos+1,str);
  pi2.val = (pi1.val == pi2.val ? true : false);
  return pi2;
}


int main(){
  string str;
  while(cin >> str){
    if(str == "#") break;

    char_set.clear();
    for(int i=0;i<str.size();i++){
      if('a' <= str[i] && str[i] <= 'k'){
	char_set.insert(str[i]);
      }
    }

    bool isok = true;
    for(int S=0;S<=(1<<char_set.size())-1;S++){
      int idx = 0;
      for(set<char>::iterator it = char_set.begin();
	  it != char_set.end();
	  it++){
	char_table[*it] = (S & (1<<idx));
	idx++;
      }
      ParseInfo pi = parse_equation(0,str);
      if(!pi.val) isok = false;
    }
    printf("%s\n",isok ? "YES" : "NO");
  }
}
