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
  int total_students;
  int total_queries;
  while(~scanf("%d %d",&total_students,&total_queries)){
    vector<int> scores;
    for(int student_i = 0; student_i < total_students; student_i++){
      int score;
      scanf("%d",&score);
      scores.push_back(score);
    }
    set<int> leaders;
    for(int query_i = 0; query_i < total_queries; query_i++){
      string operation;
      int num;
      cin >> operation >> num;
      if(operation == "ADD"){
	leaders.insert(num - 1);
      }
      else if(operation == "REMOVE"){
	leaders.erase(lower_bound(leaders.begin(),leaders.end(),num - 1));
      }
      else if(operation == "CHECK"){
	vector<int> leader_scores;

	for(set<int>::iterator leader_it = leaders.begin(); leader_it != leaders.end(); leader_it++){
	  leader_scores.push_back(scores[*leader_it]);
	}
	sort(leader_scores.begin(),leader_scores.end());

	priority_queue<int> diff_log;
	for(int score_i = 0; score_i < scores.size(); score_i++){
	  if(!binary_search(leaders.begin(),leaders.end(),score_i)){
	    int score = scores[score_i];
	    int pos = lower_bound(leader_scores.begin(),leader_scores.end(),score) - leader_scores.begin();
	    if(pos == leader_scores.size()){
	      diff_log.push(INF);
	    }
	    else if(pos <leader_scores.size()){
	      int diff = leader_scores[pos] - score;
	      if(diff >= 0){
		diff_log.push(diff);
	      }
	      else{
		diff_log.push(INF);
	      }
	    }
	  }
	}
	while(num > 0 && !diff_log.empty()){
	  diff_log.pop();
	  num--;
	}
	if(!diff_log.empty()){
	  if(diff_log.top() == INF){
	    printf("NA\n");
	  }
	  else{
	    printf("%d\n",diff_log.top());
	  }
	}
	else{
	  printf("%d\n",0);
	}
      }
    }
  }
}
