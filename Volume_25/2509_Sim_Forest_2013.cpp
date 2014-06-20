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
  
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};

const char* compute_weekday(int minutes){
  const static char weekdays[][4] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
  return weekdays[minutes / (60 * 24)];
}

const char* compute_time_band(int minutes){
  const static char times[][6] = {"Day","Night"};
  
  int idx = 0;
  if(minutes % (60 * 24) >= 6 * 60
     && minutes % (60 * 24) < 18 * 60){
    idx = 0;
  }
  else{
    idx = 1;
  }
  return times[idx];
}


int main(){
  int wait_hatch;
  int num_of_egg;
  int stage_life;
  char mutation_weekday[4];
  char mutation_time[6];
  int inv_mutation_prob;
  int total_stages;
  while(~scanf("%d %d %d %s %s %d %d",
	       &wait_hatch,
	       &num_of_egg,
	       &stage_life,
	       mutation_weekday,
	       mutation_time,
	       &inv_mutation_prob,
	       &total_stages)){
    
    if(total_stages == 0) break;


    double res = 0.0;
    for(int start=0; start < 60 * 24 * 7;){
      int init_start = start;
      int time = start;
      double prob = 1.0;
      for(int round = 0; round < total_stages; round++){
	for(; time < init_start + stage_life; time++){
	  if(strcmp(mutation_weekday,"All") != 0
	     && strcmp(compute_weekday(time),mutation_weekday) != 0) continue;
	  if(strcmp(mutation_time,"All") != 0
	     && strcmp(compute_time_band(time),mutation_time) != 0) continue;

	  if(time - init_start == wait_hatch){
	    for(int i=0;i<num_of_egg;i++){
	      prob *= (1.0 - 1.0/(double)inv_mutation_prob);
	    }
	  }
	}
	init_start = time;
      }

      start++;
      res = max(res,1.0-prob);
    }
    printf("%.9lf\n",res);
  }
}
