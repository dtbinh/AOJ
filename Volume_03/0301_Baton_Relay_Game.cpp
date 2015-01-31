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
 
const static int tx[] = {0,1,0,-1};
const static int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

struct Student {
  bool win;
  int next;
  int prev;
  Student(bool _win,int _prev,int _next)
    : win(_win),prev(_prev),next(_next) {}
};

int main(){
  int total_students;
  int total_repeat_count;
  int total_questions;
  while(~scanf("%d %d %d",
	       &total_students,
	       &total_repeat_count,
	       &total_questions)){

    vector<Student> students;
    for(int student_i = 0; student_i < total_students; student_i++){
      students.push_back(Student(true,
				 ((student_i - 1) + total_students) % total_students,
				 (student_i + 1) % total_students));
    }
    
    int current_pos = 0;

    for(int repeat_i = 0; repeat_i < total_repeat_count; repeat_i++){
      int target;
      scanf("%d",&target);
      int limit = target;
      while(limit > 0){
	if(target % 2 == 0){
	  current_pos = students[current_pos].next;
	}
	else{
	  current_pos = students[current_pos].prev;
	}
	limit--;
      }

      students[current_pos].win = false;
      students[students[current_pos].prev].next
	= students[current_pos].next;
      students[students[current_pos].next].prev
	= students[current_pos].prev;
      current_pos = students[current_pos].next;
    }

    for(int question_i = 0; question_i < total_questions; question_i++){
      int query;
      scanf("%d",&query);
      printf("%d\n",students[query].win ? 1 : 0);
    }
  }
}
