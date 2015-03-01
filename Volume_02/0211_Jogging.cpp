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

static const int tx[] = {+0,+1,+0,-1};
static const int ty[] = {-1,+0,+1,+0};

ll GCD(ll a ,ll b){
  return b > 0 ? GCD(b,a%b) : a;
}

ll LCM(ll a ,ll b){
  return a / GCD(a,b) * b;
}

class Student {
public:
  ll distance;
  ll velocity;
  Student(ll distance,ll velocity) 
    : distance(distance), velocity(velocity) {}
};

int main(){
  int total_students;
  while(~scanf("%d",&total_students)){
    if(total_students == 0) break;

    vector<Student> students;
    for(int student_i = 0; student_i < total_students; student_i++){
      ll distance;
      ll velocity;
      scanf("%lld %lld",&distance,&velocity);
      int gcd = GCD(distance,velocity);
      students.push_back(Student(distance / gcd,velocity / gcd));
    }

    ll reference_distance = students[0].distance;
    for(int student_i = 0; student_i < total_students; student_i++){
      reference_distance = LCM(reference_distance,
			       students[student_i].distance);

    }

    for(int student_i = 0; student_i < total_students; student_i++){
      students[student_i].velocity
	= students[student_i].velocity * (reference_distance / students[student_i].distance);
    }

    ll gcd = students[0].velocity;
    for(int student_i = 0; student_i < total_students; student_i++){
      gcd = GCD(gcd,students[student_i].velocity);
    }
	
    for(int student_i = 0; student_i < total_students; student_i++){
      printf("%lld\n",students[student_i].velocity / gcd);
    }
  }
}
