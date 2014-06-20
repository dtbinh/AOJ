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

const static char weekdays[][4] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
const static char times[][6] = {"Day","Night"};

const char* compute_weekday(int minutes){
  return weekdays[minutes / (60 * 24)];
}

const char* compute_time_band(int minutes){
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

    double probs[101];
    probs[0] = 1.0;
    for(int i=0;i<num_of_egg;i++){
      probs[i+1] = probs[i] * (1.0 - 1.0/(double)inv_mutation_prob);
    }

    double res = 0.0;
    for(int start=0; start < 60 * 24 * 7;start++){
      int init_start = start;
      double prob = 1.0;
      
      for(int round = 0; round < total_stages; round++){
	int time = init_start + wait_hatch;
	if(strcmp(mutation_weekday,"All") != 0
	   && strcmp(compute_weekday(time % (60 * 24 * 7)),mutation_weekday) != 0){
	  init_start += stage_life;
	  continue;
	}
	if(strcmp(mutation_time,"All") != 0
	   && strcmp(compute_time_band(time % (60 * 24 * 7)),mutation_time) != 0){
	  init_start += stage_life;
	  continue;
	}
	prob *= probs[num_of_egg];
	init_start += stage_life;
      }
      res = max(res,1.0-prob);
    }
    printf("%.9lf\n",res);
  }
}
