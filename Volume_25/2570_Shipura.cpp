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
P sp(int pos,const string& str);
P number(int pos,const string& str);

P expr(int pos,const string& str){
  P p1 = term(pos,str);
  P p2 = sp(p1.first,str);
  pos = p2.first;
  while(pos < str.size()){
    while(str[pos] == '>') pos++; //for '>'
    P p3 = sp(pos,str);
    P p4 = term(p3.first,str);
    cout << p1.second << " >> " << p4.second << endl;
    p1.second >>= min(p4.second,32LL);
    pos = p4.first;
  }
  return P(pos,p1.second);
}

P term(int pos,const string& str){
  if(str[pos] == 'S'){
    P p1 = sp(pos + 1,str);
    p1.first++; // for "<"
    P p2 = sp(p1.first,str);
    P p3 = expr(p2.first,str);
    P p4 = sp(p3.first,str);
    p4.first++; // for ">"
    return P(p4.first,((p3.second % MOD) * (p3.second % MOD)) % MOD);
  }
  
  else{
    return number(pos,str);
  }
}

P sp(int pos,const string& str){
  while(pos < str.size() && str[pos] == ' '){
    pos++;
  }
  return P(pos,0);
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

    cout << str << endl;
    P p = expr(0,str);
    cout << p.second << endl;
  }
}
