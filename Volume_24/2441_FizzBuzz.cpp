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

ll fast_pow(ll x, ll n) {
  ll res = 1;
  while(n > 0) {
    if (n & 1) res = res * x;
    x = x * x;
    n >>= 1;
  }
  return res;
}

ll ComputeCharLength(ll turn_count){
  int upper_digit = 0;

  ll tmp = turn_count;
  while(tmp > 0){
    tmp /= 10LL;
    upper_digit++;
  }

  ll res = 0;
  for(int digit=1;digit <= upper_digit; digit++){
    ll remaining_nums = 0;
    ll current_max = 0;
    if(digit == upper_digit){
      current_max = turn_count;
      //ex... 132 - 100 + 1
      remaining_nums = turn_count - fast_pow(10,digit-1)+1;
    }
    else{
      //ex... 100 - 1 -> 99
      current_max = fast_pow(10,digit) - 1;

      //ex... ((100-1) - 10) + 1
      remaining_nums = (fast_pow(10,digit)-1) - fast_pow(10,digit-1)+1;
    }
    
    //ex... 133/3 - (100 - 1)/3
    ll fizz_count = current_max / 3 - (fast_pow(10,digit-1)-1) / 3;

    //ex... 133/5 - (100 - 1)/5
    ll buzz_count = current_max / 5 - (fast_pow(10,digit-1)-1) / 5; 

    //ex... 133/15 - (100 - 1)/15
    ll fizzbuzz_count = current_max / 15 - (fast_pow(10,digit-1)-1) / 15;

    ll current_total = (fizz_count+buzz_count-2*fizzbuzz_count)*4
      + fizzbuzz_count*8
      + (remaining_nums - (fizz_count+buzz_count-fizzbuzz_count)) * digit;
    res += current_total;
  }

  return res;
}

int main(){
  ll num;
  while(~scanf("%ld",&num)){

    ll lhs = 0;
    ll rhs = fast_pow(10,18);

    for(int i=0;i<100;i++){
      ll mid = (lhs + rhs)/2LL;
      if(ComputeCharLength(mid) < num){
	lhs = mid;
      }
      else if(ComputeCharLength(mid) >= num){
	rhs = mid;
      }
    }

    string res = "";
    for(ll turn=rhs;turn<=lhs+20;turn++){
      if(turn % 15 == 0){
	res += "FizzBuzz";
      }
      else if(turn % 5 == 0){
	res += "Buzz";
      }
      else if(turn % 3 == 0){
	res += "Fizz";
      }
      else{
	char buf[32];
	sprintf(buf,"%ld",turn);
	res += buf;
      }
    }
    
    printf("%s\n",res.substr(num-ComputeCharLength(lhs)-1,20).c_str());
  }
}


