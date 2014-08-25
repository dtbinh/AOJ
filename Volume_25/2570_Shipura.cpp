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
  
static const double EPS = 1e-8;
static const int MOD = 1000000007;

int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};

P expr(int pos,const string& str);
P term(int pos,const string& str);
P sp(int pos,const string& str);
P number(int pos,const string& str);

P expr(int pos,const string& str){
  if(isdigit(str[pos]) || str[pos] == 'S'){
    P p = term(pos,str);
    return p;
  }
  
  while(pos < str.size()){
    P p1 = expr(pos,str);
    P p2 = sp(p1.first,str);
    while(str[p2.first] == '>') p2.first++; //for '>'
    P p3 = sp(p2.first,str);
    P p4 = term(p3.first,str);

    cout << p1.second << endl;
    int val = p1.second / pow(2.0,(double)p4.second);
    cout << val << endl;
    return P(p4.first,val);
  }
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
  
  string tmp = "";
  while(pos < str.size() && isdigit(str[pos])){
    tmp.push_back(str[pos]);
    pos++;
  }
  return P(pos,atoi(tmp.c_str()));
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
