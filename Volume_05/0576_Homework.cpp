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
  int total_holidays;
  while(~scanf("%d",&total_holidays)){
    int japanese_drill_pages;
    int math_drill_pages;
    int max_japanese_pages_par_day;
    int max_math_pages_par_day;
    scanf("%d %d %d %d",
	  &japanese_drill_pages,
	  &math_drill_pages,
	  &max_japanese_pages_par_day,
	  &max_math_pages_par_day);

    int remaining_days =
      total_holidays
      - max(japanese_drill_pages / max_japanese_pages_par_day
	    + (bool)(japanese_drill_pages % max_japanese_pages_par_day),
	    math_drill_pages / max_math_pages_par_day
	    + (bool)(math_drill_pages % max_math_pages_par_day));
	    
    printf("%d\n",remaining_days);
  }
}
