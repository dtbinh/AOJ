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
typedef pair <int,ll> P;
  
static const double EPS = 1e-8;
static const ll MOD = 1000000007;

int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};

P expr(int pos,const string& str);
P term(int pos,const string& str);
P number(int pos,const string& str);

P expr(int pos,const string& str){
  P p1 = term(pos,str);
  pos = p1.first;

  while(pos + 2 < str.size() 
	&& str[pos] == '>'
	&& str[pos+1] == '>'
	&& (isdigit(str[pos+2]) || str[pos+2] == 'S')){
    while(str[pos] == '>') pos++; //for '>'
    P p2 = term(pos,str);
    p1.second >>= min(p2.second,63LL);
    pos = p2.first;
  }
  return P(pos,p1.second);
}

P term(int pos,const string& str){
  if(str[pos] == 'S'){
    pos+=2; // for "S<"
    P p1 = expr(pos,str);
    pos = p1.first;
    pos++; // for ">"
    return P(pos,((p1.second % MOD) * (p1.second % MOD)) % MOD);
  }
  
  else{
    return number(pos,str);
  }
}

P number(int pos,const string& str){
  
  string tmp = "0";
  while(pos < str.size() && isdigit(str[pos])){
    tmp.push_back(str[pos]);
    pos++;
  }
  return P(pos,atol(tmp.c_str()));
}

int main(){
  string str;
  while(getline(cin,str)){
    if(str == "#") continue;

    string tmp = "";
    for(int i=0;i<str.size();i++){
      if(str[i] != ' '){
	tmp.push_back(str[i]);
      }
    }
    str = tmp;
    P p = expr(0,str);
    cout << p.second % MOD << endl;
  }
}
