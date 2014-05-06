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

int dp[1001][9];

int main(){
  int total_days;
  while(~scanf("%d",&total_days)){
    string must_attend_persons;
    cin >> must_attend_persons;

    must_attend_persons = "J" + must_attend_persons;

    memset(dp,0,sizeof(dp));

    //J:=0 O:=1 I:=2
    dp[0][(1<<0)] = 1;

    map<char,int> name2idx;
    name2idx['J'] = 0;
    name2idx['O'] = 1;
    name2idx['I'] = 2;

    for(int day=1;day<=total_days;day++){
      //J:=0 O:=1 I:=2
      for(int prev_attendance=0;prev_attendance<=(1<<3)-1;prev_attendance++){
	for(int next_attendance=0;next_attendance<=(1<<3)-1;next_attendance++){
	  if(__builtin_popcount(prev_attendance & next_attendance) == 0) continue;
	  if(!(next_attendance & (1<<name2idx[must_attend_persons[day]]))) continue;
	  
	  dp[day][next_attendance]
	    += dp[day-1][prev_attendance];
	  dp[day][next_attendance] %= 10007;
	}
      }
    }
    
    int res = 0;
    for(int attendance=0;attendance<=(1<<3)-1;attendance++){
      res += dp[total_days][attendance];
      res %= 10007;
    }
    printf("%d\n",res);
  }
}
