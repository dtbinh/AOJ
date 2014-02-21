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

class Star {
private:
  int lower_bound_time;
  int upper_bound_time;
public:
  Star(int _l,int _u) : lower_bound_time(_l),upper_bound_time(_u){}
  Star() : lower_bound_time(0),upper_bound_time(0){}
  bool is_7age(int time){
    return (lower_bound_time <= time
	    && time <= upper_bound_time);
  }
};

int main(){
  int total_stars;
  int start;
  while(~scanf("%d %d",&total_stars,&start)){

    Star stars[501];
    for(int star_idx = 0; star_idx < total_stars; star_idx++){
      int lower_bound_time,upper_bound_time;
      scanf("%d %d",&lower_bound_time,&upper_bound_time);
      stars[star_idx] = Star(lower_bound_time,upper_bound_time);
    }

    int cost[501][501];
    for(int from_star_idx = 0; from_star_idx < total_stars; from_star_idx++){
      for(int to_star_idx = 0; to_star_idx < total_stars; to_star_idx++){
	scanf("%d",&cost[from_star_idx][to_star_idx]);
      }
    }

    
  }
}
