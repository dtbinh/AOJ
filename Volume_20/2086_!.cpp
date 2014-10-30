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

unsigned long long conv(int base,const string& fact){
  unsigned long long res = 0;
  unsigned long long digit = 1;
  for(int i = fact.size() - 1; i >= 0; i--){
    if('A' <= fact[i] &&  fact[i] <= 'Z'){
      res += (fact[i] - 'A' + 10) * digit;
      digit *= base;
    }
    else{
      res += (fact[i] - '0') * digit;
      digit *= base;
    }
  }
  return res;
}

int main(){
  int base;
  string fact;
  while(cin >> base >> fact){
    if(base == 0 && fact == "0") break;
    unsigned long long num = conv(base,fact);
    int count[6] = {};
    while(num > 0){
      unsigned long long tmp = num;
      while(tmp % 2 == 0){
	tmp /= 2;
	count[2]++;
      }
      while(tmp % 5 == 0){
	tmp /= 5;
	count[5]++;
      }
      num--;
    }

    printf("%d\n",min(count[2],count[5]));
  }
}
