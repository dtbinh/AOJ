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

struct Team{
public:
  int solved;
  int elapsed_time;
  int penalty;
  int id;
  Team() : solved(0),elapsed_time(0),penalty(0),id(0){}
  bool operator<(const Team& t) const{
    if(__builtin_popcount(solved) == __builtin_popcount(t.solved)){
      if((elapsed_time + penalty) == (t.elapsed_time + t.penalty)){
	return id > t.id;
      }
      else{
	return ((elapsed_time + penalty) < (t.elapsed_time + t.penalty)); 
      }
    }
    else{
      return (__builtin_popcount(solved) > __builtin_popcount(t.solved));
    }
  }
  bool operator==(const Team& t) const{
    if(__builtin_popcount(solved) == __builtin_popcount(t.solved)
       && (elapsed_time + penalty) == (t.elapsed_time + t.penalty)){
      return true;
    }
    return false;
  }
};

int main(){
  int duration;
  int total_teams;
  int total_problems;
  int total_submission_records;
  while(~scanf("%d %d %d %d",
	       &duration,
	       &total_teams,
	       &total_problems,
	       &total_submission_records)){

    if(duration == 0
       && total_teams == 0
       && total_problems == 0
       && total_submission_records == 0) break;

    Team teams[51];
    int freq[51][11];
    
    memset(freq,0,sizeof(freq));
    for(int team_idx=0;team_idx < total_teams; team_idx++){
      teams[team_idx].id = team_idx+1;
    }
    for(int submit_idx=0;submit_idx< total_submission_records; submit_idx++){
      int elapsed_time;
      int team_number;
      int problem_number;
      int judgement;
      scanf("%d %d %d %d",
	    &elapsed_time,
	    &team_number,
	    &problem_number,
	    &judgement);
      if(judgement == 0){
	teams[team_number-1].elapsed_time
	  += elapsed_time;
	teams[team_number-1].penalty
	  += freq[team_number-1][problem_number-1] * 20;
	freq[team_number-1][problem_number-1] = 0;
	teams[team_number-1].solved |= (1<<(problem_number-1));
      }
      else{
	if(!(teams[team_number-1].solved & (1<<(problem_number-1)))){
	  freq[team_number-1][problem_number-1]++;
	}
      }
    }

    sort(teams,teams+total_teams);
    for(int team_idx=0;team_idx+1 < total_teams; team_idx++){
      if(teams[team_idx] == teams[team_idx+1]){
	printf("%d=",teams[team_idx].id);
      }
      else{
	printf("%d,",teams[team_idx].id);
      }
    }
    printf("%d\n",teams[total_teams-1].id);
  }
}
