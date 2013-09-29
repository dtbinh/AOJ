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
 
const static int tx[] = {0,1,1,1,0,-1,-1,-1};
const static int ty[] = {-1,-1,0,1,1,1,0,-1};

struct Data {
  int pos;
  int time;
};

int main(){
  int N;
  while(~scanf("%d",&N)){
    if(N==0) break;

    struct Data stage[41];
    for(int i=1;i<=N;i++){
      int pos,time;
      scanf("%d %d",&pos,&time);
      struct Data d = {pos,time};
      stage[i] = d;
    }
    struct Data s = {0,0};
    stage[0] = s;

    int dp[41][41];//dp[pos][balloonn_num] := min_cost
    memset(dp,0x3f,sizeof(dp));
    dp[0][0] = 0;

    for(int dst_idx=1;dst_idx<=N;dst_idx++){

      int now = stage[dst_idx-1].time;
      
      for(int have_balloon_num=0;have_balloon_num<=3;have_balloon_num++){
	//go straight
	int time_straight = abs(stage[dst_idx].pos - stage[dst_idx-1].pos)
	  * (have_balloon_num + 1);

	//go back home once and ge to the dst
	int time_back_once = stage[dst_idx-1].pos * (have_balloon_num + 1)
	  + stage[dst_idx].pos;
	
	if(now + time_straight <= stage[dst_idx].time
	   && have_balloon_num < 3){
	  dp[dst_idx][have_balloon_num + 1] = 
	    min(dp[dst_idx][have_balloon_num + 1],
		dp[dst_idx-1][have_balloon_num] + abs(stage[dst_idx].pos-stage[dst_idx-1].pos));
	}
	if(now + time_back_once <= stage[dst_idx].time){
	  dp[dst_idx][1] = 
	    min(dp[dst_idx][1],
		dp[dst_idx-1][have_balloon_num]
		+ stage[dst_idx-1].pos + stage[dst_idx].pos
	    );
	}

	// printf("dp[%d][%d]=%d\n",dst_idx,have_balloon_num,dp[dst_idx][have_balloon_num]);

      }
    }

    int min_dist = INF;
    
    for(int have_balloon_num=0;have_balloon_num<=3;have_balloon_num++){
      min_dist = min(min_dist,dp[N][have_balloon_num] + stage[N].pos);
    }
    if(min_dist < INF){
      printf("OK %d\n",min_dist);
    }
    else{
      int stop_idx = 0;
      for(int dst_idx=1;dst_idx<=N;dst_idx++){
	bool isok = false;
	for(int have_balloon_num = 0; have_balloon_num <= 3; have_balloon_num++){
	  if(dp[dst_idx][have_balloon_num] < INF){
	    isok = true;
	    break;
	  }
	}
	if(!isok){
	  stop_idx = dst_idx;
	  break;
	}
      }
      printf("NG %d\n",stop_idx);
    }
  }
}
