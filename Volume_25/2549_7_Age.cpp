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
public:
  int lower_bound_time;
  int upper_bound_time;
  int idx;
  Star(int _l,int _u,int _i) : lower_bound_time(_l),upper_bound_time(_u),idx(_i){}
  Star() : lower_bound_time(0),upper_bound_time(0){}
  bool operator<(const Star& s) const{
    return upper_bound_time < s.upper_bound_time;
  }
  bool operator>(const Star& s) const{
    return upper_bound_time > s.upper_bound_time;
  }
};

int main(){
  int total_stars;
  int start;
  while(~scanf("%d %d",&total_stars,&start)){
    start--;

    Star stars[501];
    for(int star_idx = 0; star_idx < total_stars; star_idx++){
      int lower_bound_time,upper_bound_time;
      scanf("%d %d",&lower_bound_time,&upper_bound_time);
      stars[star_idx] = Star(lower_bound_time,upper_bound_time,star_idx);
    }

    sort(stars,stars+total_stars);

    map<int,int> conv;
    for(int star_idx = 0; star_idx < total_stars; star_idx++){
      conv[stars[star_idx].idx] = star_idx;
    }

    int cost[501][501];
    memset(cost,0x3f,sizeof(cost));
    for(int from_star_idx = 0; from_star_idx < total_stars; from_star_idx++){
      for(int to_star_idx = 0; to_star_idx < total_stars; to_star_idx++){
	scanf("%d",&cost[conv[from_star_idx]][conv[to_star_idx]]);
      }
    }
    for(int mid_star_idx = 0; mid_star_idx < total_stars; mid_star_idx++){
      for(int from_star_idx = 0; from_star_idx < total_stars; from_star_idx++){
	for(int to_star_idx = 0; to_star_idx < total_stars; to_star_idx++){
	  cost[from_star_idx][to_star_idx]
	    = min(cost[from_star_idx][mid_star_idx]
		  + cost[mid_star_idx][to_star_idx],
		  cost[from_star_idx][to_star_idx]);
	}
      }
    }


    int max_duration[501];
    memset(max_duration,-1,sizeof(max_duration));

    int res = 0;
    start = conv[start];
    for(int to_star_idx = 0; to_star_idx < total_stars; to_star_idx++){
      if(cost[start][to_star_idx] <= stars[to_star_idx].upper_bound_time){
	max_duration[to_star_idx]
	  = stars[to_star_idx].upper_bound_time
	  - max(cost[start][to_star_idx],stars[to_star_idx].lower_bound_time);
	res = max(res,max_duration[to_star_idx]);
      }
    }


    for(int from_star_idx = 0; from_star_idx < total_stars; from_star_idx++){
      if(max_duration[from_star_idx] < 0) continue;

      for(int to_star_idx = 0; to_star_idx < total_stars; to_star_idx++){
	int time = stars[from_star_idx].upper_bound_time + cost[from_star_idx][to_star_idx];
	if(time > stars[to_star_idx].upper_bound_time) continue;

	if(max_duration[to_star_idx] 
	   < max_duration[from_star_idx] + stars[to_star_idx].upper_bound_time - max(time,stars[to_star_idx].lower_bound_time)){
	  max_duration[to_star_idx]
	    = max_duration[from_star_idx]
	    + stars[to_star_idx].upper_bound_time - max(time,stars[to_star_idx].lower_bound_time);
	  res = max(res,max_duration[to_star_idx]);
	}
      }
    }
    printf("%d\n",res);
  }
}
