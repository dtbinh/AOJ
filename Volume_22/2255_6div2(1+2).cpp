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
 
const int tx[] = {+0,+1,+0,-1};
const int ty[] = {-1,+0,+1,+0};
 
static const double EPS = 1e-8;

struct ParseResult{
  int pos;
  int num;
  ParseResult(int pos,int num) : 
    pos(pos),num(num) {}
  ParseResult();
};

ParseResult expr(int pos,const string& str);
ParseResult factor(int pos,const string& str);
ParseResult term(int pos,const string& str);
ParseResult num(int pos,const string& str);

ParseResult expr(int pos,const string& str){
  ParseResult r = factor(pos,str);
  while(r.pos < str.size() && str[r.pos] == '+'){
    ParseResult tmp = factor(pos+1,str);
    r.num += tmp.num;
    r.pos = tmp.pos;
  }
  while(r.pos < str.size() && str[r.pos] == '-'){
    ParseResult tmp = factor(pos+1,str);
    r.num -= tmp.num;
    r.pos = tmp.pos;
  }
  return r;
}

ParseResult factor(int pos, const string& str){
  ParseResult r = term(pos,str);
  while(r.pos < str.size() && str[r.pos] == '*'){
    ParseResult tmp = term(r.pos+1,str);
    r.num *= tmp.num;
    r.pos = tmp.pos;
  }
  while(r.pos < str.size() && str[r.pos] == '/'){
    ParseResult tmp = term(r.pos+1,str);
    r.num /= tmp.num;
    r.pos = tmp.pos;
  }
  return r;
}

ParseResult term(int pos, const string& str){
  if(str[pos] == '('){
    ParseResult r = expr(pos+1,str);
    r.pos++; // for ')'
    return r;
  }
  else if(isdigit(str[pos])){
    return num(pos,str);
  }
}

ParseResult num(int pos,const string& str){
  int sum = 0;
  while(pos < str.size() && isdigit(str[pos])){
    sum *= 10;
    sum += str[pos] - '0';
    pos++;
  }
  return ParseResult(pos,sum);
}

int main(){
  string str;
  while(cin >> str){
    if(str == "#") break;
    ParseResult r = expr(0,str);
    cout << r.num << endl;
  }
}
