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
    vector<int> student_scores;
    vector<int> sorted_student_scores;
    for(int student_i = 0; student_i < total_students; student_i++){
      int score;
      scanf("%d",&score);
      student_scores.push_back(score);
      sorted_student_scores.push_back(score);;
    }

    sort(sorted_student_scores.begin(),sorted_student_scores.end());

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
	  leader_scores.push_back(student_scores[*leader_it]);

	}
	sort(leader_scores.begin(),leader_scores.end());
	
	int rhs = INF;
	int lhs = 0;

	for(int round = 0; round < 50; round++){
	  int mid = lhs + (rhs - lhs) / 2;
	  int prev = 0;
	  int fail_sum = 0;
	  for(int leader_i = 0; leader_i < leader_scores.size(); leader_i++){
	    int score = leader_scores[leader_i];
	    int current= lower_bound(sorted_student_scores.begin(),
				 sorted_student_scores.end(),
				 score - mid)
	      - sorted_student_scores.begin();
	    int fail = max(0,current - prev);
	    fail_sum += fail;
	    prev = upper_bound(sorted_student_scores.begin(),
			       sorted_student_scores.end(),score)
	      - sorted_student_scores.begin();
	  }
	  fail_sum += max(total_students - prev,0);

	  if(fail_sum > num){
	    lhs = mid;
	  }
	  else{
	    rhs = mid;
	  }
	}

	if(rhs < INF){
	  printf("%d\n",rhs);
	}
	else{
	  printf("NA\n");
	}
      }
    }
  }
}
