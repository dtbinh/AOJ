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
 
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

int main(){
  int total_applicants;
  int working_duration;
  while(~scanf("%d %d",
	       &total_applicants,
	       &working_duration)){
    if(total_applicants == 0) break;

    vector<int> problems;
    for(int applicant_idx = 0; applicant_idx < total_applicants; applicant_idx++){
      int difficulty;
      scanf("%d",&difficulty);
      problems.push_back(difficulty);
    }

    int min_time = INF;
    int times[1001];
    for(int applicant_idx = 0; applicant_idx < total_applicants; applicant_idx++){
      times[applicant_idx] = problems[applicant_idx] * (working_duration/problems[applicant_idx]);
      min_time = min(times[applicant_idx],min_time);
    }

    for(int applicant_idx = 1; applicant_idx < total_applicants; applicant_idx++){

      for(int multiply=0; multiply <= working_duration/problems[applicant_idx]; multiply++){
	bool isok = true;
	int time = problems[applicant_idx] * multiply;
	for(int prev = 0; prev < applicant_idx; prev++){
	  if(time == times[prev]
	     && problems[applicant_idx] < problems[prev]){
	    isok = false;
	    break;
	  }
	  if(time < times[prev]){
	    isok = false;
	    break;
	  }
	}
	
	if(isok){
	  times[applicant_idx] = time;
	  min_time = min(time,min_time);
	  break;
	}
      }
    }

    int count = 0;
    int res;
    int min_diffculty = INF;

    for(int applicant_idx = 0; applicant_idx < total_applicants; applicant_idx++){
      if(min_time == times[applicant_idx]){
	if(min_diffculty > problems[applicant_idx]){
	  count = 1;
	  res = applicant_idx + 1;
	  min_diffculty = problems[applicant_idx];
	}
	else if(min_diffculty == problems[applicant_idx]){
	  count++;
	}
      }
    }

    printf("%d\n",count > 1 ? total_applicants : res);
  }
}





