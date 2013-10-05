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
  int cycle_length,interview_num;
  int cycle[100];
  map<int,vector<int> > interview;

  while(~scanf("%d",&cycle_length)){
    if(cycle_length == 0) break;
    for(int i=0;i<cycle_length;i++){
      scanf("%d",cycle+i);
    }
    scanf("%d",&interview_num);
  
    int last_day = 0;
    for(int i=0;i<interview_num;i++){
      int day,start_hour;
      scanf("%d %d",&day,&start_hour);
      interview[day].push_back(start_hour);
      last_day = max(day,last_day);
    }

    //dp[day][cycle_idx] = min_cost
    int dp[101][100];
    memset(dp,0x3f,sizeof(dp));

    //init
    dp[1][0] = 0;
    for(int i=0;i<cycle_length;i++){
      dp[0][i] = 0;
    }

    for(int day=1;day<=last_day;day++){
      for(int cycle_idx=0;cycle_idx < cycle_length; cycle_idx++){
	for(int hour_idx=0;hour_idx<interview[day].size();hour_idx++){
	  int start_hour = interview[day][hour_idx];
	  if(cycle[(cycle_idx+1)%cycle_length] <= start_hour){
	    dp[day][(cycle_idx+1)%cycle_length]
	      = min(dp[day-1][cycle_idx],dp[day][(cycle_idx+1)%cycle_length]);
	  }
	  dp[day][0] = min(dp[day-1][cycle_idx]+1,dp[day][0]);
	}
      }
    }
  
    int min_v = INF;
    for(int i=0;i<cycle_length;i++){
      min_v = min(dp[last_day][i],min_v);
    }
    printf("%d\n",min_v);
  }
}
