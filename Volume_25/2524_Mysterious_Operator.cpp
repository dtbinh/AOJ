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

class MysteriousNumber{

public:
  int num;
  int operator+(const MysteriousNumber& mn){
    return (num - mn.num) * fast_pow(10,compute_digit(num+mn.num))
      + (num+mn.num);
  }
  MysteriousNumber(int _n) : num(_n){}

private:
  int compute_digit(int n){
    int res = 0;
    while(n > 0){
      n/=10;
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

};
int main(){
  string str;
  while(cin >> str){
    int whole = atoi(str.c_str());
    int res = 0;
    for(int len=0;len<str.size();len++){
      string front_str = str.substr(0,len);
      string rear_str = str.substr(len,str.size()-len);
      int front_num = atoi(front_str.c_str());
      int rear_num = atoi(rear_str.c_str());

      if((rear_num - front_num) < 0) continue;
      if((rear_num - front_num) % 2 != 0) continue;

      MysteriousNumber b((rear_num - front_num) / 2);
      MysteriousNumber a(front_num + b.num);
      if(a + b == whole){
	res++;
      }
    }
    printf("%d\n",res);
  }
}
