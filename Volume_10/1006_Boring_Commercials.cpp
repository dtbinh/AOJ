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

using namespace std;

typedef long long ll;
typedef pair <int,int> P;

static const double EPS = 1e-8;

bool is_cm[1441];

int main(){
  int channel_num;
  int watch_begin_time;
  int watch_end_time;
  
  while(~scanf("%d %d %d",&channel_num,&watch_begin_time,&watch_end_time)){
    if(channel_num == 0 
       && watch_begin_time == 0
       && watch_end_time == 0) break;


    memset(is_cm,-1,sizeof(is_cm));

    int watch_begin_minute
      = (watch_begin_time / 100) * 60 + watch_begin_time % 100;
    int watch_end_minute
      = (watch_end_time / 100) * 60 + watch_end_time % 100;

    for(int i=0;i<channel_num;i++){
      int cm_num;
      scanf("%d",&cm_num);

      int org = watch_begin_minute;
      for(int cm_idx=0;cm_idx<cm_num;cm_idx++){
	int cm_begin_time;
	int cm_end_time;
	scanf("%d %d",&cm_begin_time,&cm_end_time);
	int cm_begin_minute 
	  = (cm_begin_time/100) * 60 + cm_begin_time % 100;
	int cm_end_minute 
	  = (cm_end_time/100) * 60 + cm_end_time % 100;

	for(int time = org;time < cm_begin_minute;time++){
	  is_cm[time] = false;
	}

	org = cm_end_minute;

	if(cm_idx == cm_num -1){
	  for(int time = org;time < watch_end_minute;time++){
	    is_cm[time] = false;
	  }
	}
      }
    }

    
    int res = 0;
    int duration = 0;
    for(int time = watch_begin_minute;time<=watch_end_minute;time++){
      res = max(res,duration);
      if(is_cm[time]){
	duration = 0;
	// printf("%d\n",is_cm[time]);
	continue;
      }
      duration++;
    }

    res = max(res,duration);
    printf("%d\n",res);
  }
}
