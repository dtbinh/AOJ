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

double dp[101][101][101][11][4];//dp[note_i][prev_combo][prev_score][prev_st][prev]

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

    dp[0][0][0][0][0] = 1.0;

    //dp[note_i][prev_combo][prev_score][prev_st][prev]
    for(int note_i = 0; note_i < len; note_i++){
      for(int prev_combo = note_i; prev_combo >= 0; prev_combo--){
	for(int prev = 0; prev < 4; prev++){
	  for(int prev_st = 10; prev_st >= 0; prev_st--){
	    for(int prev_score = 100; prev_score >= 0; prev_score--){
	      if(notes[note_i] == 0){
		dp[note_i+1][0][prev_score][10][prev]
		  += dp[note_i][prev_combo][prev_score][prev_st][prev];
	      }
	      
	      else if(notes[note_i] == 1){
		int st0 = max(0,(stability[prev][0] - 10) * 10 + prev_st * 10);
		int st1 = max(0,(stability[prev][1] - 10) * 10 + prev_st * 10);
		int added = (A + B * min(prev_combo + 1,10)) / 100;

		if(note_i == 0) st0 = st1 = 100;
		double precision0 = (double)st0/100.0;
		double precision1 = (double)st1/100.0;

		//correct
		if(prev_score + added < 100){
		  dp[note_i+1][prev_combo + 1][prev_score + added][st0 / 10][0]
		    += dp[note_i][prev_combo][prev_score][prev_st][prev] * precision0;
		  // dp[note_i+1][prev_combo + 1][prev_score + added][st1 / 10][1]
		  //   += dp[note_i][prev_combo][prev_score][prev_st][prev] * precision1;
		}

		//mistake
		dp[note_i+1][0][prev_score][st0 / 10][0]
		  += dp[note_i][prev_combo][prev_score][prev_st][prev] * (1.0 - precision0);
		// dp[note_i+1][0][prev_score][st1 / 10][1]
		//   += dp[note_i][prev_combo][prev_score][prev_st][prev] * (1.0 - precision1);

		//ignore
		// dp[note_i+1][0][prev_score][10][prev]
		//   += dp[note_i][prev_combo][prev_score][prev_st][prev];
	      }
	      else if(notes[note_i] == 2){
		int st2 = max(0,(stability[prev][2] - 10) * 10 + prev_st * 10);
		int st3 = max(0,(stability[prev][3] - 10) * 10 + prev_st * 10);
		int added = (A + B * min(prev_combo + 1,10)) / 100;
		if(note_i == 0) st2 = st3 = 100;
		double precision2 = (double)st2/100.0;
		double precision3 = (double)st3/100.0;

		if(prev_score + added < 100){
		  dp[note_i+1][prev_combo + 1][prev_score + added][st2 / 10][2]
		    += dp[note_i][prev_combo][prev_score][prev_st][prev] * precision2;
		  dp[note_i+1][prev_combo + 1][prev_score + added][st3 /10][3]
		    += dp[note_i][prev_combo][prev_score][prev_st][prev] * precision3;
		}

		dp[note_i+1][0][prev_score][st2 / 10][2]
		  += dp[note_i][prev_combo][prev_score][prev_st][prev] * (1.0 - precision2);
		dp[note_i+1][0][prev_score][st3 / 10][3]
		  += dp[note_i][prev_combo][prev_score][prev_st][prev] * (1.0 - precision3);
	      }
	    }
	  }
	}
      }
    }
    
    double res = 0.0;

    for(int score = 0; score <= 100; score++){
      double tmp = 0;
      for(int prev_st = 0; prev_st <= 10; prev_st++){
	for(int combo = 0; combo <= len; combo++){
	  for(int next = 0; next < 4; next++){
	    res += dp[len][combo][score][prev_st][next];
	    tmp += dp[len][combo][score][prev_st][next];
	  }
	}
      }
      printf("%d %.6lf\n",score,tmp);
    }
    printf("%.6lf\n",1.0 - res);
  }
  over:;

}
