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

struct State{
  ll num;
  int pos;
  bool is_over_flow;
  State(int _n,int _p,bool _o) : num(_n),pos(_p),is_over_flow(_o) {}
  State() : num(0),pos(0),is_over_flow(false) {}
};

ll compute_digit(ll num){
  ll res = 0;
  while(num > 0){
    num /= 10;
    res++;
  }
  return res;
}

ll fast_pow(ll x, ll n){
  ll res = 1;
  while(n > 0) {
    if (n & 1) res = res * x;
    x = x * x;
    n >>= 1;
  }
  return res;
}


State parse_mono(const string& str,int pos,ll n){
  if(str[pos] == 'n' && str[pos+1] == '^'){
    ll num = str[pos+2]-'0';
    int digit = compute_digit(n) * num;
    State s;

    if(digit > 10){
      s.is_over_flow = true;
      s.num = 0;
      s.pos = pos+3;
    }
    else{
      s.is_over_flow = false;
      s.num = fast_pow(n,num);
      s.pos = pos+3;
    }
    return s;
  }
}

State parse_poly(const string& str,int pos,ll n){
  State res;

  if(pos < str.size() && str[pos] != '+') {
    State s = parse_mono(str,pos,n);
    res.num += s.num;
    res.is_over_flow |= s.is_over_flow;
    pos = s.pos;
  }

  while(pos < str.size() && str[pos] == '+'){
    State s = parse_mono(str,pos+1,n);
    res.num += s.num;
    res.is_over_flow |= s.is_over_flow;
    pos = s.pos;
  }

  return res;
}

int main(){
  ll n,T;
  while(~scanf("%lld %lld",&n,&T)){
    string str;
    cin >> str;
    State s = parse_poly(str,0,n);
    if(s.is_over_flow || s.num * T > 1000000000LL){
      cout << "TLE" << endl;
    }
    else{
      cout << s.num * T << endl;
    }
  }
}
