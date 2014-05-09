#define _USE_MATH_DEFINES
#define INF 100000000
 
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

int main(){
  int total_songs;
  int cyalume;
  while(~scanf("%d %d",
	       &total_songs,
	       &cyalume)){
    
    int dp[51][51][51]; //prev next accumulate
    dp[0][0][0] = 0;
    for(int song_idx=0;song_idx < total_songs;song_idx++){
      int level2_satisfaction,level1_satisfaction,none_satisfaction;
      scanf("%d %d %d",
	    &level2_satisfaction,
	    &level1_satisfaction,
	    &none_satisfaction);
      for(int prev=0;prev<=song_idx;prev++){
	for(int next=0;next<=song_idx;next++){
	  for(int accumulate=0;accumulate<=song_idx;accumulate++){
	    
	  }
	}
      }
    }
  }
}
