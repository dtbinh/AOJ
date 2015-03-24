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
#include <assert.h>
  
using namespace std;
  
typedef long long ll;
typedef pair <int,int> P;
typedef pair <double,P> PP;
  
static const double EPS = 1e-8;

int num_of_desks;
int book_limit;
int num_of_students;

int take_book(int id,deque<int> desks[101]){
  for(int desk_i = 0; desk_i < num_of_desks; desk_i++){
    for(int i = 0; i < desks[desk_i].size(); i++){
      if(desks[desk_i][i] == id){
	deque<int> tmp;
	for(int j = 0; j < desks[desk_i].size(); j++){
	  if(desks[desk_i][j] == id) continue;
	  tmp.push_back(desks[desk_i][j]);
	}
	desks[desk_i] = tmp;
	return desk_i + 1;
      }
    }
  }
  return num_of_desks + 1;
}

int main(){
  while(~scanf("%d %d %d",&num_of_desks,&book_limit,&num_of_students)){
    if(num_of_desks == 0
       && book_limit == 0
       && num_of_students == 0) break;
    vector<int> students[101];
    int max_request = 0;
    for(int student_i = 0; student_i < num_of_students; student_i++){
      int num_of_books_requested;
      scanf("%d",&num_of_books_requested);
      max_request = max(max_request,num_of_books_requested);
      for(int book_i = 0; book_i < num_of_books_requested; book_i++){
	int id;
	scanf("%d",&id);
	students[student_i].push_back(id);
      }
    }
    queue<int> books;
    for(int book_i = 0; book_i < max_request; book_i++){
      for(int student_i = 0; student_i < num_of_students; student_i++){
	if(students[student_i].size() <= book_i) continue;
	books.push(students[student_i][book_i]);
      }
    }

    deque<int> desks[101];

    int score = 0;
    while(!books.empty()){
      int id = books.front();
      books.pop();

      //take from desk/shelf
      score += take_book(id,desks);

      //put 
      if(desks[0].size() < book_limit){
	desks[0].push_back(id);
	score += 1;
      }
      else{
	int tmp_place = -1;
	for(int desk_i = 1; desk_i <= num_of_desks; desk_i++){
	  //put to shelf
	  if(desk_i == num_of_desks){
	    desks[desk_i].push_back(id);
	    tmp_place = desk_i;
	    score += desk_i + 1;
	    break;
	  }
	  //put to desk
	  else if(desks[desk_i].size() < book_limit){
	    desks[desk_i].push_back(id);
	    tmp_place = desk_i;
	    score += desk_i + 1;
	    break;
	  }
	}

	//take book
	int old = desks[0].front(); 
	desks[0].pop_front();
	score += 1;

	for(int desk_i = 1; desk_i <= num_of_desks; desk_i++){
	  //put book
	  if(desk_i == num_of_desks){
	    desks[desk_i].push_back(old);
	    score += desk_i + 1;
	    break;
	  }
	  //put book
	  else if(desks[desk_i].size() < book_limit){
	    desks[desk_i].push_back(old);
	    score += desk_i + 1;
	    break;
	  }

	}

	//take book
	desks[tmp_place].pop_back();
	score += tmp_place + 1;

	//put book
	desks[0].push_back(id);
	score += 1;
      }
    }
    printf("%d\n",score);
  }
}
