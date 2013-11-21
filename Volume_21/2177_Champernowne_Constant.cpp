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

int main(){
  ll place_idx,total_digits;
  while(~scanf("%lld %lld",&place_idx,&total_digits)){
    if(place_idx==0 && total_digits==0) break;
    //1~9 : 0-1+1=1*9
    //10~99 : 99-10+1=2*90
    //100~999 : 999-100+1=3*900
    //1000~9999 : 9999-1000+1=4*9000
    //10000~99999 : 99999-10000+1=5*90000
    //100000~999999 : 999999-100000+1=6*900000
    //1000000~9999999 : 9999999-1000000+1=7*9000000
    //10000000~99999999 : 99999999-10000000+1=8*90000000
    //100000000~999999999 : 999999999-100000000+1=9*900000000
    //1000000000~9999999999 : 9999999999-1000000000+1=10*9000000000
    
    const ll sum[] = {9,2*90,3*900,4*9000,5*90000,
		      6*900000LL,7*9000000LL,8*90000000LL,9*900000000LL,10*9000000000LL,
		      11*90000000000LL};
    ll base = 0;
    int digits = 0;
    ll first = 1;
    for(int i=0;i<10;i++){
      if(base + sum[i] >= place_idx){
	digits = i + 1;
	break;
      }
      base += sum[i];
      first *= 10LL;
    }
    
    int relative_idx = (place_idx - base - 1);

    // printf("place_idx:%d\n",place_idx);
    // printf("relative_idx:%d\n",relative_idx);
    string str = "";
    
    for(ll i=first+relative_idx/digits;i<=first+relative_idx/digits + 100;i++){
      stringstream ss;
      string tmp;
      ss << i;
      ss >> tmp;
      str += tmp;
    }

    cout << str.substr(relative_idx%digits,total_digits) << endl;
  }
}
