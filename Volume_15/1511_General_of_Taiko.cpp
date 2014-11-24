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

double dp[101][11][101][11][5];//dp[note_i][prev_combo][prev_score][prev_stability][prev_action]

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

    for(int prev_combo = 10; prev_combo >= 0; prev_combo--){
      for(int prev_action = 4; prev_action >= 0; prev_action--){
	for(int prev_stability = 10; prev_stability >= 0; prev_stability--){
	  dp[len][prev_combo][100][prev_stability][prev_action] = 1.0;
	}
      }
    }

    //dp[note_i][prev_combo][prev_score][prev_stability][prev_action]
    for(int note_i = len - 1; note_i >= 0; note_i--){
      if(notes[note_i] == 0){
	for(int prev_score = 100; prev_score >= 0; prev_score--){
	  for(int prev_combo = 10; prev_combo >= 0; prev_combo--){
	    for(int prev_stability = 10; prev_stability >= 0; prev_stability--){
	      for(int prev_action = 4; prev_action >= 0; prev_action--){
		dp[note_i][prev_combo][prev_score][prev_stability][prev_action]
		  = dp[note_i + 1][prev_combo][prev_score][10][4];
	      }
	    }
	  }
	}
      }	      
      else if(notes[note_i] > 0){
	int offset = (notes[note_i] == 1 ? 0 : 2);
	for(int prev_score = 100; prev_score >= 0; prev_score--){
	  for(int prev_combo = 10; prev_combo >= 0; prev_combo--){
	    int added = (A + B * prev_combo) / 100;

	    for(int prev_stability = 10; prev_stability >= 0; prev_stability--){
	      for(int prev_action = 3; prev_action >= 0; prev_action--){
		dp[note_i][prev_combo][prev_score][prev_stability][prev_action] 
		  = dp[note_i + 1][0][prev_score][10][4];

		int st0 = max(0,(stability[prev_action][offset + 0] - 10) * 10 + prev_stability * 10);
		int st1 = max(0,(stability[prev_action][offset + 1] - 10) * 10 + prev_stability * 10);
		
		double precision0 = (double)st0/100.0;
		double precision1 = (double)st1/100.0;


		//bang
		dp[note_i][prev_combo][prev_score][prev_stability][prev_action] 
		  = max(dp[note_i][prev_combo][prev_score][prev_stability][prev_action] ,
			dp[note_i + 1][min(10,prev_combo + 1)][min(100,prev_score + added)][st0 / 10][offset + 0] * precision0
			+ dp[note_i + 1][0][prev_score][st0 / 10][offset + 0] * (1.0 - precision0));

		dp[note_i][prev_combo][prev_score][prev_stability][prev_action] 
		  = max(dp[note_i][prev_combo][prev_score][prev_stability][prev_action],
			dp[note_i + 1][min(10,prev_combo + 1)][min(100,prev_score + added)][st1 / 10][offset + 1] * precision1
			+ dp[note_i + 1][0][prev_score][st1 / 10][offset + 1] * (1.0 - precision1));
		
	      }

	      //ignore
	      dp[note_i][prev_combo][prev_score][prev_stability][4]
	      	= max(dp[note_i + 1][0][prev_score][10][4],
	      	      max(dp[note_i + 1][min(10,prev_combo + 1)][min(100,prev_score + added)][10][offset + 0],
	      		  dp[note_i + 1][min(10,prev_combo + 1)][min(100,prev_score + added)][10][offset + 1]));

	    }
	  }
	}
      }
    }
    printf("%.6lf\n",dp[0][0][0][10][4]);
  }
  over:;

}
