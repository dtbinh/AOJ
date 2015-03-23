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

int main(){
  int num_of_desks;
  int num_of_books;
  int num_of_students;
  while(~scanf("%d %d %d",&num_of_desks,&num_of_books,&num_of_students)){
    for(int student_i = 0; student_i < num_of_students; student_i++){
      int num_of_books_requested;
      scanf("%d",&num_of_books_requested);
      for(int book_i = 0; book_i < num_of_books_requested; book_i++){
	int id;
	scanf("%d",&id);
      }
    }
  }
}
