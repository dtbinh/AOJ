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

double dp[101][101][101][12][4];//dp[note_i][prev_combo][prev_score][prev]

int main(){
  while(true){
    //lt rt lk rk
    int stability[4][4];
    for(int i = 0; i < 4; i++){
      int count = 0;
      for(int j = 0; j < 4; j++){
	scanf("%d",&stability[i][j]);
	if(i == 0 && stability[i][j] == -1){
	  count++;
	}
      }
      if(count >= 4) goto over;
    }
    int len;
    scanf("%d",&len);
    
    int notes[101];
    
    //0:none 1:t 2:k
    for(int note_i = 0; note_i < len; note_i++){
      scanf("%d",&notes[note_i]);
    }
    int A,B;
    scanf("%d %d",&A,&B);
    
    memset(dp,0,sizeof(dp));

    dp[0][0][0][10][0] = 1.0;

    //dp[note_i][prev_combo][prev_score][prev]
    for(int note_i = 0; note_i < len; note_i++){
      for(int prev_combo = 0; prev_combo <= note_i; prev_combo++){
	for(int next = 0; next < 4; next++){
	  //t or k
	  int added = 0;
	  if(next/2 + 1 == notes[note_i]){
	    added = (A + B * min(prev_combo + 1,10)) / 100;
	  }
	  else {
	    added = (A + B * min(0,10)) / 100;
	  }

	  for(int prev_score = 100; prev_score >= 0; prev_score--){
	    if(prev_score + added >= 100) continue;

	    for(int prev = 0; prev < 4; prev++){
	      for(int prev_st = 0; prev_st <= 10; prev_st++){
		int st = stability[prev][next];
		double precision = (double)max(0,(st - 10) * 10 + prev_st) / 100.0;
		if(note_i == 0) precision = 1.0;

		dp[note_i+1][prev_combo + 1][prev_score + added][st][next]
		  += dp[note_i][prev_combo][prev_score][prev_st][prev] * precision;

		dp[note_i+1][0][prev_score][st][next]
		  += dp[note_i][prev_combo][prev_score][prev_st][prev] * (1.0-precision);
	      }
	    }
	  }
	}
      }
    }
    
    double res = 0.0;
    for(int score = 0; score < 100; score++){
      for(int combo = 0; combo <= len; combo++){
	for(int prev_st = 0; prev_st <= 10; prev_st++){
	  for(int next = 0; next < 4; next++){
	    res += dp[len][combo][score][prev_st][next];
	  }
	}
      }
    }
    printf("%.6lf\n",1.0 - res);
  }
  over:;

}
