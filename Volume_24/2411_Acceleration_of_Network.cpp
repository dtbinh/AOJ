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
  int total_services;
  int seek_duration;
  while(~scanf("%d %d",&total_services,&seek_duration)){
    for(int service_idx = 0; service_idx < total_services; service_idx++){
      int lower_bound;
      int type;
      int speed_up_duration;
      scanf("%d %d %d",&lower_bound,&type,&speed_up_duration);
    }

    for(int seek_idx = 0; seek_idx < seek_duration; seek_idx++){
      int day;
      scanf("%d",&day);
    }
  }
}
